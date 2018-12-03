#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "RBTree.h"
#include "graphNTransport.h"

#define SITESIZE 100
#define HOTELSIZE 100
#define TPSIZE 300

int main() {
	int i, j;
	site *sites[SITESIZE];
	sInfo *graph[SITESIZE];
	tp *transport[TPSIZE];
	/* Randomly generate site, hotel, transportation */
	srand(time(NULL));
	for (i = 0; i < SITESIZE; i++) {
		sites[i] = initSite(i, rand() % TPSIZE);
	}
	for (i = 0; i < SITESIZE; i++) {
		graph[i]->tourTime = rand() % 990 + 10;
		//graph[i]->head = sites[rand() % SITESIZE];
	}
	return 0;
}
