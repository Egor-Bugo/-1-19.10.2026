#pragma once
#ifndef QUEUENODE_H
#define QUEUENODE_H

struct QueueNode {
    int data;
    QueueNode* next;
    QueueNode(int val) : data(val), next(nullptr) {}
};

#endif