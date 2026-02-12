#ifndef DSA_CPP
#define DSA_CPP

#include <iostream>
#include <cstring>
using namespace std;

// ==================== LINKED LIST ====================
template <typename T>
class Node {
public:
    T data;
    Node* next;
    Node(T value) : data(value), next(nullptr) {}
};

template <typename T>
class LinkedList {
private:
    Node<T>* head;
    int size;

public:
    LinkedList() : head(nullptr), size(0) {}
    
    ~LinkedList() {
        while (head) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
        }
    }
    
    void insertAtBeginning(T data) {
        Node<T>* newNode = new Node<T>(data);
        newNode->next = head;
        head = newNode;
        size++;
    }
    
    void insertAtEnd(T data) {
        Node<T>* newNode = new Node<T>(data);
        if (!head) {
            head = newNode;
        } else {
            Node<T>* temp = head;
            while (temp->next) temp = temp->next;
            temp->next = newNode;
        }
        size++;
    }
    
    bool deleteByValue(T value) {
        if (!head) return false;
        
        if (head->data == value) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
            size--;
            return true;
        }
        
        Node<T>* current = head;
        while (current->next && current->next->data != value)
            current = current->next;
        
        if (current->next) {
            Node<T>* temp = current->next;
            current->next = current->next->next;
            delete temp;
            size--;
            return true;
        }
        return false;
    }
    
    bool search(T value) {
        Node<T>* temp = head;
        while (temp) {
            if (temp->data == value) return true;
            temp = temp->next;
        }
        return false;
    }
    
    T getAt(int index) {
        Node<T>* temp = head;
        for (int i = 0; i < index && temp; i++)
            temp = temp->next;
        if (temp) return temp->data;
        throw "Index out of bounds";
    }
    
    int getSize() { return size; }
    
    bool isEmpty() { return head == nullptr; }
};

// ==================== HASH TABLE ====================
const int HASH_TABLE_SIZE = 100;

template <typename V>
class HashTable {
private:
    struct Entry {
        char key[100];
        V value;
        bool occupied;
        Entry() : occupied(false) { key[0] = '\0'; }
    };
    
    Entry table[HASH_TABLE_SIZE];
    
    int hashFunction(const char* key) {
        int hash = 0;
        for (int i = 0; key[i] != '\0'; i++) {
            hash = (hash * 31 + key[i]) % HASH_TABLE_SIZE;
        }
        return hash;
    }
    
    int probe(int index, int i) {
        return (index + i * i) % HASH_TABLE_SIZE;
    }

public:
    bool insert(const char* key, const V& value) {
        int index = hashFunction(key);
        for (int i = 0; i < HASH_TABLE_SIZE; i++) {
            int probeIndex = probe(index, i);
            if (!table[probeIndex].occupied || strcmp(table[probeIndex].key, key) == 0) {
                strcpy(table[probeIndex].key, key);
                table[probeIndex].value = value;
                table[probeIndex].occupied = true;
                return true;
            }
        }
        return false;
    }
    
    bool search(const char* key, V& value) {
        int index = hashFunction(key);
        for (int i = 0; i < HASH_TABLE_SIZE; i++) {
            int probeIndex = probe(index, i);
            if (!table[probeIndex].occupied) return false;
            if (strcmp(table[probeIndex].key, key) == 0) {
                value = table[probeIndex].value;
                return true;
            }
        }
        return false;
    }
    
    bool remove(const char* key) {
        int index = hashFunction(key);
        for (int i = 0; i < HASH_TABLE_SIZE; i++) {
            int probeIndex = probe(index, i);
            if (!table[probeIndex].occupied) return false;
            if (strcmp(table[probeIndex].key, key) == 0) {
                table[probeIndex].occupied = false;
                return true;
            }
        }
        return false;
    }
};

// ==================== QUEUE ====================
template <typename T>
class Queue {
private:
    struct QueueNode {
        T data;
        QueueNode* next;
        QueueNode(T value) : data(value), next(nullptr) {}
    };
    
