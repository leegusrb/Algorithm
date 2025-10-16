#include <stdio.h>
#include <stdlib.h>

int n;

void merge(int *A, int l, int m, int r) {
	int i = l, k = l, j = m + 1;
	int *B = (int *) malloc(sizeof(int) * n);

	while (i <= m && j <= r) {
		if (A[i] <= A[j]) {
			B[k++] = A[i++];
		} else {
			B[k++] = A[j++];
		}
	}

	while (i <= m)
		B[k++] = A[i++];

	while (j <= r)
		B[k++] = A[j++];

	for (k = l; k <= r; k++) {
		A[k] = B[k];
	}
}

void mergeSort(int *A, int l, int r) {
	if (l < r) {
		int m = (l + r) / 2;
		mergeSort(A, l, m);
		mergeSort(A, m + 1, r);
		merge(A, l, m, r);
	}
}

int main() {
	scanf("%d", &n);

	int *A = (int *) malloc(sizeof(int) * n);

	for (int i = 0; i < n; i++) {
		scanf("%d", &A[i]);
	}

	mergeSort(A, 0, n - 1);

	for (int i = 0; i < n; i++) {
		printf(" %d", A[i]);
	}

	return 0;
}
