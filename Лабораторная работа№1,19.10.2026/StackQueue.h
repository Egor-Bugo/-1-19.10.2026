#pragma once
#ifndef STACKQUEUE_H
#define STACKQUEUE_H

#include "Base.h"
#include "QueueNode.h"

class StackQueue : public Base {
private:
    QueueNode* topNode;
    int count;

public:
    StackQueue();
    StackQueue(const StackQueue& other);
    ~StackQueue() override;

    void push(int value) override; // Добавление на вершину (LIFO на базе очереди)
    int pop() override;            // Удаление с вершины
    void print() const override;
    void saveToFile(std::ostream& os) const override;
    void loadFromFile(std::istream& is) override;
    const char* getType() const override { return "Stack"; }
};

#endif