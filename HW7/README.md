# HW7: Process Scheduling Simulation (FCFS & SJF)

## How to Run

Compile:
```
gcc -o scheduler scheduler.c
```

Run:
```
./scheduler
```

The program will prompt for the number of processes, then ask for each process's arrival time and burst time.

## Example

```
Enter the number of processes: 4
Enter the arrival time and burst time for process 1: 0 8
Enter the arrival time and burst time for process 2: 1 4
Enter the arrival time and burst time for process 3: 2 9
Enter the arrival time and burst time for process 4: 3 5
```

Output shows FCFS and SJF results with Gantt charts, per-process metrics, and averages.
