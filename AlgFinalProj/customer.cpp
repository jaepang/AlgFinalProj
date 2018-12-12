/**
 * Algorithm Final Project - customer.cpp
 *
 * Team 21 :
 *		2017312077 YESONG HA
 *		2017310528 JAEKWANG SHIN
 *
 * github repository :
 *		https://github.com/shinjawkwang/AlgFinalProj
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "customer.h"

cTree *initCTree() {
	cTree *t = (cTree *)malloc(sizeof(cTree));
	t->root = NULL;
	return t;
}

customer *initCustomer(char *k) {
	customer *n = (customer *)malloc(sizeof(customer));
	n->key = (char *)malloc(sizeof(char) * 10);
	n->left = NULL;
	n->right = NULL;
	n->p = NULL;
	strcpy(n->key, k);
	n->isRed = 0;
	n->route = NULL;
	return n;
}

customer *search(cTree *T, char *z) {
	customer *cur = T->root;

	// printf("Search(%d) path: ", z);
	while (cur != NULL) {
		// printf("%d ", cur->key);
		if (strcmp(z,cur->key) == 0) {
			// printf("=> Found!\n");
			return cur;
		}
		else if (strcmp(z, cur->key) < 0) {
			cur = cur->left;
		}
		else {
			cur = cur->right;
		}
	}
	// printf("=> Not Found\n");
	return NULL;
}

customer *successor(customer *z) {
	customer *prev;
	if (z->right != NULL) {
		z = z->right;
		while (z->left != NULL) {
			z = z->left;
		}
		return z;
	}
	else {
		prev = z->p;
		while (prev != NULL && z == prev->right) {
			z = prev;
			prev = prev->p;
		}
		return prev;
	}
}

customer *precessor(customer *z) {
	customer *prev;
	if (z->left != NULL) {
		z = z->left;
		while (z->right != NULL) {
			z = z->right;
		}
		return z;
	}
	else {
		prev = z->p;
		while (prev != NULL && z == prev->left) {
			z = prev;
			prev = prev->p;
		}
		return prev;
	}
}

void leftRotate(cTree *T, customer *x) {
	customer *y = x->right;
	x->right = y->left;
	if (y->left != NULL) {
		y->left->p = x;
	}
	y->p = x->p;
	if (x->p == NULL) {
		T->root = y;
	}
	else if (x == x->p->left) {
		x->p->left = y;
	}
	else {
		x->p->right = y;
	}
	y->left = x;
	x->p = y;
}

void rightRotate(cTree *T, customer *x) {
	customer *y = x->left;
	x->left = y->right;
	if (y->right != NULL) {
		y->right->p = x;
	}
	y->p = x->p;
	if (x->p == NULL) {
		T->root = y;
	}
	else if (x == x->p->right) {
		x->p->right = y;
	}
	else {
		x->p->left = y;
	}
	y->right = x;
	x->p = y;
}

void rbInsertFixup(cTree *T, customer *z) {
	customer *y;
	if (z->p != NULL && z->p->p != NULL) {
		while (z != NULL && z->p != NULL && z->p->p != NULL && z->p->isRed) {
			if (z->p == z->p->p->left) {
				y = z->p->p->right;
				if (y != NULL && y->isRed) {
					z->p->isRed = 0;
					y->isRed = 0;
					z->p->p->isRed = 1;
					z = z->p->p;
				}
				else {
					if (z == z->p->right) {
						z = z->p;
						leftRotate(T, z);
					}
					z->p->isRed = 0;
					z->p->p->isRed = 1;
					rightRotate(T, z->p->p);
				}
			}
			else {
				customer *y = z->p->p->left;
				if (y != NULL && y->isRed) {
					z->p->isRed = 0;
					y->isRed = 0;
					z->p->p->isRed = 1;
					z = z->p->p;
				}
				else {
					if (z == z->p->left) {
						z = z->p;
						rightRotate(T, z);
					}
					z->p->isRed = 0;
					z->p->p->isRed = 1;
					leftRotate(T, z->p->p);
				}
			}
		}
	}
	T->root->isRed = 0;
}

void rbInsert(cTree *T, customer *z) {
	customer *cur, *prev = NULL;

	z->isRed = 1;
	cur = T->root;
	while (cur != NULL) {
		prev = cur;
		if (z->key < cur->key) {
			cur = cur->left;
		}
		else if (z->key > cur->key) {
			cur = cur->right;
		}
		else {
			return;
		}
	}
	if (prev != NULL) {
		z->p = prev;
		if (z->key < prev->key) {
			prev->left = z;
		}
		else {
			prev->right = z;
		}
	}
	else {
		T->root = z;
	}
	rbInsertFixup(T, z);
}

void rbDeleteFixup(cTree *T, customer *x) {
	customer *y;
	while (x != T->root && !x->isRed) {
		if (x->p->left == x) {
			y = x->p->right;
			if (y->isRed) {
				y->isRed = 0;
				x->p->isRed = 1;
				leftRotate(T, x->p);
				y = x->p->right;
			}
			if (!y->right->isRed && !y->left->isRed) {
				y->isRed = 1;
				x = x->p;
			}
			else {
				if (!y->right->isRed) {
					y->left->isRed = 0;
					y->isRed = 1;
					rightRotate(T, y);
					y = x->p->right;
				}
				y->isRed = x->p->isRed;
				x->p->isRed = 0;
				y->right->isRed = 0;
				leftRotate(T, x->p);
				x = T->root;
			}
		}
		else {
			y = x->p->left;
			if (y->isRed) {
				y->isRed = 0;
				x->p->isRed = 1;
				rightRotate(T, x->p);
				y = x->p->left;
			}
			if (!y->left->isRed && !y->right->isRed) {
				y->isRed = 1;
				x = x->p;
			}
			else {
				if (!y->left->isRed) {
					y->right->isRed = 0;
					y->isRed = 1;
					leftRotate(T, y);
					y = x->p->left;
				}
				y->isRed = x->p->isRed;
				x->p->isRed = 0;
				y->left->isRed = 0;
				rightRotate(T, x->p);
				x = T->root;
			}
		}
		x->isRed = 0;
		T->root->isRed = 0;
	}
}

void rbDelete(cTree *T, char *tar) {
	customer *x, *y;
	customer *z = search(T, tar);
	if (z != NULL) {
		if (z->left == NULL || z->right == NULL) {
			y = z;
		}
		else {
			y = successor(z);
		}
		if (y->left != NULL) {
			x = y->left;
		}
		else {
			x = y->right;
		}
		if (x != NULL) {
			x->p = y->p;
		}
		if (y->p == NULL) {
			T->root = x;
		}
		else if (y == y->p->left) {
			y->p->left = x;
		}
		else {
			y->p->right = x;
		}
		if (y != z) {
			z->key = y->key;
		}
		if (!y->isRed && x != NULL) {
			rbDeleteFixup(T, x);
		}
	}
}
