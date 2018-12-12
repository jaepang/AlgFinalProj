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
#include "Hotel.h"
#include "itinerary.h"
#include "graphNTransport.h"
#include "customer.h"
#include "UIModule.h"

#define CITYSIZE 100
#define HOTELSIZE 100
#define TPSIZE 300

int *vertexAvoidDup();					  // avoid start and end is same
int *setVertex(tp **tpGroup, int size);   // avoid creating vertex that is already exist

int main(void) {
	int i, j, price;				// i,j: for iteration; price: literally
	int *vertex;					// vertex
	cTree *customerTree;		    // RBTree that save customer information
	hTree *hotelTree;				// temporalily created and fit into each city
	hotel *node;					// temporary hotel node
	gNode *edge;					// temporary edge
	customer *person;				// temporary customer
	userinfo *user;                 // for input
	city *city[CITYSIZE];			// core graph variable **important
	tp *transport[TPSIZE];			// transport array
	srand(time(NULL));				// for random

	/* =============== Randomly generate city, hotel, transportation =============== */
	customerTree = initCTree();
	for (i = 0; i < CITYSIZE; i++) {
		hotelTree = initHTree();
		// there should be 100 hotels per city
		for (j = 0; j < HOTELSIZE; j++) {
			// hotel price boundary: 500~5000
			price = (rand() % 10 + 1) * 500;
			node = initHotel(price);
			rbInsert(hotelTree, node);
		}
		// city tour time boundary: 1~5 (days)
		city[i] = initCity(hotelTree, rand() % 5 + 1);
	}	

	for (i = 0; i < TPSIZE; i++) {
		vertex = setVertex(transport, i);
		// transport price boundary: 10~100
		transport[i] = initTransport(vertex, (rand() % 10 + 1) * 10);
		// connect city and city
		edge = initGNode(vertex[1], transport[i]);
		insertVertex(city[vertex[0]], edge);
		edge = initGNode(vertex[0], transport[i]);
		insertVertex(city[vertex[1]], edge);
		free(vertex);	// we don't need this anymore
	}
	/* ============================================================================= */

	/**
	 * It's Your Turn!
	 * Show me your code
	 * ASAP..
	 */

	 /* ===========Part for getting inputs============================================ */
	while (1) {
		user = initUI(customerTree);
		if (user == NULL) {
			break;
		}
		person = initCustomer(user->key);
		person->budget = user->budget;
		person->destination = city[user->destination];
		person->period = user->period;

		rbInsert(customerTree, person);
		printTree(customerTree);

		routeFinding(person, person->destination, user->destination, city, 0, 0);

	}
	
	return 0;
}

/**
 * This function should be here
 * because when in another .cpp,
 * srand(time(NULL)) doesn't work
 * as result, generate 300 same vertexes
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
