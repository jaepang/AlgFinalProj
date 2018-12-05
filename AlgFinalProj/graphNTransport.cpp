/**
 * Algorithm Final Project - graphNTransport.cpp
 *
 * Team 21 :
 *		2017312077 YESONG HA
 *		2017310528 JAEKWANG SHIN
 *
 * github repository :
 *		https://github.com/shinjawkwang/AlgFinalProj
 */
#include <stdlib.h>
#include <time.h>
#include "graphNTransport.h"

tp *initTransport(int *vInfo, int price) {
	tp *tr = (tp *)malloc(sizeof(tp));
	tr->start = vInfo[0];
	tr->end = vInfo[1];
	tr->price = price;
	return tr;
}

gNode *initGNode(int sID, tp *trans) {
	gNode *edge;
	edge = (gNode *)malloc(sizeof(gNode));
	edge->sID = sID;
	edge->trans = trans;
	edge->next = NULL;
	return edge;
}

site *initSite(tree* hTree, int tourT) {
	site *s = (site *)malloc(sizeof(site));
	s->head = NULL;
	s->hotelTree = hTree;
	s->tourTime = tourT;
	return s;
}

void insertVertex(site *S, gNode *edge) {
	gNode *cur;
	if (S->head == NULL) {
		S->head = edge;
	}
	else {
		cur = S->head;
		while (cur->next != NULL) {
			cur = cur->next;
		}
		cur->next = edge;
	}
}
