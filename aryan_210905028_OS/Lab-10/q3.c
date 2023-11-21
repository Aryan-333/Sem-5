#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
// Define the DSA structure
struct DSA {
    int request_id;
    int arrival_time_stamp;
    int cylinder;
    int address;
    int process_id;
};

// Compare function for sorting by cylinder
int compareCylinder(const void* a, const void* b) {
    return ((struct DSA*)a)->cylinder - ((struct DSA*)b)->cylinder;
}

// First-Come, First-Served (FCFS) Disk Scheduling
void fcfs(struct DSA requests[], int n) {
    int current_position = 0;
    int total_movement = 0;
    int val;
    for (int i = 0; i < n; i++) {
        total_movement += (val=abs(requests[i].cylinder - current_position));
        current_position = requests[i].cylinder;
        printf("Move from %d to %d in time %d units\n",current_position,requests[i].cylinder,val);
    }
    printf("FCFS Total seek time: %d units\n", total_movement);
    printf("FCFS Average seek time: %.3f units\n",((float)total_movement/n));
}

// Shortest Seek Time First (SSTF) Disk Scheduling
void sstf(struct DSA requests[], int n) {
    int current_position = 0;
    int total_movement = 0;
    bool processed[n];
    for (int i = 0; i < n; i++) {
        processed[i] = false;
    }

    for (int i = 0; i < n; i++) {
        int min_seek = INT_MAX;
        int next_request = -1;

        for (int j = 0; j < n; j++) {
            if (!processed[j]) {
                int seek = abs(requests[j].cylinder - current_position);
                if (seek < min_seek) {
                    min_seek = seek;
                    next_request = j;
                }
            }
        }
        printf("Move %d to %d in time %d units\n",current_position,requests[next_request].cylinder,min_seek);
        processed[next_request] = true;
        total_movement += min_seek;
        current_position = requests[next_request].cylinder;
    }
    printf("SSTF Total seek time: %d units\n", total_movement);
    printf("SSTF Average seek time: %.3f units\n",((float)total_movement/n));
}

int main() {
    // Create an array of disk requests
    int n;
    printf("Number of requests: ");
    scanf("%d",&n);
    printf("Enter request parameters: ");
    struct DSA requests[n];
    for(int i=0;i<n;i++){
    	scanf("%d%d%d%d%d",&requests[i].request_id,&requests[i].arrival_time_stamp,&requests[i].cylinder,&requests[i].address,&requests[i].process_id);
    }
    /*struct DSA requests[] = {
        {1, 0, 50, 100, 1},
        {2, 2, 25, 200, 2},
        {3, 4, 75, 300, 3},
        {4, 6, 10, 400, 4},
        {5, 8, 90, 500, 5}
    };*/

    //int n = sizeof(requests) / sizeof(requests[0]);

    fcfs(requests, n);

    // Sort the requests by cylinder for SSTF
    qsort(requests, n, sizeof(struct DSA), compareCylinder);

    sstf(requests, n);

    return 0;
}