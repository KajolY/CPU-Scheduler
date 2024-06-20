#ifndef PROCESS_H
#define PROCESS_H

struct Process
{
    int pid;
    int priority;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int start_time;
    int completion_time;
};

#endif // PROCESS_H
