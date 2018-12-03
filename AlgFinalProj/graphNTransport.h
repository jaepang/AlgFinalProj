#include "RBTree.h"
#ifndef __GRAPHNTRANSPORT__
#define __GRAPHNTRANSPORT__

/**
  * in main, make sInfo[100] == graph.
  * each index is each site
*/

typedef struct __TRNASPORT__ {
	int id;
	int price;
} tp;

typedef struct __GRAPHNODE__ {
	int id;
	// transport ID
	int tpID;
	struct __GRAPHNODE__ *next;
} site;

typedef struct __SITEINFO__ {
	site *head;
	int tourTime;
} sInfo;

site *initSite(int id, int tpID);
#endif
