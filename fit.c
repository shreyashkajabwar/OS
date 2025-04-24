#include <stdio.h>

#define MAX 100

int blockSize[MAX], blockAllocated[MAX];
int processSize[MAX], processAllocated[MAX];
int lastIndex = 0;

void reset(int blocks, int processes) {
    for (int i = 0; i < blocks; i++) blockAllocated[i] = 0;
    for (int i = 0; i < processes; i++) processAllocated[i] = -1;
}

void firstFit(int blocks, int processes) {
    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < blocks; j++) {
            if (!blockAllocated[j] && blockSize[j] >= processSize[i]) {
                processAllocated[i] = j;
                blockAllocated[j] = 1;
                break;
            }
        }
    }
}

void bestFit(int blocks, int processes) {
    for (int i = 0; i < processes; i++) {
        int best = -1;
        for (int j = 0; j < blocks; j++) {
            if (!blockAllocated[j] && blockSize[j] >= processSize[i]) {
                if (best == -1 || blockSize[j] < blockSize[best])
                    best = j;
            }
        }
        if (best != -1) {
            processAllocated[i] = best;
            blockAllocated[best] = 1;
        }
    }
}

void worstFit(int blocks, int processes) {
    for (int i = 0; i < processes; i++) {
        int worst = -1;
        for (int j = 0; j < blocks; j++) {
            if (!blockAllocated[j] && blockSize[j] >= processSize[i]) {
                if (worst == -1 || blockSize[j] > blockSize[worst])
                    worst = j;
            }
        }
        if (worst != -1) {
            processAllocated[i] = worst;
            blockAllocated[worst] = 1;
        }
    }
}

void nextFit(int blocks, int processes) {
    for (int i = 0; i < processes; i++) {
        int count = 0, j = lastIndex;
        while (count < blocks) {
            if (!blockAllocated[j] && blockSize[j] >= processSize[i]) {
                processAllocated[i] = j;
                blockAllocated[j] = 1;
                lastIndex = (j + 1) % blocks;
                break;
            }
            j = (j + 1) % blocks;
            count++;
        }
    }
}

void showResult(int processes) {
    printf("\nProcess Allocation Results:\n");
    for (int i = 0; i < processes; i++) {
        printf("Process %d (Size %d) -> ", i + 1, processSize[i]);
        if (processAllocated[i] != -1)
            printf("Block %d\n", processAllocated[i] + 1);
        else
            printf("Not Allocated\n");
    }
}

int main() {
    int blocks, processes, choice;

    printf("Enter number of memory blocks: ");
    scanf("%d", &blocks);
    printf("Enter block sizes:\n");
    for (int i = 0; i < blocks; i++)
        scanf("%d", &blockSize[i]);

    printf("Enter number of processes: ");
    scanf("%d", &processes);
    printf("Enter process sizes:\n");
    for (int i = 0; i < processes; i++)
        scanf("%d", &processSize[i]);

    do {
        reset(blocks, processes);
        printf("\nMemory Allocation Techniques:\n");
        printf("1. First Fit\n2. Best Fit\n3. Worst Fit\n4. Next Fit\n5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: firstFit(blocks, processes); showResult(processes); break;
            case 2: bestFit(blocks, processes); showResult(processes); break;
            case 3: worstFit(blocks, processes); showResult(processes); break;
            case 4: nextFit(blocks, processes); showResult(processes); break;
            case 5: printf("Exiting...\n"); break;
            default: printf("Invalid choice!\n");
        }

    } while (choice != 5);

    return 0;
}

/*
Enter number of memory blocks: 5
Enter block sizes:
100 500 200 300 600
Enter number of processes: 4
Enter process sizes:
212 417 112 426 

Memory Allocation Techniques:
1. First Fit
2. Best Fit
3. Worst Fit
4. Next Fit
5. Exit
Enter your choice: 1

Process Allocation Results:
Process 1 (Size 212) -> Block 2
Process 2 (Size 417) -> Block 5
Process 3 (Size 112) -> Block 3
Process 4 (Size 426) -> Not Allocated

Memory Allocation Techniques:
1. First Fit
2. Best Fit
3. Worst Fit
4. Next Fit
5. Exit
Enter your choice: 2

Process Allocation Results:
Process 1 (Size 212) -> Block 4
Process 2 (Size 417) -> Block 2
Process 3 (Size 112) -> Block 3
Process 4 (Size 426) -> Block 5

Memory Allocation Techniques:
1. First Fit
2. Best Fit
3. Worst Fit
4. Next Fit
5. Exit
Enter your choice: 3

Process Allocation Results:
Process 1 (Size 212) -> Block 5
Process 2 (Size 417) -> Block 2
Process 3 (Size 112) -> Block 4
Process 4 (Size 426) -> Not Allocated

Memory Allocation Techniques:
1. First Fit
2. Best Fit
3. Worst Fit
4. Next Fit
5. Exit
Enter your choice: 4

Process Allocation Results:
Process 1 (Size 212) -> Block 2
Process 2 (Size 417) -> Block 5
Process 3 (Size 112) -> Block 3
Process 4 (Size 426) -> Not Allocated

Memory Allocation Techniques:
1. First Fit
2. Best Fit
3. Worst Fit
4. Next Fit
5. Exit
Enter your choice: 
*/