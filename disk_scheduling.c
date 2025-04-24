#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

int absolute(int a) {
    return (a < 0) ? -a : a;
}

void printSequence(int seq[], int size, int total) {
    printf("Sequence of head movement: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", seq[i]);
    }
    printf("\nTotal head movement: %d cylinders\n\n", total);
}

void fifo(int req[], int n, int head) {
    printf("FIFO (FCFS) Disk Scheduling:\n");
    int seq[MAX], total = 0;
    seq[0] = head;

    for (int i = 0; i < n; i++) {
        seq[i + 1] = req[i];
        total += absolute(seq[i + 1] - seq[i]);
    }

    printSequence(seq, n + 1, total);
}

void sstf(int req[], int n, int head) {
    printf("SSTF Disk Scheduling:\n");
    int seq[MAX], visited[MAX] = {0}, total = 0, current = head;
    seq[0] = head;

    for (int i = 1; i <= n; i++) {
        int minDist = 1e9, index = -1;
        for (int j = 0; j < n; j++) {
            if (!visited[j] && absolute(current - req[j]) < minDist) {
                minDist = absolute(current - req[j]);
                index = j;
            }
        }
        visited[index] = 1;
        total += minDist;
        current = req[index];
        seq[i] = current;
    }

    printSequence(seq, n + 1, total);
}

void sort(int arr[], int n) {
    for (int i = 0; i < n-1; i++)
        for (int j = i+1; j < n; j++)
            if (arr[i] > arr[j]) {
                int t = arr[i];
                arr[i] = arr[j];
                arr[j] = t;
            }
}

void scan(int req[], int n, int head, int diskSize, char dir[]) {
    printf("SCAN Disk Scheduling (%s direction):\n", dir);
    int sorted[MAX], seq[MAX], size = 0, total = 0;

    for (int i = 0; i < n; i++) sorted[i] = req[i];
    sort(sorted, n);

    seq[size++] = head;

    if (strcmp(dir, "left") == 0) {
        for (int i = n - 1; i >= 0; i--)
            if (sorted[i] <= head) seq[size++] = sorted[i];
        seq[size++] = 0;
        for (int i = 0; i < n; i++)
            if (sorted[i] > head) seq[size++] = sorted[i];
    } else {
        for (int i = 0; i < n; i++)
            if (sorted[i] >= head) seq[size++] = sorted[i];
        seq[size++] = diskSize - 1;
        for (int i = n - 1; i >= 0; i--)
            if (sorted[i] < head) seq[size++] = sorted[i];
    }

    for (int i = 1; i < size; i++)
        total += absolute(seq[i] - seq[i - 1]);

    printSequence(seq, size, total);
}

void cscan(int req[], int n, int head, int diskSize, char dir[]) {
    printf("C-SCAN Disk Scheduling (%s direction):\n", dir);
    int sorted[MAX], seq[MAX], size = 0, total = 0;

    for (int i = 0; i < n; i++) sorted[i] = req[i];
    sort(sorted, n);

    seq[size++] = head;

    if (strcmp(dir, "right") == 0) {
        for (int i = 0; i < n; i++)
            if (sorted[i] >= head) seq[size++] = sorted[i];
        seq[size++] = diskSize - 1;
        seq[size++] = 0;
        for (int i = 0; i < n; i++)
            if (sorted[i] < head) seq[size++] = sorted[i];
    } else {
        for (int i = n - 1; i >= 0; i--)
            if (sorted[i] <= head) seq[size++] = sorted[i];
        seq[size++] = 0;
        seq[size++] = diskSize - 1;
        for (int i = n - 1; i >= 0; i--)
            if (sorted[i] > head) seq[size++] = sorted[i];
    }

    for (int i = 1; i < size; i++)
        total += absolute(seq[i] - seq[i - 1]);

    printSequence(seq, size, total);
}

