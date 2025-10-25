#include <stdio.h>
void main() {
    int n, temp;
    float awt = 0, atat = 0;
    printf("Enter the number of process: ");
    scanf("%d", &n);
    int bt[n], wt[n], tat[n], i, j, pro[n];
    for (i = 0; i < n; i++) {
        pro[i] = i + 1;
        printf("Enter the burst time of process p%d : ", i + 1);
        scanf("%d", &bt[i]);
    }
    printf("\nProcess ID\tBurst Time\n");
    for (i = 0; i < n; i++) {
        printf("p%d\t\t%d\n", pro[i], bt[i]);
    }

    for (i = 0; i < n; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (bt[j] > bt[j + 1]) {
                temp = bt[j];
                bt[j] = bt[j + 1];
                bt[j + 1] = temp;
                temp = pro[j];
                pro[j] = pro[j + 1];
                pro[j + 1] = temp;
            }
        }
    }

    wt[0] = 0;
    printf("\nProcess ID\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (i = 0; i < n; i++) {
        if (i != 0) {
            wt[i] = wt[i - 1] + bt[i - 1];
            awt += wt[i];
        }
        tat[i] = bt[i] + wt[i];
        atat += tat[i];
        printf("p%d\t\t%d\t\t%d\t\t\t%d\n", pro[i], bt[i], tat[i], wt[i]);
    }

    printf("\nAverage Waiting Time: %.2f\n", awt / n);
    printf("Average Turnaround Time: %.2f\n\n", atat / n);

    printf("Gantt Chart\n");
    for (i = 0; i < n; i++) {
        printf(" p%d\t", pro[i]);
    }
    printf("\n0");
    for (i = 0; i < n; i++) {
        printf("\t%d", tat[i]);
    }
    printf("\n");
}