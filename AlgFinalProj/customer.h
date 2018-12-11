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
#include "graphNTransport.h"
#ifndef __CUSTOMER_RBTREE__
#define __CUSTOMER_RBTREE__

typedef struct __CUSTOMERNODE__ {
	/*======== RBTREE FACTORS ========*/
	struct __CUSTOMERNODE__ *left;
	struct __CUSTOMERNODE__ *right;
	struct __CUSTOMERNODE__ *p;
	/*================================*/
	char *key;
	city *destination;	// destination site: input by user
	city **route;   	// recommended route of the customer
	int budget;
	int period;
	int isRed;
} customer;

typedef struct __CUSTOMERTREE__ {
	customer *root;
} cTree;

cTree *initCTree();
customer *initCustomer(char *k);
customer *search(cTree *T, char *z);
customer *successor(customer *z);
customer *precessor(customer *z);
void leftRotate(cTree *T, customer *x);
void rightRotate(cTree *T, customer *x);
void rbInsertFixup(cTree *T, customer *z);
void rbInsert(cTree *T, customer *z);
void rbDeleteFixup(cTree *T, customer *x);
void rbDelete(cTree *T, char *tar);
#endif
