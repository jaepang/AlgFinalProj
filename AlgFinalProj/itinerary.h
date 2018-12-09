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

#include "Hotel.h"
#include "customer.h"
#include "graphNTransport.h"

void routeFinding(customer* person, city* now, int nowIndex, city** city, int nowT, int back);