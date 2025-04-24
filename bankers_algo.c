#include <stdio.h>
#include <stdbool.h>

#define MAX_P 10
#define MAX_R 10

int main() {
    int n, m;
    int alloc[MAX_P][MAX_R], maxNeed[MAX_P][MAX_R], need[MAX_P][MAX_R];
    int avail[MAX_R], work[MAX_R], safeSeq[MAX_P];
    bool finish[MAX_P] = {false};

    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter number of resources: ");
    scanf("%d", &m);

    printf("\nEnter Allocation Matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &alloc[i][j]);

    printf("\nEnter Maximum Need Matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &maxNeed[i][j]);

    printf("\nEnter Available Resources:\n");
    for (int i = 0; i < m; i++) {
        scanf("%d", &avail[i]);
        work[i] = avail[i]; // Initialize work
    }

    // Calculate need matrix
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            need[i][j] = maxNeed[i][j] - alloc[i][j];

    int count = 0;
    while (count < n) {
        bool found = false;
        for (int i = 0; i < n; i++) {
            if (!finish[i]) {
                bool canRun = true;
                for (int j = 0; j < m; j++) {
                    if (need[i][j] > work[j]) {
                        canRun = false;
                        break;
                    }
                }
                if (canRun) {
                    for (int j = 0; j < m; j++)
                        work[j] += alloc[i][j];
                    safeSeq[count++] = i;
                    finish[i] = true;
                    found = true;
                }
            }
        }
        if (!found) {
            printf("\nThe system is NOT in a safe state.\n");
            return 0;
        }
    }

    printf("\nThe system is in a SAFE state.\nSafe sequence: ");
    for (int i = 0; i < n; i++)
        printf("P%d ", safeSeq[i]);
    printf("\n");

    return 0;
}
/*
Enter number of processes: 4
Enter number of resource types: 3
Enter available resources: 3 3 4
Enter maximum resource matrix: 
7 5 3
3 2 2
9 0 2
2 2 2
Enter allocated resource matrix: 
0 1 0
2 0 0
3 0 2
2 1 1
*/