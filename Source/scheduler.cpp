#include "scheduler.h"
#include <algorithm>
#include <queue>
#include <vector>

void scheduleFCFS(std::vector<Task> &tasks)
{
    std::sort(tasks.begin(), tasks.end(), [](Task a, Task b)
              { return a.arrivalTime < b.arrivalTime; });
    int currentTime = 0;
    for (auto &task : tasks)
    {
        task.startTime = std::max(currentTime, task.arrivalTime);
        task.endTime = task.startTime + task.burstTime;
        task.waitingTime = task.startTime - task.arrivalTime;
        task.turnaroundTime = task.endTime - task.arrivalTime;
        currentTime = task.endTime;
    }
}

void scheduleSJN(std::vector<Task> &tasks)
{
    std::sort(tasks.begin(), tasks.end(), [](Task a, Task b)
              { return a.arrivalTime < b.arrivalTime; });
    int currentTime = 0;
    std::vector<Task> readyQueue;
    std::vector<Task> result;

    while (!tasks.empty() || !readyQueue.empty())
    {
        while (!tasks.empty() && tasks.front().arrivalTime <= currentTime)
        {
            readyQueue.push_back(tasks.front());
            tasks.erase(tasks.begin());
        }
        if (!readyQueue.empty())
        {
            std::sort(readyQueue.begin(), readyQueue.end(), [](Task a, Task b)
                      { return a.burstTime < b.burstTime; });
            Task currentTask = readyQueue.front();
            readyQueue.erase(readyQueue.begin());
            currentTask.startTime = currentTime;
            currentTime += currentTask.burstTime;
            currentTask.endTime = currentTime;
            currentTask.waitingTime = currentTask.startTime - currentTask.arrivalTime;
            currentTask.turnaroundTime = currentTask.endTime - currentTask.arrivalTime;
            result.push_back(currentTask);
        }
        else
        {
            currentTime++;
        }
    }
    tasks = result;
}

void schedulePriority(std::vector<Task> &tasks)
{
    std::sort(tasks.begin(), tasks.end(), [](Task a, Task b)
              { return a.arrivalTime < b.arrivalTime; });
    int currentTime = 0;
    std::vector<Task> readyQueue;
    std::vector<Task> result;

    while (!tasks.empty() || !readyQueue.empty())
    {
        while (!tasks.empty() && tasks.front().arrivalTime <= currentTime)
        {
            readyQueue.push_back(tasks.front());
            tasks.erase(tasks.begin());
        }
        if (!readyQueue.empty())
        {
            std::sort(readyQueue.begin(), readyQueue.end(), [](Task a, Task b)
                      { return a.priority < b.priority; });
            Task currentTask = readyQueue.front();
            readyQueue.erase(readyQueue.begin());
            currentTask.startTime = currentTime;
            currentTime += currentTask.burstTime;
            currentTask.endTime = currentTime;
            currentTask.waitingTime = currentTask.startTime - currentTask.arrivalTime;
            currentTask.turnaroundTime = currentTask.endTime - currentTask.arrivalTime;
            result.push_back(currentTask);
        }
        else
        {
            currentTime++;
        }
    }
    tasks = result;
}

void scheduleRR(std::vector<Task> &tasks, int quantum)
{
    std::sort(tasks.begin(), tasks.end(), [](Task a, Task b)
              { return a.arrivalTime < b.arrivalTime; });
    std::queue<Task> readyQueue;
    int currentTime = 0;
    std::vector<Task> result;

    while (!tasks.empty() || !readyQueue.empty())
    {
        while (!tasks.empty() && tasks.front().arrivalTime <= currentTime)
        {
            readyQueue.push(tasks.front());
            tasks.erase(tasks.begin());
        }
        if (!readyQueue.empty())
        {
            Task currentTask = readyQueue.front();
            readyQueue.pop();
            if (currentTask.burstTime <= quantum)
            {
                currentTask.startTime = currentTime;
                currentTime += currentTask.burstTime;
                currentTask.endTime = currentTime;
                currentTask.waitingTime = currentTask.startTime - currentTask.arrivalTime;
                currentTask.turnaroundTime = currentTask.endTime - currentTask.arrivalTime;
                result.push_back(currentTask);
            }
            else
            {
                currentTask.startTime = currentTime;
                currentTime += quantum;
                currentTask.burstTime -= quantum;
                readyQueue.push(currentTask);
            }
        }
        else
        {
            currentTime++;
        }
    }
    tasks = result;
}

void scheduleMultilevelQueue(std::vector<Task> &tasks)
{
}
