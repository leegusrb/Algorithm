#include <stdio.h>

int H[100], n = 0;

void swap(int *p, int *q) {
	int tmp = *p;
	*p = *q;
	*q = tmp;
}

void upHeap(int i) {
	if (i == 1 || H[i] <= H[i / 2]) return;

	swap(&H[i], &H[i / 2]);
	upHeap(i / 2);
}

void insertItem(int key) {
	n++;
	H[n] = key;
	upHeap(n);
}

void downHeap(int i) {
	if (i * 2 > n) return;

	int larger = i * 2;
	if (i * 2 + 1 <= n && H[i * 2 + 1] > H[larger])
		larger = i * 2 + 1;

	if (H[i] >= H[larger]) return;

	swap(&H[i], &H[larger]);
	downHeap(larger);
}

void inPlaceHeapSort() {
	for (int i = n; n > 0; i--) {
		swap(&H[1], &H[i]);
		n--;
		downHeap(1);
	}
}

void printArray() {
	for (int i = 1; i <= n; i++) {
		printf(" %d", H[i]);
	}
	printf("\n");
}

int main() {
	int N;
	scanf("%d", &N);

	for (int i = 0; i < N; i++) {
		int k;
		scanf("%d", &k);
		insertItem(k);
	}

	inPlaceHeapSort();
	n = N;
	printArray();

	return 0;
}