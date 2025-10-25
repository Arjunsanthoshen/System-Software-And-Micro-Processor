 
 #include <stdio.h>
int main() {
	int i, t = 0,idx = 0,timeline[100], pro[100],done,q,n;
	float awt = 0, atat = 0;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
	int p[n],bt[n],rbt[n],wt[n],tat[n];
	timeline[0] = 0;

    for (i = 0; i < n; i++) {
    	p[i] = i + 1;
        printf("Enter Burst time for p%d: ", i + 1);
        scanf("%d", &bt[i]);
        rbt[i] = bt[i];
    }

    printf("Enter time quantum: ");
    scanf("%d", &q);

	do {
        done = 1;
        for (i = 0; i < n; i++) {
            if (rbt[i] > 0) {
                done = 0;
				pro[idx] = p[i];
                if (rbt[i] > q) {   
                    t += q;
                    rbt[i] -= q;
                } else {
                    t += rbt[i];
                    tat[i] =t; 
                    wt[i] = t - bt[i]; 
                    rbt[i] = 0;
                }
                timeline[++idx] = t;
            }
        }
    } while (!done);
    
   printf("\nProcess ID\tBurst time\tWaiting time\tTurnaround time\n");
    for (i = 0; i < n; i++) {
        awt += wt[i];
        atat += tat[i];
        printf("P%d\t\t%d\t\t%d\t\t%d\n", p[i], bt[i],wt[i],tat[i]);
    }
    printf("\nAverage Waiting time = %.2f",awt / n);
    printf("\nAverage Turnaround time = %.2f\n",atat/ n);
    
	printf("\nGantt Chart:\n");
    for (i = 0; i < idx; i++) {
        printf("    P%d\t", pro[i]);
    }
    printf("\n");
    for (i = 0; i <= idx; i++) {
        printf("%d\t\t", timeline[i]);
    }
    printf("\n");
    return 0;
}  