#include <stdio.h>
#include <stdlib.h>

void swap(int *p, int *q) {
	int tmp = *p;
	*p = *q;
	*q = tmp;
}

void inPlaceSelectionSort(int *arr, int n) {
	for (int i = n - 1; i > 0; i--) {
		int mxIdx = 0;
		for (int j = 0; j <= i; j++) {
			if (arr[j] > arr[mxIdx])
				mxIdx = j;
		}
		swap(arr + i, arr + mxIdx);
	}
}

int main() {
	int n;
	scanf("%d", &n);

	int *arr = (int *) malloc(sizeof(int) * n);

	for (int i = 0; i < n; i++)
		scanf("%d", &arr[i]);

	inPlaceSelectionSort(arr, n);

	for (int i = 0; i < n; i++)
		printf(" %d", arr[i]);
	printf("\n");

	return 0;
}