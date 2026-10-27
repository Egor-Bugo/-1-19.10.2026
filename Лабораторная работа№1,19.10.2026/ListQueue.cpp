#include "ListQueue.h"
#include "MyException.h"
#include <iostream>
ListQueue::ListQueue() : head(nullptr), tail(nullptr), count(0) {
    std::cout << "[Constructor] ListQueue created.\n";
}
ListQueue::ListQueue(const ListQueue& other) : head(nullptr), tail(nullptr), count(0) {
    std::cout << "[Copy Constructor] ListQueue copied.\n";
    QueueNode* current = other.head;
    while (current != nullptr) {
        push(current->data);
        current = current->next;
    }
}
ListQueue::~ListQueue() {
    std::cout << "[Destructor] ListQueue destroyed.\n";
    while (head != nullptr) {
        QueueNode* temp = head;
        head = head->next;
        delete temp;
    }
}
void ListQueue::push(int value) {
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
int ListQueue::pop() {
    if (head == nullptr) {
        throw MyException("Error: List is empty, cannot pop element!");
    }
    QueueNode* temp = head;
    int val = temp->data;
    head = head->next;
    if (head == nullptr) {
        tail = nullptr;
    }
    delete temp;
    count--;
    return val;
}
void ListQueue::print() const {
    std::cout << "List (Queue-based): ";
    QueueNode* current = head;
    while (current != nullptr) {
        std::cout << current->data << " ";
        current = current->next;
    }
    std::cout << "\n";
}
void ListQueue::saveToFile(std::ostream& os) const {
    os << count << " ";
    QueueNode* current = head;
    while (current != nullptr) {
        os << current->data << " ";
        current = current->next;
    }
}
void ListQueue::loadFromFile(std::istream& is) {
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