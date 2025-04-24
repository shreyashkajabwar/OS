#include <bits/stdc++.h>
using namespace std;
class Process
{
public:
    string pid;
    int at;
    int bt;
    int ct;
    int wt;
    int tat;
    int priority;
    int remaining_bt;
};

bool compareAT(Process a, Process b)
{
    return a.at < b.at;
}

bool comparePriority(Process a, Process b)
{
    return a.priority < b.priority;
}

void calculateWaitingTimeAndTurnaroundTime(Process processes[], int n)
{
    int totalWT = 0, totalTAT = 0;

    cout << "\nPID\tArrival Time\tBurst Time\tCompletion Time\tWaiting Time\tTurnaround Time\n";
    for (int i = 0; i < n; i++)
    {
        processes[i].wt = processes[i].ct - processes[i].at - processes[i].bt;
        processes[i].tat = processes[i].wt + processes[i].bt;
        totalWT += processes[i].wt;
        totalTAT += processes[i].tat;
        cout << processes[i].pid << "\t" << processes[i].at << "\t\t" << processes[i].bt << "\t\t"
             << processes[i].ct << "\t\t" << processes[i].wt << "\t\t" << processes[i].tat << endl;
    }

    cout << "\nAverage Waiting Time: " << (float)totalWT / n << endl;
    cout << "Average Turnaround Time: " << (float)totalTAT / n << endl;
}

void FCFS(Process processes[], int n)
{
    sort(processes, processes + n, [](Process a, Process b)
         { return a.at < b.at; });
    int time = 0;

    for (int i = 0; i < n; i++)
    {
        if (time < processes[i].at)
        {
            time = processes[i].at;
        }
        processes[i].ct = time + processes[i].bt;
        time = processes[i].ct;
    }

    calculateWaitingTimeAndTurnaroundTime(processes, n);
}

void PriorityNonPreemptive(Process processes[], int n)
{
    sort(processes, processes + n, [](Process a, Process b)
         { return a.at < b.at; });
    int time = 0;

    for (int i = 0; i < n; i++)
    {
        Process selected;
        int highestPriority = INT_MAX;
        bool found = false;

        for (int j = 0; j < n; j++)
        {
            if (processes[j].at <= time && processes[j].ct == 0 && processes[j].priority < highestPriority)
            {
                highestPriority = processes[j].priority;
                selected = processes[j];
                found = true;
            }
        }

        if (found)
        {
            selected.ct = time + selected.bt;
            time = selected.ct;
            for (int j = 0; j < n; j++)
            {
                if (processes[j].pid == selected.pid)
                {
                    processes[j] = selected;
                    break;
                }
            }
        }
        else
        {
            time++;
        }
    }

    calculateWaitingTimeAndTurnaroundTime(processes, n);
}

void PriorityPreemptive(Process processes[], int n)
{
    sort(processes, processes + n, [](Process a, Process b)
         { return a.at < b.at; });
    int time = 0;
    int remainingProcesses = n;

    while (remainingProcesses > 0)
    {
        Process selected;
        int highestPriority = INT_MAX;
        bool found = false;

        for (int i = 0; i < n; i++)
        {
            if (processes[i].at <= time && processes[i].remaining_bt > 0 && processes[i].priority < highestPriority)
            {
                highestPriority = processes[i].priority;
                selected = processes[i];
                found = true;
            }
        }

        if (found)
        {
            selected.remaining_bt--;
            time++;
            if (selected.remaining_bt == 0)
            {
                selected.ct = time;
                remainingProcesses--;
            }
            for (int i = 0; i < n; i++)
            {
                if (processes[i].pid == selected.pid)
                {
                    processes[i] = selected;
                    break;
                }
            }
        }
        else
        {
            time++;
        }
    }

    calculateWaitingTimeAndTurnaroundTime(processes, n);
}
void SJFNonPreemptive(Process processes[], int n)
{
    sort(processes, processes + n, [](Process a, Process b)
         { return a.at < b.at; });
    int time = 0;

    for (int i = 0; i < n; i++)
    {
        Process selected;
        int shortestBT = INT_MAX;
        bool found = false;

        for (int j = 0; j < n; j++)
        {
            if (processes[j].at <= time && processes[j].ct == 0 && processes[j].bt < shortestBT)
            {
                shortestBT = processes[j].bt;
                selected = processes[j];
                found = true;
            }
        }

        if (found)
        {
            selected.ct = time + selected.bt;
            time = selected.ct;
            for (int j = 0; j < n; j++)
            {
                if (processes[j].pid == selected.pid)
                {
                    processes[j] = selected;
                    break;
                }
            }
        }
        else
        {
            time++;
        }
    }

    calculateWaitingTimeAndTurnaroundTime(processes, n);
}

void SJFPreemptive(Process processes[], int n)
{
    sort(processes, processes + n, [](Process a, Process b)
         { return a.at < b.at; });
    int time = 0;
    int remainingProcesses = n;

    while (remainingProcesses > 0)
    {
        Process selected;
        int shortestBT = INT_MAX;
        bool found = false;

        for (int i = 0; i < n; i++)
        {
            if (processes[i].at <= time && processes[i].remaining_bt > 0 &&
                processes[i].remaining_bt < shortestBT)
            {
                shortestBT = processes[i].remaining_bt;
                selected = processes[i];
                found = true;
            }
        }

        if (found)
        {
            selected.remaining_bt--;
            time++;
            if (selected.remaining_bt == 0)
            {
                selected.ct = time;
                remainingProcesses--;
            }
            for (int i = 0; i < n; i++)
            {
                if (processes[i].pid == selected.pid)
                {
                    processes[i] = selected;
                    break;
                }
            }
        }
        else
        {
            time++;
        }
    }

    calculateWaitingTimeAndTurnaroundTime(processes, n);
}

