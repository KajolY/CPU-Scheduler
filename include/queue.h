#ifndef QUEUE_H
#define QUEUE_H

#include "process.h"
#include <queue>
#include <vector>

class Queue
{
public:
    std::queue<Process> processes;
};

class PriorityQueue
{
public:
    std::priority_queue<Process, std::vector<Process>, std::greater<>> processes;
};

#endif // QUEUE_H