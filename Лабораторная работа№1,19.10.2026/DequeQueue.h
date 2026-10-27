#pragma once
#ifndef DEQUEQUEUE_H
#define DEQUEQUEUE_H
#include "Base.h"
#include "QueueNode.h"
class DequeQueue : public Base {
private:
    QueueNode* head;
    QueueNode* tail;
    int count;

public:
    DequeQueue();
    DequeQueue(const DequeQueue& other);
    ~DequeQueue() override;

    void push(int value) override; // Добавление в конец
    int pop() override;            // Удаление с начала
    void pushFront(int value);     // Добавление в начало
    int popBack();                 // Удаление с конца

    void print() const override;
    void saveToFile(std::ostream& os) const override;
    void loadFromFile(std::istream& is) override;
    const char* getType() const override { return "Deque"; }
};

#endif