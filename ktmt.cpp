#include<stdio.h>
int isPrime(int n) {
	if (n <= 1) return 0;
	for (int i = 2; i < n; i++) {
		if (n%i == 0) { return 0; }
	}
	return 1;
}

int FindPrimeMax(int arr[],int size) {
	int max = 0;
	for (int i = 0; i < size; i++) {
		if (isPrime(arr[i])==1) {
			if (arr[i] > max) {
				max = arr[i];
			}
		}
	}
	if (max != 0) { return max; }
	else return -1;
}

int main() {
	
	int arr[6] = {0,13,6,1,4,2};
	printf("%d",FindPrimeMax(arr,6));
	return 0;
}

