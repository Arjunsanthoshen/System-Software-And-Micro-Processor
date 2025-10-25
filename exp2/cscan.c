#include <stdio.h> 
void bubbleSort(int arr[], int n) {
    int temp;
    for (int i=0; i<n-1; i++) {
        for (int j=0; j<n-i-1; j++) {
            if(arr[j] > arr[j+1]) {
                temp=arr[j];
                arr[j]=arr[j+1];
                arr[j+1]=temp;
            }
        }
    }
}

int main() {
    int head, n, size, seektime=0;
    printf("Enter Head position: ");
    scanf("%d", &head);
    
    printf("Enter number of disk requests: ");
    scanf("%d", &n);
    
    int a[n+1];
    
    printf("Enter the disk size: ");
    scanf("%d", &size);
    
    printf("Enter the disk requests: ");
    for (int i=0; i<n; i++) {
        scanf("%d", &a[i]);
    }
    
    a[n] = head;
    n++;
    
    bubbleSort(a, n);
    
    int pos = 0;
    for (int i=0; i<n; i++) {
        if(a[i] == head) {
            pos = i;
            break;
        }
    }
    
    printf("\n\tC-SCAN DISK SCHEDULING\n\n");
    
    for (int i=pos; i<n-1; i++) {
        int distance = a[i+1] - a[i];
        printf("Head movement from %d to %d : %d\n", a[i], a[i+1], distance);
        seektime += distance;
    }
    
    if (a[n-1] != size-1) {
        int distance = (size - 1) - a[n-1];
        printf("Head movement from %d to %d : %d\n", a[n-1], size -1, distance);
        seektime += distance;
    }
    
    printf("Head movement from %d to 0 : %d\n", size-1, size-1);
    seektime += size -1;
    
    for (int i=0; i<pos; i++) {
        int distance;
        if (i == 0)
            distance = a[i] - 0;
        else
            distance = a[i] - a[i-1];
            printf("Head movement from %d to %d : %d\n", i == 0 ? 0 : a[i-1], a[i], distance);
            seektime += distance;
    }
    
    printf("\nTotal seek time is : %d\n", seektime);
    return 0;
}