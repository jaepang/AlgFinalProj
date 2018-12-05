/**
 * Algorithm Final Project - main.cpp
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
#include <time.h>
#include "RBTree.h"
#include "graphNTransport.h"

#define SITESIZE 100
#define HOTELSIZE 100
#define TPSIZE 300

int *vertexAvoidDup();					  // avoid start and end is same
int *setVertex(tp **tpGroup, int size);   // avoid creating vertex that is already exist

int main(void) {
	int i, j, price;				// i,j: for iteration; price: literally
	int *vertex;					// vertex
	tree *hotelTree;				// temporalily created and fit into each site
	node *node;						// temporary node
	gNode *edge;					// temporary edge
	site *site[SITESIZE];			// core graph variable **important
	tp *transport[TPSIZE];			// transport array
	srand(time(NULL));				// for random

	/* =============== Randomly generate site, hotel, transportation =============== */
	for (i = 0; i < SITESIZE; i++) {
		hotelTree = initTree();
		// there should be 100 hotels per site
		for (j = 0; j < HOTELSIZE; j++) {
			// hotel price boundary: 1000~10000
			price = (rand() % 10 + 1) * 1000;
			node = initNode(price);
			initReservationTree(node);
			rbInsert(hotelTree, node);
		}
		// site tour time boundary: 1~5 (hours)
		site[i] = initSite(hotelTree, rand() % 5 + 1);
	}

	for (i = 0; i < TPSIZE; i++) {
		vertex = setVertex(transport, i);
		// transport price boundary: 10~100
		transport[i] = initTransport(vertex, (rand() % 10 + 1) * 10);
		// connect site and site
		edge = initGNode(vertex[1], transport[i]);
		insertVertex(site[vertex[0]], edge);
		edge = initGNode(vertex[0], transport[i]);
		insertVertex(site[vertex[1]], edge);
		free(vertex);	// we don't need this anymore
	}
	/* ============================================================================= */

	/**
	 * It's Your Turn!
	 * Show me your code
	 * ASAP..
	 */
	return 0;
}

/**
 * This function should be here
 * because when in another .cpp,
 * srand(time(NULL)) doesn't work
 * and generate 300 same vertexes
 */
int *vertexAvoidDup() {
	int s = 0, e = 0, *ver;
	ver = (int *)malloc(sizeof(int) * 2);
	while (s == e) {
		s = rand() % 100;
		e = rand() % 100;
	}
	ver[0] = s;
	ver[1] = e;
	return ver;
}

int *setVertex(tp **tpGroup, int size) {
	int *ver, flag = 1;
	ver = vertexAvoidDup();
	while (flag) {
		flag = 0;	// for when size == 0
		for (int i = 0; i < size; i++) {
			flag = ((tpGroup[i]->start == ver[0]) || (tpGroup[i]->start == ver[1]))
				   && ((tpGroup[i]->end == ver[0]) || (tpGroup[i]->end == ver[1]));
			if (flag){
				break;
			}
		}
		if (!flag) {
			break;
		}
		ver = vertexAvoidDup();
	}
	return ver;
}
