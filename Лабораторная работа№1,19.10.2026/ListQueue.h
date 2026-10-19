#pragma once
#ifndef LISTQUEUE_H
#define LISTQUEUE_H

#include "Base.h"
#include "QueueNode.h"

class ListQueue : public Base {
private:
    QueueNode* head;
    QueueNode* tail;
    int count;

public:
    ListQueue();
    ListQueue(const ListQueue& other);
    ~ListQueue() override;

    void push(int value) override; // Добавление в конец списка
    int pop() override;            // Удаление с начала
    void print() const override;
    void saveToFile(std::ostream& os) const override;
    void loadFromFile(std::istream& is) override;
    const char* getType() const override { return "List"; }
};

#endif