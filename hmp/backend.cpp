#include <iostream>
#include <fstream>
#include <cstring>
#include <ctime>
#include "dsa_simplified.cpp"

using namespace std;

const string USERS_FILE = "users.txt";
const string ROOMS_FILE = "rooms.txt";
const string BOOKINGS_FILE = "bookings.txt";
const int MAX_ROOMS = 100;

// ==================== STRUCTURES ====================
struct User {
    int id;
    char name[100];
    char email[100];
    char phone[20];
    char password[100];
    time_t createdAt;
};

struct Room {
    int id;
    int number;
    int floor;
    char type[20];
    double price;
    bool available;
};

struct Booking {
    int id;
    int userId;
    int roomId;
    char checkIn[20];
    char checkOut[20];
    int guests;
    char specialRequests[200];
    double totalPrice;
    char status[20];
    time_t bookedAt;
};

// ==================== GLOBAL DATA STRUCTURES ====================
HashTable<User> userHashMap;          // Email -> User
Room roomsArray[MAX_ROOMS];            // Array to store rooms
int roomCount = 0;                     // Number of rooms
Queue<Booking> bookingQueue;           // Queue for booking requests
Stack<Booking> bookingHistory;         // Stack for booking history

// ==================== CLASS DEFINITIONS ====================
class HotelManagementSystem {
private:
    int nextUserId;
    int nextBookingId;

    bool isValidEmail(const char* email) {
        int len = strlen(email);
        bool hasAt = false;
        int atPos = -1;
        for (int i = 0; i < len; i++) {
            if (email[i] == '@') {
                hasAt = true;
                atPos = i;
                break;
            }
        }
        if (!hasAt || atPos == 0) return false;
        
        bool hasDot = false;
        for (int i = atPos + 1; i < len; i++) {
            if (email[i] == '.') {
                hasDot = true;
                break;
            }
        }
        return hasDot;
    }

    bool isValidPhone(const char* phone) {
        return strlen(phone) >= 10;
    }

    void saveUserToFile(const User& user) {
        ofstream file(USERS_FILE, ios::app);
        if (file.is_open()) {
            file << user.id << "|" << user.name << "|" << user.email << "|" 
                 << user.phone << "|" << user.password << "|" << user.createdAt << endl;
            file.close();
        }
    }

    void saveRoomsToFile() {
        ofstream file(ROOMS_FILE);
        if (file.is_open()) {
            for (int i = 0; i < roomCount; i++) {
                file << roomsArray[i].id << "|" << roomsArray[i].number << "|" 
                     << roomsArray[i].floor << "|" << roomsArray[i].type << "|" 
                     << roomsArray[i].price << "|" << roomsArray[i].available << endl;
            }
            file.close();
        }
    }

    void saveBookingToFile(const Booking& booking) {
        ofstream file(BOOKINGS_FILE, ios::app);
        if (file.is_open()) {
            file << booking.id << "|" << booking.userId << "|" << booking.roomId << "|" 
                 << booking.checkIn << "|" << booking.checkOut << "|" << booking.guests << "|" 
                 << booking.specialRequests << "|" << booking.totalPrice << "|" 
                 << booking.status << "|" << booking.bookedAt << endl;
            file.close();
        }
    }

    void loadUsersFromFile() {
        ifstream file(USERS_FILE);
        if (!file.is_open()) return;
        
        string line;
        while (getline(file, line)) {
            if (line.empty() || line[0] == '#') continue;
            
            User user;
            sscanf(line.c_str(), "%d|%99[^|]|%99[^|]|%19[^|]|%99[^|]|%ld",
                   &user.id, user.name, user.email, user.phone, user.password, &user.createdAt);
            
            userHashMap.insert(user.email, user);
            if (user.id >= nextUserId) nextUserId = user.id + 1;
        }
        file.close();
    }

