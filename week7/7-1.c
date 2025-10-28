#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	int key;
	struct Node *parent, *lChild, *rChild;
} Node;

Node *root;

int isExternal(Node *w) {
	return !w->lChild && !w->rChild;
}

int isInternal(Node *w) {
	return !isExternal(w);
}

Node *treeSearch(Node *v, int k) {
	if (isExternal(v))
		return v;

	if (k == v->key)
		return v;
	if (k < v->key)
		return treeSearch(v->lChild, k);
	return treeSearch(v->rChild, k);
}

int findElement(int k) {
	Node *w = treeSearch(root, k);

	if (isExternal(w))
		return 0;
	return w->key;
}

Node *sibling(Node *w) {
	if (w->parent->lChild == w)
		return w->parent->rChild;
	return w->parent->lChild;
}

void expandExternal(Node *w) {
	Node *l = (Node *) malloc(sizeof(Node));
	Node *r = (Node *) malloc(sizeof(Node));

	l->lChild = l->rChild = NULL;
	l->parent = w;

	r->lChild = r->rChild = NULL;
	r->parent = w;

	w->lChild = l;
	w->rChild = r;
}

Node *reduceExternal(Node *z) {
	Node *w = z->parent;
	Node *zs = sibling(z);

	if (root == w) {
		root = zs;
		zs->parent = NULL;
	} else {
		Node *g = w->parent;
		zs->parent = g;
		if (w == g->lChild)
			g->lChild = zs;
		else
			g->rChild = zs;
	}

	free(z);
	free(w);

	return zs;
}

Node *inOrderSucc(Node *w) {
	w = w->rChild;

	while (isInternal(w->lChild))
		w = w->lChild;

	return w;
}

void insertItem(int k) {
	Node *w = treeSearch(root, k);

	w->key = k;
	expandExternal(w);
}

int removeElement(int k) {
	Node *w = treeSearch(root, k);

	if (isExternal(w))
		return 0;

	Node *z = w->lChild;
	if (isInternal(z))
		z = w->rChild;
	if (isExternal(z))
		reduceExternal(z);
	else {
		Node *y = inOrderSucc(w);
		z = y->lChild;
		w->key = y->key;
		reduceExternal(z);
	}

	return k;
}

void preOrder(Node *v) {
	if (isExternal(v)) return;

	printf(" %d", v->key);
	preOrder(v->lChild);
	preOrder(v->rChild);
}

int main() {
	root = (Node *) malloc(sizeof(Node));
	root->parent = NULL;
	root->lChild = NULL;
	root->rChild = NULL;

	while (1) {
		char c;
		int k;

		scanf("%c", &c);
		if (c == 'i') {
			scanf("%d", &k);
			insertItem(k);
		} else if (c == 'd') {
			scanf("%d", &k);
			k = removeElement(k);
			if (k == 0)
				printf("X\n");
			else
				printf("%d\n", k);
		} else if (c == 's') {
			scanf("%d", &k);
			k = findElement(k);
			if (k == 0)
				printf("X\n");
			else
				printf("%d\n", k);
		} else if (c == 'p') {
			preOrder(root);
			printf("\n");
		} else if (c == 'q') {
			break;
		}
		getchar();
	}
}