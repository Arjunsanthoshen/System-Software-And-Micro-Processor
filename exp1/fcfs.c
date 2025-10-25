#include <stdio.h>

void main() {
    int n, i;
    float awt = 0, atat = 0;

    printf("Enter the number of process: ");
    scanf("%d", &n);

    int bt[n], wt[n], tat[n];

    for (i = 0; i < n; i++) {
        printf("Enter the burst time of process p%d: ", i + 1);
        scanf("%d", &bt[i]);
    }

    wt[0] = 0;

    printf("\nProcess ID\tBurst Time\tWaiting Time\tTurn Around Time\n");

    for (i = 0; i < n; i++) {
        if (i != 0)
            wt[i] = wt[i - 1] + bt[i - 1];
        tat[i] = bt[i] + wt[i];
        awt += wt[i];
        atat += tat[i];
        printf("p%d\t\t%d\t\t%d\t\t\t%d\n", i + 1, bt[i], wt[i], tat[i]);
    }

    printf("\nAverage Waiting Time: %.2f\n", awt / n);
    printf("Average Turnaround Time: %.2f\n", atat / n);

    printf("\nGantt Chart\n");
    for (i = 0; i < n; i++) {
        printf(" p%d\t", i + 1);
    }
    printf("\n0");
    for (i = 0; i < n; i++) {
        printf("\t%d", tat[i]);
    }
    printf("\n");
}2