    void loadRoomsFromFile() {
        ifstream file(ROOMS_FILE);
        if (!file.is_open()) return;
        
        string line;
        roomCount = 0;
        while (getline(file, line) && roomCount < MAX_ROOMS) {
            if (line.empty() || line[0] == '#') continue;
            
            int avail;
            sscanf(line.c_str(), "%d|%d|%d|%19[^|]|%lf|%d",
                   &roomsArray[roomCount].id, &roomsArray[roomCount].number,
                   &roomsArray[roomCount].floor, roomsArray[roomCount].type,
                   &roomsArray[roomCount].price, &avail);
            roomsArray[roomCount].available = (avail == 1);
            roomCount++;
        }
        file.close();
    }

    void loadBookingsFromFile() {
        ifstream file(BOOKINGS_FILE);
        if (!file.is_open()) return;
        
        string line;
        while (getline(file, line)) {
            if (line.empty() || line[0] == '#') continue;
            
            Booking booking;
            sscanf(line.c_str(), "%d|%d|%d|%19[^|]|%19[^|]|%d|%199[^|]|%lf|%19[^|]|%ld",
                   &booking.id, &booking.userId, &booking.roomId, booking.checkIn,
                   booking.checkOut, &booking.guests, booking.specialRequests,
                   &booking.totalPrice, booking.status, &booking.bookedAt);
            
            bookingQueue.enqueue(booking);
            bookingHistory.push(booking);
            if (booking.id >= nextBookingId) nextBookingId = booking.id + 1;
        }
        file.close();
    }

public:
    HotelManagementSystem() : nextUserId(1), nextBookingId(1) {
        initializeRooms();
        loadUsersFromFile();
        loadRoomsFromFile();
        loadBookingsFromFile();
    }

    void initializeRooms() {
        int roomId = 1;
        const char* types[] = {"Single", "Double", "Deluxe", "Suite"};
        double prices[] = {120.0, 180.0, 280.0, 500.0};
        
        roomCount = 0;
        for (int floor = 1; floor <= 5; floor++) {
            for (int i = 0; i < 4; i++) {
                if (roomCount >= MAX_ROOMS) break;
                
                roomsArray[roomCount].id = roomId;
                roomsArray[roomCount].number = floor * 100 + i + 1;
                roomsArray[roomCount].floor = floor;
                strcpy(roomsArray[roomCount].type, types[i]);
                roomsArray[roomCount].price = prices[i];
                roomsArray[roomCount].available = true;
                
                roomCount++;
                roomId++;
            }
        }
    }

    // ==================== USER MANAGEMENT ====================
    bool registerUser(const char* name, const char* email, const char* phone, const char* password) {
        User existingUser;
        if (userHashMap.search(email, existingUser)) {
            cout << "Error: Email already registered!" << endl;
            return false;
        }
        
        if (!isValidEmail(email)) {
            cout << "Error: Invalid email!" << endl;
            return false;
        }
        
        if (!isValidPhone(phone)) {
            cout << "Error: Invalid phone!" << endl;
            return false;
        }
        
        if (strlen(password) < 6) {
            cout << "Error: Password must be at least 6 characters!" << endl;
            return false;
        }

        User user;
        user.id = nextUserId++;
        strcpy(user.name, name);
        strcpy(user.email, email);
        strcpy(user.phone, phone);
        strcpy(user.password, password);
        user.createdAt = time(0);
        
        userHashMap.insert(email, user);
        saveUserToFile(user);
        cout << "User registered successfully! ID: " << user.id << endl;
        return true;
    }

    bool loginUser(const char* email, const char* password) {
        User user;
        if (!userHashMap.search(email, user)) {
            cout << "Error: Email not found!" << endl;
            return false;
        }
        
        if (strcmp(user.password, password) != 0) {
            cout << "Error: Incorrect password!" << endl;
            return false;
        }
        
        cout << "Login successful! Welcome, " << user.name << endl;
        return true;
    }

