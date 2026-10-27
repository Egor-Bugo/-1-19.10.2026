#pragma once
#ifndef BASE_H
#define BASE_H
#include <iostream>
class Base {
public:
    Base() {
        std::cout << "[Base Constructor] Base object created.\n";
    }

    virtual ~Base() {
        std::cout << "[Base Destructor] Base object destroyed.\n";
    }
        virtual void push(int value) = 0;
    virtual int pop() = 0;
    virtual void print() const = 0;
    virtual void saveToFile(std::ostream& os) const = 0;
    virtual void loadFromFile(std::istream& is) = 0;
    virtual const char* getType() const = 0;
};

#endif