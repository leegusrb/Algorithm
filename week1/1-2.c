#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	int data;
	struct Node *left, *right;
} Node;

Node *makeNode(int data) {
	Node *node = (Node *) malloc(sizeof(Node));

	node->data = data;
	node->left = node->right = NULL;

	return node;
}

Node *findNode(Node *root, int data) {
	if (!root || root->data == data)
		return root;

	Node *node = findNode(root->left, data);
	if (node)
		return node;
	return findNode(root->right, data);
}

void search(Node *root, char *str) {
	printf(" %d", root->data);
	
	if (!*str) return;

	if (*str == 'L')
		search(root->left, str + 1);
	else
		search(root->right, str + 1);
}

int main() {
	Node *root;

	int n;
	scanf("%d", &n);

	for (int i = 0; i < n; i++) {
		int data, left, right;
		scanf("%d %d %d", &data, &left, &right);

		if (i == 0)
			root = makeNode(data);

		Node *node = findNode(root, data);
		if (left != 0)
			node->left = makeNode(left);
		if (right != 0)
			node->right = makeNode(right);
	}

	int s;
	scanf("%d", &s);

	for (int i = 0; i < s; i++) {
		char str[101];
		scanf("%s", str);

		search(root, str);
		printf("\n");
	}

	return 0;
}