    // ==================== ROOM MANAGEMENT ====================
    void displayAllRooms() {
        cout << "\n===== ALL ROOMS =====\n";
        cout << "ID\tRoom#\tFloor\tType\t\tPrice\tAvailable\n";
        for (int i = 0; i < roomCount; i++) {
            cout << roomsArray[i].id << "\t" << roomsArray[i].number << "\t" 
                 << roomsArray[i].floor << "\t" << roomsArray[i].type << "\t\t$" 
                 << roomsArray[i].price << "\t" 
                 << (roomsArray[i].available ? "Yes" : "No") << endl;
        }
    }

    // Linear Search by room number
    Room* searchRoomByNumber(int roomNumber) {
        for (int i = 0; i < roomCount; i++) {
            if (roomsArray[i].number == roomNumber) {
                return &roomsArray[i];
            }
        }
        return nullptr;
    }

    // Binary Search by room number (array must be sorted first)
    Room* binarySearchByNumber(int roomNumber) {
        // First, create a sorted copy of room numbers with indices
        int sortedNumbers[MAX_ROOMS];
        int sortedIndices[MAX_ROOMS];
        
        for (int i = 0; i < roomCount; i++) {
            sortedNumbers[i] = roomsArray[i].number;
            sortedIndices[i] = i;
        }
        
        // Bubble sort the numbers array along with indices
        for (int i = 0; i < roomCount - 1; i++) {
            for (int j = 0; j < roomCount - i - 1; j++) {
                if (sortedNumbers[j] > sortedNumbers[j + 1]) {
                    int tempNum = sortedNumbers[j];
                    sortedNumbers[j] = sortedNumbers[j + 1];
                    sortedNumbers[j + 1] = tempNum;
                    
                    int tempIdx = sortedIndices[j];
                    sortedIndices[j] = sortedIndices[j + 1];
                    sortedIndices[j + 1] = tempIdx;
                }
            }
        }
        
        // Binary search on sorted array
        int index = binarySearch(sortedNumbers, roomCount, roomNumber);
        if (index != -1) {
            return &roomsArray[sortedIndices[index]];
        }
        return nullptr;
    }

    // Filter rooms by floor (stores results in provided array)
    int filterByFloor(int floor, Room resultArray[], int maxResults) {
        int count = 0;
        for (int i = 0; i < roomCount && count < maxResults; i++) {
            if (roomsArray[i].floor == floor) {
                resultArray[count++] = roomsArray[i];
            }
        }
        return count;
    }

    // Filter rooms by type
    int filterByType(const char* type, Room resultArray[], int maxResults) {
        int count = 0;
        for (int i = 0; i < roomCount && count < maxResults; i++) {
            if (strcmp(roomsArray[i].type, type) == 0) {
                resultArray[count++] = roomsArray[i];
            }
        }
        return count;
    }

    // Sort rooms by price (using bubble sort)
    void sortRoomsByPrice(bool ascending = true) {
        for (int i = 0; i < roomCount - 1; i++) {
            for (int j = 0; j < roomCount - i - 1; j++) {
                bool condition = ascending ? 
                    roomsArray[j].price > roomsArray[j + 1].price : 
                    roomsArray[j].price < roomsArray[j + 1].price;
                
                if (condition) {
                    Room temp = roomsArray[j];
                    roomsArray[j] = roomsArray[j + 1];
                    roomsArray[j + 1] = temp;
                }
            }
        }
    }

    // Get available rooms
    int getAvailableRooms(Room resultArray[], int maxResults) {
        int count = 0;
        for (int i = 0; i < roomCount && count < maxResults; i++) {
            if (roomsArray[i].available) {
                resultArray[count++] = roomsArray[i];
            }
        }
        return count;
    }

