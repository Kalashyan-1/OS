#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int pid;
    int arrival_time;
    int burst_time;
    int turnaround_time;
    int waiting_time;
    int response_time;
} Process;

int compare_arrival(const void* a, const void* b) {
    const Process *pa = (const Process *)a;
    const Process *pb = (const Process *)b;
    if (pa->arrival_time != pb->arrival_time)
        return pa->arrival_time - pb->arrival_time;
    return pa->pid - pb->pid;
}

void print_results(Process* order, int n, const char* title) {
    printf("%s\n", title);

    printf("Gantt Chart: ");
    for (int i = 0; i < n; i++)
        printf("| P%d ", order[i].pid);
    printf("|\n");

    printf("%-8s%-8s%-8s%-8s%-8s%-8s\n", "PID", "AT", "BT", "WT", "TAT", "RT");

    double sum_wt = 0, sum_tat = 0, sum_rt = 0;
    for (int i = 0; i < n; i++) {
        printf("%-8d%-8d%-8d%-8d%-8d%-8d\n",
               order[i].pid, order[i].arrival_time, order[i].burst_time,
               order[i].waiting_time, order[i].turnaround_time,
               order[i].response_time);
        sum_wt += order[i].waiting_time;
        sum_tat += order[i].turnaround_time;
        sum_rt += order[i].response_time;
    }

    printf("\nAverage Waiting Time: %.2f\n", sum_wt / n);
    printf("Average Turnaround Time: %.2f\n", sum_tat / n);
    printf("Average Response Time: %.2f\n\n", sum_rt / n);
}

void fcfs(Process* procs, int n) {
    Process *order = malloc(n * sizeof(Process));
    if (order == NULL) {
        fprintf(stderr, "Memory allocation failed in fcfs\n");
        return;
    }
    memcpy(order, procs, n * sizeof(Process));

    qsort(order, n, sizeof(Process), compare_arrival);

    int current_time = 0;
    for (int i = 0; i < n; i++) {
        if (current_time < order[i].arrival_time)
            current_time = order[i].arrival_time;

        order[i].waiting_time = current_time - order[i].arrival_time;
        order[i].response_time = order[i].waiting_time;
        current_time += order[i].burst_time;
        order[i].turnaround_time = current_time - order[i].arrival_time;
    }

    print_results(order, n, "First Come First Served (FCFS)");
    free(order);
    order = NULL;
}

void sjf(Process* procs, int n) {
    Process *order = malloc(n * sizeof(Process));
    int *completed = calloc(n, sizeof(int));
    Process *sorted = malloc(n * sizeof(Process));

    if (order == NULL || completed == NULL || sorted == NULL) {
        fprintf(stderr, "Memory allocation failed in sjf\n");
        free(order);
        order = NULL;
        free(completed);
        completed = NULL;
        free(sorted);
        sorted = NULL;
        return;
    }

    memcpy(sorted, procs, n * sizeof(Process));
    qsort(sorted, n, sizeof(Process), compare_arrival);

    int current_time = 0;
    int done = 0;

    while (done < n) {
        int best = -1;
        int earliest_arrival = -1;

        for (int i = 0; i < n; i++) {
            if (completed[i])
                continue;
            if (sorted[i].arrival_time > current_time) {
                if (earliest_arrival == -1 || sorted[i].arrival_time < earliest_arrival)
                    earliest_arrival = sorted[i].arrival_time;
                continue;
            }
            if (best == -1 || sorted[i].burst_time < sorted[best].burst_time ||
                (sorted[i].burst_time == sorted[best].burst_time &&
                 sorted[i].arrival_time < sorted[best].arrival_time))
                best = i;
        }

        if (best == -1) {
            current_time = earliest_arrival;
            continue;
        }

        sorted[best].waiting_time = current_time - sorted[best].arrival_time;
        sorted[best].response_time = sorted[best].waiting_time;
        current_time += sorted[best].burst_time;
        sorted[best].turnaround_time = current_time - sorted[best].arrival_time;

        order[done] = sorted[best];
        completed[best] = 1;
        done++;
    }

    print_results(order, n, "Shortest Job First (SJF)");
    free(order);
    order = NULL;
    free(completed);
    completed = NULL;
    free(sorted);
    sorted = NULL;
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        fprintf(stderr, "Invalid number of processes\n");
        return 1;
    }

    Process* procs = malloc(n * sizeof(Process));
    if (procs == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        procs[i].pid = i + 1;
        printf("Enter the arrival time and burst time for process %d: ", i + 1);
        if (scanf("%d %d", &procs[i].arrival_time, &procs[i].burst_time) != 2) {
            fprintf(stderr, "Invalid input for process %d\n", i + 1);
            free(procs);
            procs = NULL;
            return 1;
        }
    }

    printf("\n");
    fcfs(procs, n);
    sjf(procs, n);

    free(procs);
    procs = NULL;
    return 0;
}
