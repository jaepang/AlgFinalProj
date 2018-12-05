/**
 * Algorithm Final Project - RBTree.h
 *
 * Team 21 :
 *		2017312077 YESONG HA
 *		2017310528 JAEKWANG SHIN
 *
 * github repository :
 *		https://github.com/shinjawkwang/AlgFinalProj
 */
#ifndef __RBTREE__
#define __RBTREE__

typedef struct __NODE__ {
	struct __NODE__ *left;
	struct __NODE__ *right;
	struct __NODE__ *p;
	/* key can be price(hotel node) or id(customer node) */
	int key;
	int isRed;
	struct __TREE__ *reserveTree;
} node;

typedef struct __TREE__ {
	node *root;
} tree;

tree *initTree();
node *initNode(int k);
node *search(tree *T, int z);
node *successor(node *z);
node *precessor(node *z);
int heightPrint(node *n);
int print(node *n, int isLeft, int offset, int depth, char treeStr[20][255]);
void printTree(tree *t);
void leftRotate(tree *T, node *x);
void rightRotate(tree *T, node *x);
void rbInsertFixup(tree *T, node *z);
void rbInsert(tree *T, node *z);
void rbDeleteFixup(tree *T, node *x);
void rbDelete(tree *T, int tar);
/* for hotel nodes only: init hotel reservation tree */
void initReservationTree(node *n);
#endif
