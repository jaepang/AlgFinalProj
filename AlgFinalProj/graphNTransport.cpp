#include <stdlib.h>
#include "graphNTransport.h"

site *initSite(int id, int tpID) {
	site *s = (site *)malloc(sizeof(site));
	s->id = id;
	s->tpID = tpID;
	return s;
}
