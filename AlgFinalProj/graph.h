#include "RBTree.h"
#ifndef __GRAPH__
#define __GRAPH__

/**
  * in main, make graph[100].
  * each index is each site
*/

typedef struct __GRAPHNODE__ {
	int id;
	// transport ID
	int tpID;
	struct __GRAPHNODE__ *next;
} gNode;

typedef struct __GRAPHSTRUCT__ {
	gNode *head;
} graph;
#endif
