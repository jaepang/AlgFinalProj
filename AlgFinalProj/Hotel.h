/**
 * Algorithm Final Project - Hotel.h
 *
 * Team 21 :
 *		2017312077 YESONG HA
 *		2017310528 JAEKWANG SHIN
 *
 * github repository :
 *		https://github.com/shinjawkwang/AlgFinalProj
 */
#ifndef __HOTELRBTREE__
#define __HOTELRBTREE__

typedef struct __HOTELNODE__ {
	/*======== RBTREE FACTORS ========*/
	struct __HOTELNODE__ *left;
	struct __HOTELNODE__ *right;
	struct __HOTELNODE__ *p;
	/*================================*/
	int key;
	int isRed;
} hotel;

typedef struct __HOTELTREE__ {
	hotel *root;
} hTree;

hTree *initHTree();
hotel *initCustomer(int k);
hotel *search(hTree *T, int z);
hotel *successor(hotel *z);
hotel *precessor(hotel *z);
int heightPrint(hotel *n);
int print(hotel *n, int isLeft, int offset, int depth, char treeStr[20][255]);
void printTree(hTree *t);
void leftRotate(hTree *T, hotel *x);
void rightRotate(hTree *T, hotel *x);
void rbInsertFixup(hTree *T, hotel *z);
void rbInsert(hTree *T, hotel *z);
void rbDeleteFixup(hTree *T, hotel *x);
void rbDelete(hTree *T, int tar);
#endif
