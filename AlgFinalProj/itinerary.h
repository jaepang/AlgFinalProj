/**
* Algorithm Final Project - itinerary.h
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
#include "UIModule.h"

int routeFinding(customer* person, city* now, int nowIndex, city** city, int nowT, int back, userinfo *user);
void moneyCalculate(customer* person, city* now, city** city);
void stackPrinter(city **c, tp **t);
int itinerary(customer* person, city* now, city** city, userinfo *user, tp **tp);
