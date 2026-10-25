#include "Keeper.h"
#include "ListQueue.h"
#include "StackQueue.h"
#include "DequeQueue.h"
#include "MyException.h"
#include <iostream>
#include <fstream>
#include <cstring>

void Keeper::resize(int newCapacity) {
    capacity = newCapacity > 0 ? newCapacity : 1;
    Base** newData = new Base * [capacity];
    for (int i = 0; i < size; ++i) {
        newData[i] = data[i];
    }
    delete[] data;
    data = newData;
}

Keeper::Keeper() : size(0), capacity(2) {
    data = new Base * [capacity];
    std::cout << "[Constructor] Keeper created.\n";
}

Keeper::Keeper(const Keeper& other) : size(other.size), capacity(other.capacity) {
    data = new Base * [capacity];
    for (int i = 0; i < size; ++i) {
        // Копирование через фабричный метод или условие типа
        if (std::strcmp(other.data[i]->getType(), "List") == 0) {
            data[i] = new ListQueue(*(static_cast<ListQueue*>(other.data[i])));
        }
        else if (std::strcmp(other.data[i]->getType(), "Stack") == 0) {
            data[i] = new StackQueue(*(static_cast<StackQueue*>(other.data[i])));
        }
        else if (std::strcmp(other.data[i]->getType(), "Deque") == 0) {
            data[i] = new DequeQueue(*(static_cast<DequeQueue*>(other.data[i])));
        }
    }
    std::cout << "[Copy Constructor] Keeper copied.\n";
}

Keeper::~Keeper() {
    for (int i = 0; i < size; ++i) {
        delete data[i];
    }
    delete[] data;
    std::cout << "[Destructor] Keeper destroyed.\n";
}

void Keeper::add(Base* obj) {
    if (size >= capacity) {
        resize(capacity * 2);
    }
    data[size++] = obj;
}

void Keeper::remove(int index) {
    if (index < 0 || index >= size) {
        throw MyException("Error: Invalid index for removal!");
    }
    delete data[index];
    for (int i = index; i < size - 1; ++i) {
        data[i] = data[i + 1];
    }
    size--;
}

Base* Keeper::get(int index) const {
    if (index < 0 || index >= size) {
        throw MyException("Error: Index out of bounds!");
    }
    return data[index];
}

int Keeper::getSize() const {
    return size;
}

void Keeper::printAll() const {
    if (size == 0) {
        std::cout << "Keeper is empty.\n";
        return;
    }
    for (int i = 0; i < size; ++i) {
        std::cout << "[" << i << "] Type: " << data[i]->getType() << " -> ";
        data[i]->print();
    }
}

void Keeper::saveToFile(const char* filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        throw MyException("Error: Could not open file for writing!");
    }
    file << size << "\n";
    for (int i = 0; i < size; ++i) {
        file << data[i]->getType() << "\n";
        data[i]->saveToFile(file);
        file << "\n";
    }
    file.close();
    std::cout << "Successfully saved to " << filename << "\n";
}

void Keeper::loadFromFile(const char* filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw MyException("Error: Could not open file for reading!");
    }

    for (int i = 0; i < size; ++i) {
        delete data[i];
    }
    size = 0;

    int newSize;
    if (!(file >> newSize)) return;

    for (int i = 0; i < newSize; ++i) {
        char type[20];
        file >> type;
        Base* obj = nullptr;
        if (std::strcmp(type, "List") == 0) {
            obj = new ListQueue();
        }
        else if (std::strcmp(type, "Stack") == 0) {
            obj = new StackQueue();
        }
        else if (std::strcmp(type, "Deque") == 0) {
            obj = new DequeQueue();
        }
        if (obj) {
            obj->loadFromFile(file);
            add(obj);
        }
    }
    file.close();
    std::cout << "Successfully loaded from " << filename << "\n";
}