int main() {
    int requests[MAX], n, head, diskSize, choice;
    char dir[10];

    printf("Enter number of disk requests: ");
    scanf("%d", &n);

    printf("Enter disk requests:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &requests[i]);

    printf("Enter initial head position: ");
    scanf("%d", &head);

    printf("Enter total disk size (e.g. 200): ");
    scanf("%d", &diskSize);

    do {
        printf("\n=== Disk Scheduling Menu ===\n");
        printf("1. FIFO (FCFS)\n2. SSTF\n3. SCAN\n4. C-SCAN\n5. Exit\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1: fifo(requests, n, head); break;
        case 2: sstf(requests, n, head); break;
        case 3:
            printf("Enter direction (left/right): ");
            scanf("%s", dir);
            scan(requests, n, head, diskSize, dir);
            break;
        case 4:
            printf("Enter direction (left/right): ");
            scanf("%s", dir);
            cscan(requests, n, head, diskSize, dir);
            break;
        case 5: printf("Exiting program.\n"); break;
        default: printf("Invalid choice. Try again.\n");
        }
    } while (choice != 5);

    return 0;
}

/*
cd "/Users/shreyashkajabwar/Desktop/Operating System/" && gcc tempCodeRunnerFile.c -o tempCodeRunnerFile && "/Users/shreyashkajabwar/Desktop/Operating System/"tempCodeRunnerFile
shreyashkajabwar@Shreyashs-MacBook-Air ~ % cd "/Users/shreyashkajabwar/Desktop/Operating System/" && gcc tempCodeRunnerFile.c -o tempCodeRunnerFile && "/User
s/shreyashkajabwar/Desktop/Operating System/"tempCodeRunnerFile
Enter number of disk requests: 7
Enter disk requests:
82
170
43
140
24
16
190
Enter initial head position: 50
Enter total disk size (e.g. 200): 200

=== Disk Scheduling Menu ===
1. FIFO (FCFS)
2. SSTF
3. SCAN
4. C-SCAN
5. Exit
Enter your choice: 1
FIFO (FCFS) Disk Scheduling:
Sequence of head movement: 50 82 170 43 140 24 16 190 
Total head movement: 642 cylinders


=== Disk Scheduling Menu ===
1. FIFO (FCFS)
2. SSTF
3. SCAN
4. C-SCAN
5. Exit
Enter your choice: 2
SSTF Disk Scheduling:
Sequence of head movement: 50 43 24 16 82 140 170 190 
Total head movement: 208 cylinders


=== Disk Scheduling Menu ===
1. FIFO (FCFS)
2. SSTF
3. SCAN
4. C-SCAN
5. Exit
Enter your choice: 3
Enter direction (left/right): left
SCAN Disk Scheduling (left direction):
Sequence of head movement: 50 43 24 16 0 82 140 170 190 
Total head movement: 240 cylinders


=== Disk Scheduling Menu ===
1. FIFO (FCFS)
2. SSTF
3. SCAN
4. C-SCAN
5. Exit
Enter your choice: 3
Enter direction (left/right): right
SCAN Disk Scheduling (right direction):
Sequence of head movement: 50 82 140 170 190 199 43 24 16 
Total head movement: 332 cylinders


=== Disk Scheduling Menu ===
1. FIFO (FCFS)
2. SSTF
3. SCAN
4. C-SCAN
5. Exit
Enter your choice: 4
Enter direction (left/right): left
C-SCAN Disk Scheduling (left direction):
Sequence of head movement: 50 43 24 16 0 199 190 170 140 82 
Total head movement: 366 cylinders


=== Disk Scheduling Menu ===
1. FIFO (FCFS)
2. SSTF
3. SCAN
4. C-SCAN
5. Exit
Enter your choice: 4
Enter direction (left/right): rigth
C-SCAN Disk Scheduling (rigth direction):
Sequence of head movement: 50 43 24 16 0 199 190 170 140 82 
Total head movement: 366 cylinders


=== Disk Scheduling Menu ===
1. FIFO (FCFS)
2. SSTF
3. SCAN
4. C-SCAN
5. Exit
Enter your choice: */