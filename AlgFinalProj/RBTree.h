#ifndef __RBTREE__
#define __RBTREE__

typedef struct __NODE__ {
	struct __NODE__ *left;
	struct __NODE__ *right;
	struct __NODE__ *p;
	int key;
	int isRed;
	/** price will be -1 or int value
	  * hotel: int value
	  * reserved customer: -1 value
	*/
	int price;
} node;

typedef struct __TREE__ {
	node *root;
	/** this can be either site or hotel
	  * because there are hotel RBTree
	  * AND hotel reservation RBTree
	*/
	int pID;
} tree;

tree *initTree(int pID);
node *initHotelNode(int k, int p);
node *initCustomerNode(int k);
node *search(tree *T, int z);
node *successor(node *z);
node *precessor(node *z);
int heightPrint(node *n);
int print(node *n, int isLeft, int offset, int depth, char treeStr[20][255]);
void printTree(tree *t);
void leftRotate(tree *T, node *x);
void rightRotate(tree *T, node *x);
void rbInsertFixup(tree *T, node *z);
void rbInsert(tree *T, int x, int p);
void rbDeleteFixup(tree *T, node *x);
void rbDelete(tree *T, int tar);
#endif
