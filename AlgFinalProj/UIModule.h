/**
* Algorithm Final Project - UIModule.h
*
* Team 21 :
*		2017312077 YESONG HA
*		2017310528 JAEKWANG SHIN
*
* github repository :
*		https://github.com/shinjawkwang/AlgFinalProj
*/
#ifndef __UI_MODULE__
#include "customer.h"
#define __UI_MODULE__

typedef struct __INFORMATION__ {
	char *key;
	int budget;
	int destination;
	int period;
} userinfo;

userinfo *initUI(cTree *tree);
void ResultUI(customer *person, city **city, userinfo *user, tp **t);

/* Tree print functions - hotel */
int heightPrint(hotel *n);
int print(hotel *n, int isLeft, int offset, int depth, char treeStr[20][255]);
void printTree(hTree *t);
/* Tree print functions - customer */
int heightPrint(customer *n);
int print(customer *n, int isLeft, int offset, int depth, char treeStr[20][255]);
void printTree(cTree *t);
#endif
