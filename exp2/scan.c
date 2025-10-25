#include <stdio.h> 
void bubbleSort(int arr[], int n) {
	int temp;
	for (int i = 0; i < n - 1; i++) {
		for (int j = 0; j < n - i - 1; j++) {
			if (arr[j] > arr[j + 1]) {
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
}
int main() {
	int head, n, size, seektime = 0;
	printf("Enter Head position: ");
	scanf("%d", &head);
	printf("Enter number of disk requests: ");
	scanf("%d", &n);
	printf("Enter the disk size: ");
	scanf("%d", &size);
	int a[n + 2];
	printf("Enter the disk requests: ");
	for (int i = 0; i < n; i++) {
		scanf("%d", &a[i]);
	}
	a[n] = head;
	a[n + 1] = size - 1;
	n += 2;
	bubbleSort(a, n);
	int pos;
	for (int i = 0; i < n; i++) {
		if (a[i] == head) {
			pos = i;
			break;
		}
	}
	printf("\n\tDISK REQUESTS\n\n");
	for (int i=0 ;i<n ; i++){
		printf("  %d ",a[i]);
	}
	printf("\n\n");
	printf("\n\tSCAN DISK SCHEDULING\n\n");

	for (int i = pos; i < n - 1; i++) {
    	int distance = a[i + 1] - a[i];
    	printf("Head movement from %d to %d : %d\n", a[i], a[i + 1], distance);
    	seektime += distance;
	}

	for (int i = pos; i > 0; i--) {
    	int distance = a[i] - a[i - 1];
	    printf("Head movement from %d to %d : %d\n", a[i], a[i - 1], distance);
    	seektime += distance;
	}

	printf("\nTotal seek time is: %d\n", seektime);
	return 0;
}