    // ==================== BOOKING MANAGEMENT ====================
    bool bookRoom(int userId, int roomNumber, const char* checkIn, const char* checkOut, 
                  int guests, const char* specialRequests) {
        Room* room = searchRoomByNumber(roomNumber);
        if (!room) {
            cout << "Room not found!" << endl;
            return false;
        }
        if (!room->available) {
            cout << "Room not available!" << endl;
            return false;
        }

        Booking booking;
        booking.id = nextBookingId++;
        booking.userId = userId;
        booking.roomId = room->id;
        strcpy(booking.checkIn, checkIn);
        strcpy(booking.checkOut, checkOut);
        booking.guests = guests;
        strcpy(booking.specialRequests, specialRequests);
        booking.totalPrice = room->price * 3; // Simplified: 3 nights
        strcpy(booking.status, "Confirmed");
        booking.bookedAt = time(0);
        
        room->available = false;
        bookingQueue.enqueue(booking);
        bookingHistory.push(booking);
        saveBookingToFile(booking);
        saveRoomsToFile();
        
        cout << "Booking successful! ID: " << booking.id << endl;
        return true;
    }

    void displayBookingQueue() {
        if (bookingQueue.isEmpty()) {
            cout << "No bookings in queue." << endl;
            return;
        }
        
        cout << "\n===== BOOKING QUEUE =====\n";
        // Note: Can't iterate queue without dequeuing, would need temp queue
        cout << "Queue size: " << bookingQueue.getSize() << endl;
    }

    void displayBookingHistory() {
        if (bookingHistory.isEmpty()) {
            cout << "No booking history." << endl;
            return;
        }
        
        cout << "\n===== BOOKING HISTORY =====\n";
        cout << "History size: " << bookingHistory.getSize() << endl;
    }

    bool cancelBooking(int bookingId) {
        Stack<Booking> temp;
        bool found = false;
        Booking current;
        
        while (bookingHistory.pop(current)) {
            if (current.id == bookingId && strcmp(current.status, "Confirmed") == 0) {
                strcpy(current.status, "Cancelled");
                for (int i = 0; i < roomCount; i++) {
                    if (roomsArray[i].id == current.roomId) {
                        roomsArray[i].available = true;
                        break;
                    }
                }
                found = true;
            }
            temp.push(current);
        }
        
        while (temp.pop(current)) {
            bookingHistory.push(current);
        }
        
        if (found) {
            saveRoomsToFile();
            cout << "Booking cancelled successfully!" << endl;
        } else {
            cout << "Booking not found or already cancelled!" << endl;
        }
        return found;
    }
};