void RoundRobin(Process processes[], int n, int quantum)
{
    queue<int> readyQueue;
    int time = 0;
    int completed = 0;
    int remainingBT[n];
    bool inQueue[n] = {false};

    for (int i = 0; i < n; i++)
    {
        remainingBT[i] = processes[i].bt;
        processes[i].remaining_bt = processes[i].bt; // optional
    }

    sort(processes, processes + n, [](Process a, Process b)
         { return a.at < b.at; });

    readyQueue.push(0);
    inQueue[0] = true;
    time = processes[0].at;

    while (completed < n)
    {
        if (readyQueue.empty())
        {
            time++;
            for (int i = 0; i < n; i++)
            {
                if (!inQueue[i] && processes[i].at <= time)
                {
                    readyQueue.push(i);
                    inQueue[i] = true;
                }
            }
            continue;
        }

        int i = readyQueue.front();
        readyQueue.pop();

        int execTime = min(quantum, remainingBT[i]);
        time += execTime;
        remainingBT[i] -= execTime;

        for (int j = 0; j < n; j++)
        {
            if (!inQueue[j] && processes[j].at <= time)
            {
                readyQueue.push(j);
                inQueue[j] = true;
            }
        }

        if (remainingBT[i] > 0)
        {
            readyQueue.push(i);
        }
        else
        {
            processes[i].ct = time;
            completed++;
        }
    }

    calculateWaitingTimeAndTurnaroundTime(processes, n);
}

int main()
{
    int n, quantum, choice, schedulingType;

    cout << "Enter the number of processes: ";
    cin >> n;

    Process processes[n];
    for (int i = 0; i < n; i++)
    {
        cout << "\nEnter details for process " << i + 1 << ":\n";
        cout << "Process ID: ";
        cin >> processes[i].pid;
        cout << "Arrival Time: ";
        cin >> processes[i].at;
        cout << "Burst Time: ";
        cin >> processes[i].bt;
        cout << "Priority";
        cin >> processes[i].priority;
        processes[i].remaining_bt = processes[i].bt;
        processes[i].ct = 0;
    }

    do
    {
        cout << "\nMenu:\n";
        cout << "1. FCFS Scheduling\n";
        cout << "2. SJF Scheduling\n";
        cout << "3. Priority Scheduling\n";
        cout << "4. Round Robin Scheduling\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            FCFS(processes, n);
            break;
        case 2:
            cout << "Select Scheduling Type for SJF:\n";
            cout << "1. Non-preemptive\n";
            cout << "2. Preemptive\n";
            cin >> schedulingType;
            if (schedulingType == 1)
            {
                SJFNonPreemptive(processes, n);
            }
            else
            {
                SJFPreemptive(processes, n);
            }
            break;
        case 3:
            cout << "Select Scheduling Type for Priority Scheduling:\n";
            cout << "1. Non-preemptive\n";
            cout << "2. Preemptive\n";
            cin >> schedulingType;
            if (schedulingType == 1)
            {
                PriorityNonPreemptive(processes, n);
            }
            else
            {
                PriorityPreemptive(processes, n);
            }
            break;
        case 4:
            cout << "Enter Time Quantum: ";
            cin >> quantum;
            RoundRobin(processes, n, quantum);
            break;
        case 5:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 5);

    return 0;
}

/* Enter the number of processes: 4

Enter details for process 1:
Process ID: 1
Arrival Time: 1
Burst Time: 3
Priority1

Enter details for process 2:
Process ID: 2
Arrival Time: 2
Burst Time: 4
Priority1

Enter details for process 3:
Process ID: 3
Arrival Time: 1
Burst Time: 2
Priority3

Enter details for process 4:
Process ID: 4
Arrival Time: 4
Burst Time: 4
Priority4

Menu:
1. FCFS Scheduling
2. SJF Scheduling
3. Priority Scheduling
4. Round Robin Scheduling
5. Exit
Enter your choice: 3
Select Scheduling Type for Priority Scheduling:
1. Non-preemptive
2. Preemptive
2

PID	Arrival Time	Burst Time	Completion Time	Waiting Time	Turnaround Time
1	1		3		4		0		3
3	1		2		10		7		9
2	2		4		8		2		6
4	4		4		14		6		10

Average Waiting Time: 3.75
Average Turnaround Time: 7

Menu:
1. FCFS Scheduling
2. SJF Scheduling
3. Priority Scheduling
4. Round Robin Scheduling
5. Exit
Enter your choice: 4
Enter Time Quantum: 2

PID	Arrival Time	Burst Time	Completion Time	Waiting Time	Turnaround Time
1	1		3		9		5		8
3	1		2		4		1		3
2	2		4		11		5		9
4	4		4		13		5		9

Average Waiting Time: 4
Average Turnaround Time: 7.25

Menu:
1. FCFS Scheduling
2. SJF Scheduling
3. Priority Scheduling
4. Round Robin Scheduling
5. Exit
Enter your choice:  */