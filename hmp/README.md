# 🏨 Grand Horizon Hotel Management System

A complete, scalable Hotel Management System demonstrating real-world use of **C++** and **Data Structures & Algorithms** with a modern web interface.

---

## 📋 Table of Contents

1. [Project Overview](#project-overview)
2. [Features](#features)
3. [Technology Stack](#technology-stack)
4. [File Structure](#file-structure)
5. [Data Structures & Algorithms Used](#data-structures--algorithms-used)
6. [Installation & Setup](#installation--setup)
7. [Usage Guide](#usage-guide)
8. [Frontend Features](#frontend-features)
9. [Backend Features](#backend-features)
10. [How Frontend & Backend Connect](#how-frontend--backend-connect)
11. [Code Documentation](#code-documentation)

---

## 🎯 Project Overview

The Grand Horizon Hotel Management System is a comprehensive application that combines:

- **Frontend**: Modern, responsive web interface built with HTML, CSS, and JavaScript
- **Backend**: Robust C++ application implementing advanced data structures and algorithms
- **Storage**: File-based persistence for users, rooms, and bookings

This project demonstrates practical implementation of DSA concepts in a real-world hotel management scenario.

---

## ✨ Features

### User Management
- ✅ User registration with validation
- ✅ Secure login system using Hash Maps
- ✅ User data persistence in files
- ✅ Email and phone validation

### Room Management
- ✅ 20 pre-configured rooms across 5 floors
- ✅ 4 room types: Single, Double, Deluxe, Suite
- ✅ Dynamic room availability tracking
- ✅ Multiple search and filter options

### Booking System
- ✅ Real-time room booking
- ✅ Booking queue management
- ✅ Booking history with undo functionality
- ✅ Cancellation support
- ✅ Date-based pricing calculation

### Search & Filter
- ✅ Linear search by room number
- ✅ Binary search (optimized)
- ✅ Filter by floor (1-5)
- ✅ Filter by room type
- ✅ Filter by availability status

### Sorting
- ✅ Sort by price (ascending/descending)
- ✅ Sort by room number
- ✅ Sort by room type
- ✅ Multiple sorting algorithms implemented

---

## 🛠 Technology Stack

### Frontend
- **HTML5**: Structure and content
- **CSS3**: Modern styling with animations
- **JavaScript (ES6+)**: Interactive functionality
- **Google Fonts**: Playfair Display & Montserrat

### Backend
- **C++**: Core business logic
- **STL**: Standard Template Library for data structures
- **File I/O**: Data persistence

### Storage
- **Text Files**: Simple, readable data storage
  - `users.txt` - User data
  - `rooms.txt` - Room data
  - `bookings.txt` - Booking records

---

## 📁 File Structure

```
HotelManagementSystem/
│
├── index.html           # Landing page with hero section
├── login.html           # User login page
├── signup.html          # User registration page
├── booking.html         # Room booking interface
│
├── style.css            # Complete styling for all pages
├── script.js            # Frontend JavaScript logic
│
├── backend.cpp          # Main C++ backend application
├── dsa.cpp              # Data structures & algorithms library
│
├── users.txt            # User data storage
├── rooms.txt            # Room data storage
├── bookings.txt         # Booking records storage
│
└── README.md            # This file
```

---

## 🔬 Data Structures & Algorithms Used

### Data Structures

1. **Hash Map (unordered_map)**
   - **Use**: User authentication system
   - **Complexity**: O(1) average lookup
   - **Implementation**: Email → User mapping

2. **Vector**
   - **Use**: Room storage and management
   - **Complexity**: O(1) access, O(n) search
   - **Implementation**: Dynamic array of Room objects

3. **Queue**
   - **Use**: Booking request management
   - **Complexity**: O(1) enqueue/dequeue
   - **Implementation**: FIFO booking queue

4. **Stack**
   - **Use**: Booking history and undo functionality
   - **Complexity**: O(1) push/pop
   - **Implementation**: LIFO history stack

5. **Linked List**
   - **Use**: Custom implementation for extensibility
   - **Complexity**: O(n) search, O(1) insertion at head
   - **Implementation**: Template-based generic linked list

6. **Priority Queue (Heap)**
   - **Use**: Future enhancement for VIP bookings
   - **Complexity**: O(log n) insertion/deletion
   - **Implementation**: Max-heap based priority queue

### Algorithms

1. **Linear Search**
   - **Complexity**: O(n)
   - **Use**: Search room by number (unsorted)
   
2. **Binary Search**
   - **Complexity**: O(log n)
   - **Use**: Optimized room search (sorted)
   
3. **Bubble Sort**
   - **Complexity**: O(n²)
   - **Use**: Sort rooms by price
   
4. **Quick Sort**
   - **Complexity**: O(n log n) average
   - **Use**: Efficient sorting for large datasets
   
5. **Merge Sort**
   - **Complexity**: O(n log n)
   - **Use**: Stable sorting implementation
   
6. **Selection Sort**
   - **Complexity**: O(n²)
   - **Use**: Educational purpose
   
7. **Insertion Sort**
   - **Complexity**: O(n²)
   - **Use**: Efficient for small datasets

---

## 🚀 Installation & Setup

### Prerequisites
- Modern web browser (Chrome, Firefox, Safari, Edge)
- C++ compiler (g++, clang++)
- Text editor or IDE

### Frontend Setup

1. **Clone or download the project**
   ```bash
   cd HotelManagementSystem
   ```

2. **Open in browser**
   - Simply open `index.html` in your web browser
   - Or use a local server:
     ```bash
     # Python 3
     python -m http.server 8000
     
     # Node.js
     npx http-server
     ```

3. **Access the application**
   - Navigate to `http://localhost:8000`

### Backend Setup

1. **Compile the C++ backend**
   ```bash
   g++ -std=c++17 backend.cpp -o hotel_system
   ```

2. **Run the backend**
   ```bash
   ./hotel_system
   ```

3. **Follow the interactive menu**
   - The backend provides a CLI interface for testing

---

## 📖 Usage Guide

### Using the Web Interface

#### 1. Landing Page
- View hotel introduction and services
- Browse room categories
- Navigate to Login/Signup

#### 2. Sign Up
- Click "Sign Up" in navigation
- Fill in the registration form:
  - Full Name (min 2 characters)
  - Email (valid format)
  - Phone Number (min 10 digits)
  - Password (min 6 characters)
- Submit to create account

#### 3. Login
- Click "Login" in navigation
- Enter email and password
- Access the booking system

#### 4. Book a Room
- Use filters to find desired room:
  - Search by room number
  - Filter by floor (1-5)
  - Filter by type (Single/Double/Deluxe/Suite)
  - Filter by availability
- Sort results by:
  - Room number
  - Price (low to high / high to low)
  - Room type
- Click "Book Now" on available room
- Fill booking details:
  - Check-in date
  - Check-out date
  - Number of guests
  - Special requests
- Confirm booking

#### 5. Cancel Booking
- Find your booked room
- Click "Cancel Booking"
- Confirm cancellation

### Using the C++ Backend

The backend provides a comprehensive CLI menu:

```
1. Register User          - Create new user account
2. Login User             - Authenticate user
3. Display All Rooms      - View all rooms
4. Search Room by Number  - Find specific room
5. Filter Rooms by Floor  - Filter by floor number
6. Filter Rooms by Type   - Filter by room type
7. Sort Rooms by Price    - Sort ascending/descending
8. Display Available      - Show only available rooms
9. Book a Room            - Make a booking
10. Display Booking Queue - View all bookings
11. Display History       - View booking history
12. Cancel Booking        - Cancel a booking
0. Exit                   - Close application
```

---

## 🎨 Frontend Features

### Responsive Design
- Mobile-first approach
- Breakpoints: 480px, 768px, 1024px
- Hamburger menu for mobile

### Animations
- Fade-in effects on scroll
- Hover transitions
- Smooth scroll navigation
- Loading states

### Form Validation
- Real-time input validation
- Error message display
- Email format checking
- Password strength requirements

### Local Storage
- User session management
- Room data caching
- Booking persistence

---

## ⚙️ Backend Features

### File Handling
- **Read**: Load existing data on startup
- **Write**: Save new records immediately
- **Update**: Modify existing records
- **Format**: Pipe-delimited text files

### Error Handling
- Input validation
- Duplicate prevention
- Availability checking
- Format verification

### Data Persistence
All data is stored in text files:

**users.txt format:**
```
id|name|email|phone|password|timestamp
```

**rooms.txt format:**
```
id|number|floor|type|price|available
```

**bookings.txt format:**
```
id|userId|roomId|checkIn|checkOut|guests|requests|price|status|timestamp
```

---

## 🔗 How Frontend & Backend Connect

### Current Implementation (Simulated)

The frontend uses **localStorage** to simulate backend functionality:

1. **User Registration**
   - Frontend validates input
   - Stores in localStorage
   - Simulates backend registration

2. **Room Booking**
   - Frontend checks availability
   - Updates room status
   - Creates booking record

### Integration Path (Production)

To connect frontend with C++ backend:

1. **Create REST API** (using C++ web framework like Crow or Pistache)
2. **Define endpoints**:
   - `POST /api/register` - User registration
   - `POST /api/login` - User login
   - `GET /api/rooms` - Get all rooms
   - `GET /api/rooms/:id` - Get room by ID
   - `POST /api/bookings` - Create booking
   - `DELETE /api/bookings/:id` - Cancel booking

3. **Update frontend** to use fetch API:
   ```javascript
   async function loginUser(email, password) {
     const response = await fetch('/api/login', {
       method: 'POST',
       headers: { 'Content-Type': 'application/json' },
       body: JSON.stringify({ email, password })
     });
     return await response.json();
   }
   ```

---

## 📚 Code Documentation

### Key Classes

#### HotelManagementSystem (backend.cpp)
Main class managing all hotel operations.

**Methods:**
- `registerUser()` - Register new user
- `loginUser()` - Authenticate user
- `displayAllRooms()` - Show all rooms
- `searchRoomByNumber()` - Linear search
- `binarySearchByNumber()` - Binary search
- `filterByFloor()` - Filter rooms
- `sortRoomsByPrice()` - Bubble sort
- `bookRoom()` - Create booking
- `cancelBooking()` - Cancel booking

#### Data Structure Classes (dsa.cpp)

**LinkedList<T>**
- `insertAtBeginning()`
- `insertAtEnd()`
- `deleteByValue()`
- `search()`

**HashTable<K, V>**
- `insert()`
- `search()`
- `remove()`

**QueueDS<T>**
- `enqueue()`
- `dequeue()`
- `peek()`

**StackDS<T>**
- `push()`
- `pop()`
- `peek()`

### Frontend Functions

**Validation (script.js)**
- `validateEmail()` - Email format validation
- `validatePhone()` - Phone number validation
- `validatePassword()` - Password strength check

**Search Algorithms (script.js)**
- `linearSearchRoom()` - O(n) search
- `binarySearchRoom()` - O(log n) search

**Sorting (script.js)**
- `bubbleSortByPrice()` - Sort by price
- `quickSortByType()` - Sort by type

---

## 🎓 Learning Outcomes

This project demonstrates:

1. **Hash Map Usage**: Fast user lookup for authentication
2. **Queue Implementation**: Managing booking requests in order
3. **Stack Application**: Undo functionality for bookings
4. **Search Algorithms**: Comparing linear vs binary search
5. **Sorting Algorithms**: Understanding time complexity
6. **File I/O**: Persistent data storage
7. **Web Development**: Creating responsive interfaces
8. **Integration**: Connecting frontend and backend

---

## 🔮 Future Enhancements

- [ ] JWT-based authentication
- [ ] Payment gateway integration
- [ ] Email notifications
- [ ] Admin dashboard
- [ ] Room availability calendar
- [ ] Price dynamic pricing
- [ ] Review and rating system
- [ ] Multi-language support
- [ ] Mobile application
- [ ] Database integration (MySQL/PostgreSQL)

---

## 👥 Contributors

This is an educational project demonstrating DSA concepts in a practical application.

---

## 📝 License

This project is created for educational purposes.

---

## 🙏 Acknowledgments

- Modern web design principles
- C++ STL documentation
- Data structures & algorithms textbooks
- Web development best practices

---

## 📞 Support

For questions or issues, please review the code comments and documentation.

---

## 🌟 Key Features Summary

### ✅ Frontend Deliverables
- Attractive landing page with hero section
- Responsive navigation bar
- User signup/login forms with validation
- Room booking interface with filters
- Search and sort functionality
- Modal dialogs for booking
- Mobile-responsive design

### ✅ Backend Deliverables
- User management with Hash Maps
- Room management with Vectors
- Booking queue implementation
- Booking history stack
- Linear and binary search
- Multiple sorting algorithms
- File-based data persistence
- Complete CLI interface

### ✅ DSA Implementations
- Hash Table (authentication)
- Linked List (custom implementation)
- Queue (booking requests)
- Stack (booking history)
- Vector (room storage)
- Linear Search (O(n))
- Binary Search (O(log n))
- Bubble Sort (O(n²))
- Quick Sort (O(n log n))
- Merge Sort (O(n log n))

---

**Enjoy using the Grand Horizon Hotel Management System! 🏨**