// ==================== MAIN FUNCTION ====================
int main() {
    HotelManagementSystem hotel;
    
    cout << "\n========================================\n";
    cout << "   GRAND HORIZON HOTEL MANAGEMENT\n";
    cout << "========================================\n";
    
    int choice;
    bool running = true;
    
    while (running) {
        cout << "\n===== MENU =====\n";
        cout << "1. Register User\n";
        cout << "2. Login User\n";
        cout << "3. Display All Rooms\n";
        cout << "4. Search Room (Linear Search)\n";
        cout << "5. Search Room (Binary Search)\n";
        cout << "6. Filter by Floor\n";
        cout << "7. Filter by Type\n";
        cout << "8. Sort by Price\n";
        cout << "9. Display Available Rooms\n";
        cout << "10. Book Room\n";
        cout << "11. Display Booking Queue\n";
        cout << "12. Display Booking History\n";
        cout << "13. Cancel Booking\n";
        cout << "0. Exit\n";
        cout << "Choice: ";
        cin >> choice;
        cin.ignore();
        
        switch (choice) {
            case 1: {
                char name[100], email[100], phone[20], password[100];
                cout << "Name: "; cin.getline(name, 100);
                cout << "Email: "; cin.getline(email, 100);
                cout << "Phone: "; cin.getline(phone, 20);
                cout << "Password: "; cin.getline(password, 100);
                hotel.registerUser(name, email, phone, password);
                break;
            }
            case 2: {
                char email[100], password[100];
                cout << "Email: "; cin.getline(email, 100);
                cout << "Password: "; cin.getline(password, 100);
                hotel.loginUser(email, password);
                break;
            }
            case 3:
                hotel.displayAllRooms();
                break;
            case 4: {
                int roomNumber;
                cout << "Room number: "; cin >> roomNumber;
                Room* room = hotel.searchRoomByNumber(roomNumber);
                if (room) {
                    cout << "\nRoom Found!\n";
                    cout << "Room #: " << room->number << endl;
                    cout << "Floor: " << room->floor << endl;
                    cout << "Type: " << room->type << endl;
                    cout << "Price: $" << room->price << endl;
                    cout << "Available: " << (room->available ? "Yes" : "No") << endl;
                } else {
                    cout << "Room not found!" << endl;
                }
                break;
            }
            case 5: {
                int roomNumber;
                cout << "Room number: "; cin >> roomNumber;
                Room* room = hotel.binarySearchByNumber(roomNumber);
                if (room) {
                    cout << "\nRoom Found (Binary Search)!\n";
                    cout << "Room #: " << room->number << endl;
                    cout << "Type: " << room->type << endl;
                    cout << "Price: $" << room->price << endl;
                } else {
                    cout << "Room not found!" << endl;
                }
                break;
            }
            case 6: {
                int floor;
                Room results[MAX_ROOMS];
                cout << "Floor (1-5): "; cin >> floor;
                int count = hotel.filterByFloor(floor, results, MAX_ROOMS);
                cout << "\nRooms on Floor " << floor << ": " << count << endl;
                for (int i = 0; i < count; i++) {
                    cout << "Room " << results[i].number << " - " << results[i].type 
                         << " - $" << results[i].price << endl;
                }
                break;
            }
            case 7: {
                char type[20];
                Room results[MAX_ROOMS];
                cout << "Type (Single/Double/Deluxe/Suite): ";
                cin.ignore();
                cin.getline(type, 20);
                int count = hotel.filterByType(type, results, MAX_ROOMS);
                cout << "\n" << type << " Rooms: " << count << endl;
                for (int i = 0; i < count; i++) {
                    cout << "Room " << results[i].number << " - Floor " << results[i].floor 
                         << " - $" << results[i].price << endl;
                }
                break;
            }
            case 8: {
                cout << "Sort: 1. Low to High  2. High to Low\n";
                int sortChoice; cin >> sortChoice;
                hotel.sortRoomsByPrice(sortChoice == 1);
                cout << "Rooms sorted by price!\n";
                hotel.displayAllRooms();
                break;
            }
            case 9: {
                Room results[MAX_ROOMS];
                int count = hotel.getAvailableRooms(results, MAX_ROOMS);
                cout << "\nAvailable Rooms: " << count << endl;
                for (int i = 0; i < count; i++) {
                    cout << "Room " << results[i].number << " - " << results[i].type 
                         << " - $" << results[i].price << endl;
                }
                break;
            }
            case 10: {
                int userId, roomNumber, guests;
                char checkIn[20], checkOut[20], requests[200];
                cout << "User ID: "; cin >> userId;
                cout << "Room number: "; cin >> roomNumber;
                cin.ignore();
                cout << "Check-in (YYYY-MM-DD): "; cin.getline(checkIn, 20);
                cout << "Check-out (YYYY-MM-DD): "; cin.getline(checkOut, 20);
                cout << "Guests: "; cin >> guests;
                cin.ignore();
                cout << "Special requests: "; cin.getline(requests, 200);
                hotel.bookRoom(userId, roomNumber, checkIn, checkOut, guests, requests);
                break;
            }
            case 11:
                hotel.displayBookingQueue();
                break;
            case 12:
                hotel.displayBookingHistory();
                break;
            case 13: {
                int bookingId;
                cout << "Booking ID: "; cin >> bookingId;
                hotel.cancelBooking(bookingId);
                break;
            }
            case 0:
                cout << "Thank you!\n";
                running = false;
                break;
            default:
                cout << "Invalid choice!\n";
        }
    }
    
    return 0;
}
