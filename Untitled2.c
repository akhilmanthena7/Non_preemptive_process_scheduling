#include <stdio.h>
#include <limits.h>

// Structure to represent a process
struct Process {
    int id;
    int estimatedRunTime;
    int waitingTime;
    int priority;
    int arrivalTime;
};

// Function to perform priority scheduling with arrival time
void priorityScheduling(struct Process processes[], int n) {
    int currentTime = 0;
    int totalWaitingTime = 0;

    for (int i = 0; i < n; i++) {
        processes[i].waitingTime = 0;
    }

    printf("\nGantt Chart:\n\n");

    while (1) {
        int highestPriorityIndex = -1;
        int highestPriority = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (processes[i].estimatedRunTime > 0 && processes[i].arrivalTime <= currentTime && processes[i].priority < highestPriority) {
                highestPriority = processes[i].priority;
                highestPriorityIndex = i;
            }
        }

        if (highestPriorityIndex == -1) {
            int nextArrival = INT_MAX;
            for (int i = 0; i < n; i++) {
                if (processes[i].estimatedRunTime > 0 && processes[i].arrivalTime < nextArrival) {
                    nextArrival = processes[i].arrivalTime;
                }
            }
            if (nextArrival == INT_MAX) {
                break;
            }
            currentTime = nextArrival;
            continue;
        }

        printf("Time %d: Process %d (Priority: %d)\n", currentTime, processes[highestPriorityIndex].id, processes[highestPriorityIndex].priority);

        // Execute the selected process
        processes[highestPriorityIndex].waitingTime = currentTime - processes[highestPriorityIndex].arrivalTime;
        totalWaitingTime += processes[highestPriorityIndex].waitingTime;
        currentTime += processes[highestPriorityIndex].estimatedRunTime;
        processes[highestPriorityIndex].estimatedRunTime = 0;
    }

    printf("\nProcess\tWaiting Time\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\n", processes[i].id, processes[i].waitingTime);
    }

    printf("\nAverage Waiting Time: %.2f\n", (float)totalWaitingTime / n);
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        printf("Enter estimated run time for Process %d: ", i + 1);
        scanf("%d", &processes[i].estimatedRunTime);
        printf("Enter arrival time for Process %d: ", i + 1);
        scanf("%d", &processes[i].arrivalTime);
        processes[i].priority = i + 1; // Set priorities as 1, 2, 3, 4
    }

    priorityScheduling(processes, n);

    return 0;
}
