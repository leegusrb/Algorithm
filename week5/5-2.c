#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Pair {
	int a, b;
} Pair;

void swap(int *a, int *b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

int find_pivot_index(int *arr, int l, int r) {
	srand(time(NULL));

	int idx[3];
	int n[3];
	for (int i = 0; i < 3; i++) {
		idx[i] = rand() % (r - l + 1) + l;
		n[i] = arr[idx[i]];
	}

	if ((n[1] <= n[0]) && (n[0] <= n[2]) || (n[2] <= n[0]) && n[0] <= n[1])
		return idx[0];
	if ((n[0] <= n[1]) && (n[1] <= n[2]) || (n[2] <= n[1]) && n[1] <= n[0])
		return idx[1];
	return idx[2];
}

Pair inPlacePartition(int *arr, int l, int r, int k) {
	Pair P;

	swap(&arr[k], &arr[r]);

	int p = arr[r];
	int i = l;
	int j = r - 1;
	while (i <= j) {
		while (i <= j && arr[i] < p)
			i++;
		while (i <= j && arr[j] >= p)
			j--;

		if (i < j)
			swap(&arr[i], &arr[j]);
	}

	P.a = i;
	j = r - 1;

	while (i <= j) {
		while (i <= j && arr[i] == p)
			i++;
		while (i <= j && arr[j] > p)
			j--;

		if (i < j)
			swap(&arr[i], &arr[j]);
	}

	swap(&arr[i], &arr[r]);
	P.b = i;

	return P;
}

void inPlaceQuickSort(int *arr, int l, int r) {
	if (l >= r) return;

	int k = find_pivot_index(arr, l, r);
	Pair P = inPlacePartition(arr, l, r, k);
	inPlaceQuickSort(arr, l, P.a - 1);
	inPlaceQuickSort(arr, P.b + 1, r);
}

int main() {
	int N;
	scanf("%d", &N);

	int *arr = (int *) malloc(sizeof(int) * N);

	for (int i = 0; i < N; i++)
		scanf("%d", &arr[i]);

	inPlaceQuickSort(arr, 0, N - 1);

	for (int i = 0; i < N; i++)
		printf("%d ", arr[i]);

	return 0;
}