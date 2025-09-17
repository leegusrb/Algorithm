#include <stdio.h>

int H[100], n = 0;

void swap(int *p, int *q) {
	int tmp = *p;
	*p = *q;
	*q = tmp;
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

void rBuildHeap(int i) {
	if (i > n / 2) return;

	rBuildHeap(i * 2);
	rBuildHeap(i * 2 + 1);
	downHeap(i);
}

void buildHeap() {
	for (int i = n / 2; i >= 1; i--) {
		downHeap(i);
	}
}

void printHeap() {
	for (int i = 1; i <= n; i++) {
		printf(" %d", H[i]);
	}
	printf("\n");
}

int main() {
	scanf("%d", &n);

	for (int i = 1; i <= n; i++) {
		scanf("%d", &H[i]);
	}

	rBuildHeap(1);
	// buildHeap();
	printHeap();

	return 0;
}