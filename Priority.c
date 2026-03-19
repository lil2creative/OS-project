#include <stdio.h>

struct Process {
    char pid[10];
    int at, bt, pr;
    int rt, ct, wt, tat;
};

int main() {
    int n, i, time = 0, completed = 0, max_pr, idx;

    scanf("%d", &n);

    struct Process p[n];

    // Input
    for(i = 0; i < n; i++) {
        scanf("%s %d %d %d", p[i].pid, &p[i].at, &p[i].bt, &p[i].pr);
        p[i].rt = p[i].bt; // remaining time = burst time
    }

    // Priority Scheduling (Preemptive)
    while(completed < n) {
        max_pr = -1;
        idx = -1;

        for(i = 0; i < n; i++) {
            if(p[i].at <= time && p[i].rt > 0) {
                if(p[i].pr > max_pr) {
                    max_pr = p[i].pr;
                    idx = i;
                }
            }
        }

        if(idx != -1) {
            p[idx].rt--;

            if(p[idx].rt == 0) {
                p[idx].ct = time + 1;
                completed++;
            }
        }

        time++;
    }

    float total_wt = 0, total_tat = 0;

    // Calculate WT and TAT
    for(i = 0; i < n; i++) {
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;

        total_wt += p[i].wt;
        total_tat += p[i].tat;
    }

    // Output
    printf("Waiting Time:\n");
    for(i = 0; i < n; i++)
        printf("%s %d\n", p[i].pid, p[i].wt);

    printf("Turnaround Time:\n");
    for(i = 0; i < n; i++)
        printf("%s %d\n", p[i].pid, p[i].tat);

    printf("Average Waiting Time: %.2f\n", total_wt / n);
    printf("Average Turnaround Time: %.2f\n", total_tat / n);

    return 0;
}
