#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "process.h"
#include "queue.h"
#include <vector>
#include <string>

class Scheduler
{
public:
    void fcfs_schedule(Queue &queue);
    void round_robin_schedule(Queue &queue, int time_quantum);
    void priority_schedule(PriorityQueue &queue);
    void multilevel_feedback_queue_schedule(std::vector<Queue> &queues, int num_queues);
    std::string get_stats_json() const;

private:
    void calculate_stats(std::vector<Process> &completed_processes);
    double avg_wait_time;
    double avg_turnaround_time;
    double cpu_utilization;
};

#endif // SCHEDULER_H
