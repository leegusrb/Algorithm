#include <stdio.h>
#include <stdlib.h>

void swap(int *p, int *q) {
	int tmp = *p;
	*p = *q;
	*q = tmp;
}

void inPlaceInsertionSort(int *arr, int n) {
	for (int i = 1; i < n; i++) {
		for (int j = i; j >= 0 && arr[j] < arr[j - 1]; j--)
			swap(arr + j, arr + j - 1);
	}
}

int main() {
	int n;
	scanf("%d", &n);

	int *arr = (int *) malloc(sizeof(int) * n);

	for (int i = 0; i < n; i++)
		scanf("%d", &arr[i]);

	inPlaceInsertionSort(arr, n);

	for (int i = 0; i < n; i++)
		printf(" %d", arr[i]);
	printf("\n");

	return 0;
}