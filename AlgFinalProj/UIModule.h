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
#endif
