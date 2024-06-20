#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <vector.h>

struct Task
{
    int id;
    int arrivalTime;
    int burstTime;
    int priority;
    int startTime;
    int endTime;
    int waitingTime;
    int turnaroundTime;
};

void scheduleFCFS(std::vector<Task> &tasks);
void scheduleSJN(std::vector<Task> &tasks);
void schedulePriority(std::vector<Task> &tasks);
void scheduleRR(std::vector<Task> &tasks, int quantum);
void scheduleMultilevelQueue(std::vector<Task> &tasks);

#endif // SCHEDULER_H
