#include "StackQueue.h"
#include "MyException.h"
#include <iostream>

StackQueue::StackQueue() : topNode(nullptr), count(0) {
    std::cout << "[Constructor] StackQueue created.\n";
}

StackQueue::StackQueue(const StackQueue& other) : topNode(nullptr), count(0) {
    std::cout << "[Copy Constructor] StackQueue copied.\n";
    // Для сохранения порядка стека копируем через временный массив
    if (other.count == 0) return;
    int* arr = new int[other.count];
    QueueNode* curr = other.topNode;
    int i = 0;
    while (curr) {
        arr[i++] = curr->data;
        curr = curr->next;
    }
    for (int j = other.count - 1; j >= 0; --j) {
        push(arr[j]);
    }
    delete[] arr;
}

StackQueue::~StackQueue() {
    std::cout << "[Destructor] StackQueue destroyed.\n";
    while (topNode != nullptr) {
        QueueNode* temp = topNode;
        topNode = topNode->next;
        delete temp;
    }
}

void StackQueue::push(int value) {
    // Реализация стека на основе принципа очереди (переворот при добавлении)
    QueueNode* newNode = new QueueNode(value);
    newNode->next = topNode;
    topNode = newNode;
    count++;
}

int StackQueue::pop() {
    if (topNode == nullptr) {
        throw MyException("Error: Stack is empty, cannot pop element!");
    }
    QueueNode* temp = topNode;
    int val = temp->data;
    topNode = topNode->next;
    delete temp;
    count--;
    return val;
}

void StackQueue::print() const {
    std::cout << "Stack (Queue-based): ";
    QueueNode* current = topNode;
    while (current != nullptr) {
        std::cout << current->data << " ";
        current = current->next;
    }
    std::cout << "\n";
}

void StackQueue::saveToFile(std::ostream& os) const {
    os << count << " ";
    QueueNode* current = topNode;
    while (current != nullptr) {
        os << current->data << " ";
        current = current->next;
    }
}

void StackQueue::loadFromFile(std::istream& is) {
    while (topNode != nullptr) {
        QueueNode* temp = topNode;
        topNode = topNode->next;
        delete temp;
    }
    count = 0;

    int size;
    if (!(is >> size)) return;
    int* arr = new int[size];
    for (int i = 0; i < size; ++i) {
        is >> arr[i];
    }
    for (int i = size - 1; i >= 0; --i) {
        push(arr[i]);
    }
    delete[] arr;
}