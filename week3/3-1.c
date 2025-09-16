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

int removeMax() {
	int key = H[1];
	H[1] = H[n];
	n--;
	downHeap(1);
	return key;
}

void printHeap() {
	for (int i = 1; i <= n; i++) {
		printf(" %d", H[i]);
	}
	printf("\n");
}

int main() {
	while (1) {
		char c;
		scanf("%c", &c);

		if (c == 'i') {
			int k;
			scanf("%d", &k);
			insertItem(k);
			printf("0\n");
		} else if (c == 'd') {
			printf("%d", removeMax());
		} else if (c == 'p') {
			printHeap();
		} else if (c == 'q') {
			break;
		}
	}

	return 0;
}