#include <iostream>
#include <vector>
#include "scheduler.h"

void printTasks(const std::vector<Task> &tasks)
{
    for (const auto &task : tasks)
    {
        std::cout << "Task " << task.id << ": "
                  << "Start Time = " << task.startTime << ", "
                  << "End Time = " << task.endTime << ", "
                  << "Waiting Time = " << task.waitingTime << ", "
                  << "Turnaround Time = " << task.turnaroundTime << "\n";
    }
}

int main()
{
    std::vector<Task> tasks = {
        {1, 0, 5, 1, 0, 0, 0, 0},
        {2, 2, 3, 2, 0, 0, 0, 0},
        {3, 4, 1, 3, 0, 0, 0, 0}};

    int choice;
    std::cout << "Choose Scheduling Algorithm:\n";
    std::cout << "1. FCFS\n";
    std::cout << "2. SJN\n";
    std::cout << "3. Priority\n";
    std::cout << "4. Round Robin\n";
    std::cout << "5. Multilevel Queue\n";
    std::cin >> choice;

    switch (choice)
    {
    case 1:
        scheduleFCFS(tasks);
        break;
    case 2:
        scheduleSJN(tasks);
        break;
    case 3:
        schedulePriority(tasks);
        break;
    case 4:
        int quantum;
        std::cout << "Enter time quantum: ";
        std::cin >> quantum;
        scheduleRR(tasks, quantum);
        break;
    case 5:
        scheduleMultilevelQueue(tasks);
        break;
    default:
        std::cout << "Invalid choice.\n";
        return 1;
    }

    printTasks(tasks);

    return 0;
}