    QueueNode *front, *rear;
    int size;

public:
    Queue() : front(nullptr), rear(nullptr), size(0) {}
    
    ~Queue() {
        while (front) {
            QueueNode* temp = front;
            front = front->next;
            delete temp;
        }
    }
    
    void enqueue(T data) {
        QueueNode* newNode = new QueueNode(data);
        if (!rear) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
        size++;
    }
    
    bool dequeue(T& data) {
        if (!front) return false;
        QueueNode* temp = front;
        data = temp->data;
        front = front->next;
        if (!front) rear = nullptr;
        delete temp;
        size--;
        return true;
    }
    
    bool peek(T& data) {
        if (!front) return false;
        data = front->data;
        return true;
    }
    
    bool isEmpty() { return front == nullptr; }
    int getSize() { return size; }
};

// ==================== STACK ====================
template <typename T>
class Stack {
private:
    struct StackNode {
        T data;
        StackNode* next;
        StackNode(T value) : data(value), next(nullptr) {}
    };
    
    StackNode* top;
    int size;

public:
    Stack() : top(nullptr), size(0) {}
    
    ~Stack() {
        while (top) {
            StackNode* temp = top;
            top = top->next;
            delete temp;
        }
    }
    
    void push(T data) {
        StackNode* newNode = new StackNode(data);
        newNode->next = top;
        top = newNode;
        size++;
    }
    
    bool pop(T& data) {
        if (!top) return false;
        StackNode* temp = top;
        data = temp->data;
        top = top->next;
        delete temp;
        size--;
        return true;
    }
    
    bool peek(T& data) {
        if (!top) return false;
        data = top->data;
        return true;
    }
    
    bool isEmpty() { return top == nullptr; }
    int getSize() { return size; }
};

// ==================== SEARCHING ALGORITHMS ====================

// Linear Search
template <typename T>
int linearSearch(T arr[], int size, T target) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == target) return i;
    }
    return -1;
}

// Binary Search (requires sorted array)
template <typename T>
int binarySearch(T arr[], int size, T target) {
    int left = 0, right = size - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target) return mid;
        if (arr[mid] < target) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}

// ==================== SORTING ALGORITHMS ====================

// Bubble Sort
template <typename T>
void bubbleSort(T arr[], int size, bool ascending = true) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            bool condition = ascending ? arr[j] > arr[j + 1] : arr[j] < arr[j + 1];
            if (condition) {
                T temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Selection Sort
template <typename T>
void selectionSort(T arr[], int size, bool ascending = true) {
    for (int i = 0; i < size - 1; i++) {
        int idx = i;
        for (int j = i + 1; j < size; j++) {
            bool condition = ascending ? arr[j] < arr[idx] : arr[j] > arr[idx];
            if (condition) idx = j;
        }
        if (idx != i) {
            T temp = arr[i];
            arr[i] = arr[idx];
            arr[idx] = temp;
        }
    }
}

// Insertion Sort
template <typename T>
void insertionSort(T arr[], int size, bool ascending = true) {
    for (int i = 1; i < size; i++) {
        T key = arr[i];
        int j = i - 1;
        while (j >= 0 && ((ascending && arr[j] > key) || (!ascending && arr[j] < key))) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// Quick Sort Helper
template <typename T>
int partition(T arr[], int low, int high, bool ascending = true) {
    T pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        bool condition = ascending ? arr[j] < pivot : arr[j] > pivot;
        if (condition) {
            i++;
            T temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    T temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return i + 1;
}

// Quick Sort
template <typename T>
void quickSort(T arr[], int low, int high, bool ascending = true) {
    if (low < high) {
        int pi = partition(arr, low, high, ascending);
        quickSort(arr, low, pi - 1, ascending);
        quickSort(arr, pi + 1, high, ascending);
    }
}

#endif
