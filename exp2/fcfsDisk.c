#include <stdio.h>
int main(){
	int i,n,seektime=0,distance,head;
	printf("enter the head position :");
	scanf("%d",&head);
	
	printf("enter the number of request :");
	scanf("%d",&n);
	int a[n];
	
	printf("enter the disk request :");
	for(i=1; i<=n ;i++){
		scanf("%d",&a[i]);
	}
	a[0]=head;
	
	printf("\n\tfcfs disk schdeuling\n\n");
	for(i=0;i<n;i++){
		distance =(a[i]>a[i+1])? a[i]-a[i+1] : a[i+1]-a[i];
		printf("head movement from %d to %d :%d\n",a[i],a[i+1],distance);
		seektime+=distance;
	}
	printf("\ntotal seek time : %d\n", seektime);
	return 0;
}
