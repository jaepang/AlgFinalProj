/**
 * Algorithm Final Project - graphNTransport.h
 *
 * Team 21 :
 *		2017312077 YESONG HA
 *		2017310528 JAEKWANG SHIN
 *
 * github repository :
 *		https://github.com/shinjawkwang/AlgFinalProj
 */
#include "RBTree.h"
#ifndef __GRAPHNTRANSPORT__
#define __GRAPHNTRANSPORT__

/**
 * in main, make site[100] ==> a graph
 *
 * ===================================================================
 * Example :
 *		0: hotelTree( 0), -> edge  0-1 -> edge  0-2 -> ... -> NULL
 *		1: hotelTree( 1), -> edge  1-1 -> edge  1-2 -> ... -> NULL
 *		...
 *	   99: hotelTree(99), -> edge 99-1 -> edge 99-2 -> ... -> NULL
 * ===================================================================
 *
 * each index is each site
 */

typedef struct __TRNASPORT__ {
	/**
	 * Although the naming is start and end,
	 * the order shouln't be cared
	 * because the graph is undirected graph.
	 */
	int start;
	int end;
	int price;
} tp;

typedef struct __GRAPHNODE__ {
	int sID;
	tp *trans;
	struct __GRAPHNODE__ *next;
} gNode;

typedef struct __SITEINFO__ {
	gNode *head;
	tree *hotelTree;
	int tourTime;
} site;

tp *initTransport(int *vInfo, int price);
gNode *initGNode(int sID, tp *trans);
site *initSite(tree* hTree, int tourT);
void insertVertex(site *S, gNode *edge);
#endif