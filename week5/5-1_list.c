#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	int elem;
	struct Node *next;
} Node;

Node *init() {
	Node *node = (Node *) malloc(sizeof(Node));
	node->next = NULL;

	return node;
}

int listSize(Node *L) {
	int size = 0;
	while (L->next) {
		size++;
		L = L->next;
	}
	return size;
}

void insertNode(Node *L, int e) {
	Node *node = (Node *) malloc(sizeof(Node));
	node->elem = e;

	Node *p = L;
	while (p->next)
		p = p->next;

	p->next = node;
}

Node *partition(Node *L, int k) {
	Node *L2 = init();

	Node *p = L;
	for (int i = 0; i < k; i++)
		p = p->next;

	L2->next = p->next;
	p->next = NULL;

	return L2;
}

Node *merge(Node *L1, Node *L2) {
	Node *L = init();

	Node *p = L;
	while (L1 && L2) {
		if (L1->elem < L2->elem) {
			p->next = L1;
			L1 = L1->next;
		} else {
			p->next = L2;
			L2 = L2->next;
		}
		p = p->next;
	}

	while (L1) {
		p->next = L1;
		L1 = L1->next;
		p = p->next;
	}

	while (L2) {
		p->next = L2;
		L2 = L2->next;
		p = p->next;
	}

	return L;
}

void mergeSort(Node *L) {
	int size = listSize(L);

	if (size > 1) {
		Node *L2 = partition(L, size / 2);
		Node *L1 = L;
		mergeSort(L1);
		mergeSort(L2);
		L = merge(L1, L2);
	}
}

int main() {
	int n;
	scanf("%d", &n);

	Node *L = init();
	
	for (int i = 0; i < n; i++) {
		int e;
		scanf("%d", &e);
		insertNode(L, e);
	}

	mergeSort(L);

	while (L->next) {
		L = L->next;
		printf(" %d", L->elem);
	}

	return 0;
}
