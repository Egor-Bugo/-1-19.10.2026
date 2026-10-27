#pragma once
#ifndef KEEPER_H
#define KEEPER_H
#include "Base.h"
class Keeper {
private:
    Base** data;
    int size;
    int capacity;

    void resize(int newCapacity);

public:
    Keeper();
    Keeper(const Keeper& other);
    ~Keeper();

    void add(Base* obj);
    void remove(int index);
    Base* get(int index) const;
    int getSize() const;

    void printAll() const;
    void saveToFile(const char* filename) const;
    void loadFromFile(const char* filename);

    Keeper& operator=(const Keeper& other);
};

#endif