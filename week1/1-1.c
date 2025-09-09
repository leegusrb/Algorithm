#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	char elem;
	struct Node *prev, *next;
} Node;

int length = 0;

void add(Node *list, int r, char e) {
	if (r > length + 1) {
		printf("invalid position\n");
		return;
	}

	Node *node = (Node *) malloc(sizeof(Node));
	node->elem = e;
	node->prev = NULL;
	node->next = NULL;

	Node *p = list;
	for (int i = 0; i < r - 1; i++)
		p = p->next;

	Node *prev = p;
	Node *next = p->next;

	prev->next = node;
	node->prev = prev;

	node->next = next;
	next->prev = node;

	length++;
}

char delete(Node *list, int r) {
	if (r > length) {
		printf("invalid position\n");
		return 0;
	}

	Node *p = list;

	for (int i = 0; i < r; i++)
		p = p->next;

	Node *prev = p->prev;
	Node *next = p->next;

	prev->next = next;
	next->prev = prev;

	char e = p->elem;
	free(p);

	length--;

	return e;
}

char get(Node *list, int r) {
	if (r > length) {
		printf("invalid position\n");
		return 0;
	}

	Node *p = list;

	for (int i = 0; i < r; i++)
		p = p->next;

	return (p->elem);
}

void print(Node *list) {
	Node *p = list->next;

	for (int i = 0; i < length; i++) {
		printf("%c", p->elem);
		p = p->next;
	}
	printf("\n");
}

int main() {
	Node *head = (Node *) malloc(sizeof(Node));
	Node *tail = (Node *) malloc(sizeof(Node));

	head->next = tail;
	tail->prev = head;

	int n;
	scanf("%d", &n);

	for (int i = 0; i < n; i++) {
		char c, e;
		int r;

		getchar();
		scanf("%c", &c);
		if (c == 'A') {
			scanf("%d %c", &r, &e);
			add(head, r, e);
		}
		else if (c == 'D') {
			scanf("%d", &r);
			delete(head, r);
		}
		else if (c == 'G') {
			scanf("%d", &r);
			e = get(head, r);
			if (e)
				printf("%c\n", e);
		}
		else if (c == 'P') {
			print(head);
		}
	}

	return 0;
}