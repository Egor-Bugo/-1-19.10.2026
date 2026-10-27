#include "DequeQueue.h"
#include "MyException.h"
#include <iostream>
DequeQueue::DequeQueue() : head(nullptr), tail(nullptr), count(0) {
    std::cout << "[Constructor] DequeQueue created.\n";
}
DequeQueue::DequeQueue(const DequeQueue& other) : head(nullptr), tail(nullptr), count(0) {
    std::cout << "[Copy Constructor] DequeQueue copied.\n";
    QueueNode* current = other.head;
    while (current != nullptr) {
        push(current->data);
        current = current->next;
    }
}
DequeQueue::~DequeQueue() {
    std::cout << "[Destructor] DequeQueue destroyed.\n";
    while (head != nullptr) {
        QueueNode* temp = head;
        head = head->next;
        delete temp;
    }
}
void DequeQueue::push(int value) {
    QueueNode* newNode = new QueueNode(value);
    if (tail == nullptr) {
        head = tail = newNode;
    }
    else {
        tail->next = newNode;
        tail = newNode;
    }
    count++;
}
void DequeQueue::pushFront(int value) {
    QueueNode* newNode = new QueueNode(value);
    if (head == nullptr) {
        head = tail = newNode;
    }
    else {
        newNode->next = head;
        head = newNode;
    }
    count++;
}
int DequeQueue::pop() {
    if (head == nullptr) {
        throw MyException("Error: Deque is empty, cannot pop from front!");
    }
    QueueNode* temp = head;
    int val = temp->data;
    head = head->next;
    if (head == nullptr) tail = nullptr;
    delete temp;
    count--;
    return val;
}
int DequeQueue::popBack() {
    if (tail == nullptr) {
        throw MyException("Error: Deque is empty, cannot pop from back!");
    }
    if (head == tail) {
        int val = head->data;
        delete head;
        head = tail = nullptr;
        count--;
        return val;
    }
    QueueNode* current = head;
    while (current->next != tail) {
        current = current->next;
    }
    int val = tail->data;
    delete tail;
    tail = current;
    tail->next = nullptr;
    count--;
    return val;
}
void DequeQueue::print() const {
    std::cout << "Deque (Queue-based): ";
    QueueNode* current = head;
    while (current != nullptr) {
        std::cout << current->data << " ";
        current = current->next;
    }
    std::cout << "\n";
}
void DequeQueue::saveToFile(std::ostream& os) const {
    os << count << " ";
    QueueNode* current = head;
    while (current != nullptr) {
        os << current->data << " ";
        current = current->next;
    }
}
void DequeQueue::loadFromFile(std::istream& is) {
    while (head != nullptr) {
        QueueNode* temp = head;
        head = head->next;
        delete temp;
    }
    tail = nullptr;
    count = 0;

    int size;
    if (!(is >> size)) return;
    for (int i = 0; i < size; ++i) {
        int val;
        is >> val;
        push(val);
    }
}