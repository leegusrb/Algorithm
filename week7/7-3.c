#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	int key, height;
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
	l->height = 0;

	r->lChild = r->rChild = NULL;
	r->parent = w;
	r->height = 0;

	w->lChild = l;
	w->rChild = r;
	w->height = 1;
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

int updateHeight(Node *w) {
	int h = w->lChild->height > w->rChild->height ? w->lChild->height + 1 : w->rChild->height + 1;

	if (h != w->height) {
		w->height = h;
		return 1;
	}
	return 0;
}

int isBalanced(Node *w) {
	int diff = w->lChild->height - w->rChild->height;

	return diff > -2 && diff < 2;
}

Node *restructure(Node *x, Node *y, Node *z) {
	Node *a, *b, *c;
	Node *T0, *T1, *T2, *T3;

	if (z->key < y->key && y->key < x->key) {
		a = z; b = y; c = x;
		T0 = a->lChild; T1 = b->lChild; T2 = c->lChild; T3 = c->rChild;
	} else if (x->key < y->key && y->key < z->key) {
		a = x; b = y; c = z;
		T0 = a->lChild; T1 = a->rChild; T2 = b->rChild; T3 = c->rChild;
	} else if (z->key < x->key && x->key < y->key) {
		a = z; b = x; c = y;
		T0 = a->lChild; T1 = b->lChild; T2 = b->rChild; T3 = c->rChild;
	} else {
		a = y; b = x; c = z;
		T0 = a->lChild; T1 = b->lChild; T2 = b->rChild; T3 = c->rChild;
	}

	if (z == root) {
		root = b;
		b->parent = NULL;
	} else if (z->parent->lChild == z) {
		z->parent->lChild = b;
		b->parent = z->parent;
	} else {
		z->parent->rChild = b;
		b->parent = z->parent;
	}

	a->lChild = T0;
	a->rChild = T1;
	T0->parent = T1->parent = a;
	updateHeight(a);

	c->lChild = T2;
	c->rChild = T3;
	T2->parent = T3->parent = c;
	updateHeight(c);

	b->lChild = a;
	b->rChild = c;
	a->parent = c->parent = b;
	updateHeight(b);

	return b;
}

void searchAndFixAfterInsertion(Node *w) {
	w->lChild->height = 0;
	w->rChild->height = 0;
	w->height = 1;

	if (w == root)
		return;

	Node *z = w->parent;
	while (updateHeight(z) && isBalanced(z)) {
		if (z == root)
			return;
		z = z->parent;
	}

	if (isBalanced(z))
		return;

	Node *x, *y;
	if (z->lChild->height > z->rChild->height)
		y = z->lChild;
	else
		y = z->rChild;

	if (y->lChild->height > y->rChild->height)
		x = y->lChild;
	else
		x = y->rChild;

	restructure(x, y, z);
}

void insertItem(int k) {
	Node *w = treeSearch(root, k);

	w->key = k;
	expandExternal(w);
	searchAndFixAfterInsertion(w);
}

void searchAndFixAfterRemoval(Node *z) {
	while (updateHeight(z) && isBalanced(z)) {
		if (z == root)
			return;
		z = z->parent;
	}

	if (isBalanced(z)) return;

	Node *x, *y;
	if (z->lChild->height > z->rChild->height)
		y = z->lChild;
	else
		y = z->rChild;

	if (y->lChild->height < y->rChild->height)
		x = y->rChild;
	else if (y->lChild->height > y->rChild->height)
		x = y->lChild;
	else {
		if (z->lChild == y)
			x = y->lChild;
		else
			x = y->rChild;
	}

	Node *b = restructure(x, y, z);
	if (b == root)
		return;
	searchAndFixAfterRemoval(b->parent);
}

int removeElement(int k) {
	Node *w = treeSearch(root, k);

	if (isExternal(w))
		return 0;

	Node *z = w->lChild;
	if (isInternal(z))
		z = w->rChild;
	Node *zs;
	if (isExternal(z))
		zs = reduceExternal(z);
	else {
		Node *y = inOrderSucc(w);
		z = y->lChild;
		w->key = y->key;
		zs = reduceExternal(z);
	}
	searchAndFixAfterRemoval(zs->parent);

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
	root->height = 0;

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