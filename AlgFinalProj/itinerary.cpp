/**
* Algorithm Final Project - itinerary.cpp
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
#include "itinerary.h"
#include "UIModule.h"
#include <stdio.h>

int stack[100][100];
// stack [a][0] = city number
// stack [a][1] = city tour time
// stack [a][2] = Hotel id to live at that city
// stack [a][3] = Hotel price to live at that city

int top = 0;
gNode* tmpNode;

void push(int num, int day) {
	stack[top][0] = num;
	stack[top++][1] = day;
}
void pop() { top--; }

int itinerary(customer* person, city* now, city** city, userinfo *user, tp **t) {
	stack[100][100] = { 0, };
	top = 0;
	int retNum = 0;

	retNum=routeFinding(person, person->destination, user->destination, city, 0, 0, user);
	// If retNum==0, correctly found route
	// If retNum==-1, there's no route
	if (retNum == -1) {
		return -1;
	}
	else {
		moneyCalculate(person, person->destination, city);
		stackPrinter(city, t);
		return 0;
	}
}

int routeFinding(customer* person, city* now, int nowIndex, city** city, int nowT, int back, userinfo *user) {
	int flag = 0, back_flag;
	
	if (top > 0&&(nowIndex==user->destination)) {
		return -1;
	}

		/* ==================== Going Forward ========================= */
		if (back == 0) {
			if (now == NULL) return -1;

			tmpNode = now->head;
			flag = 0;


			if (nowT + now->tourTime == person->period) {
				push(nowIndex, now->tourTime);
				nowT += now->tourTime;
				return 0;
			}
			else if (nowT + now->tourTime < person->period) {
				nowT += now->tourTime;
				while (tmpNode != NULL) {
					for (int i = top - 1; i >= 0; i--) {
						if (stack[i][0] == tmpNode->sID) {
							flag = 1;
							break;
						}
					}
					if (flag == 1) {
						flag = 0;
						tmpNode = tmpNode->next;
					}
					else {
						break;
					}
				}

				if (tmpNode == NULL) {
					tmpNode = city[stack[top - 1][0]]->head;

					back_flag = 1;
					while (tmpNode->sID != nowIndex) {
						back_flag++;
						tmpNode = tmpNode->next;
					}

					return routeFinding(person, city[stack[top - 1][0]], stack[top - 1][0], city, nowT, back_flag, user);
				}

				push(nowIndex, now->tourTime);
				return routeFinding(person, city[tmpNode->sID], tmpNode->sID, city, nowT, 0, user);
			}

			else {
				for (int i = 1;; i++) {

					tmpNode = city[stack[top - i][0]]->head;
					back_flag = 1;
					while (tmpNode->sID != nowIndex) {
						back_flag++;
						tmpNode = tmpNode->next;
						if (tmpNode == NULL) break;
					}
					if (tmpNode == NULL) {
						nowIndex = stack[top - i][0];
						continue;
					}
					else {
						top -= i;
						break;
					}
				}
				return routeFinding(person, city[stack[top - 1][0]], stack[top - 1][0], city, nowT, back_flag, user);
			}
		}

		/* ==================== Going Back ========================= */
		else {
			tmpNode = now->head;

			if (tmpNode != NULL) {
				for (int i = 0; i < back; i++) {
					tmpNode = tmpNode->next;
					if (tmpNode == NULL) break;
				}

				// Stack Check
				while (tmpNode != NULL) {
					for (int i = top - 1; i >= 0; i--) {
						if (stack[i][0] == tmpNode->sID) {
							flag = 1;
							break;
						}
					}
					if (flag == 1) {
						flag = 0;
						tmpNode = tmpNode->next;
					}
					else {
						break;
					}
				}

				if (tmpNode == NULL) {
					for (int i = 1; i <= top; i++) {
						tmpNode = city[stack[top - i][0]]->head;
						back_flag = 1;
						while (tmpNode->sID != nowIndex) {
							back_flag++;
							tmpNode = tmpNode->next;
							if (tmpNode == NULL) break;
						}

						if (tmpNode == NULL) {
							continue;
						}
						top -= i;
						return routeFinding(person, city[stack[top - 1][0]], stack[top - 1][0], city, nowT, back_flag, user);
					}
				}

				return routeFinding(person, city[tmpNode->sID], tmpNode->sID, city, nowT, 0, user);
			}
			else if (top - 2 < 0) {
				return -1;
			}
			else {
				back_flag = 0;
				tmpNode = city[stack[top - 2][0]]->head;
				while (tmpNode != NULL) {
					if (tmpNode->sID == stack[top - 1][0]) {
						pop();
						break;
					}
					else {
						back_flag++;
						tmpNode = tmpNode->next;
					}
				}
				return routeFinding(person, city[stack[top - 1][0]], stack[top - 1][0], city, nowT-stack[top][1], back_flag, user);
			}
		}
	
}

void moneyCalculate(customer* person, city* now, city** city) {
	int transMoney = 0, meanMoney = 0;
	hotel* tmpHotel;

	// Calculate transportation money
	for (int i = top - 1; i > 0; i--) {
		tmpNode=city[stack[i][0]]->head;

		while (1) {
			if (tmpNode->sID != stack[i - 1][0]) {
				tmpNode = tmpNode->next;
			}
			else break;
		}
		transMoney += tmpNode->trans->price;
	}
	person->budget -= transMoney;
	meanMoney = int(person->budget / person->period);

	for (int i = top - 1; i >= 0; i--) {
		tmpHotel = search_p(city[i]->hotelTree, meanMoney);
		stack[i][2] = tmpHotel->id;
		stack[i][3] = tmpHotel->key;
  		person->budget -= (tmpHotel->key)*stack[i][1];
	}
}

// stack [a][0] = city number
// stack [a][1] = city tour time
// stack [a][2] = Hotel id to live at that city
// stack [a][3] = Hotel price to live at that city
void stackPrinter(city **c, tp **t) {
	int cID;		// city ID
	int tID;		// transport ID
	int hID, hP;	// hotel ID, hotel Price
	for (int i = top - 1; i >= 0; i--) {
		cID = stack[i][0];
		hID = stack[i][2];
		hP = stack[i][3];
		printf("@                                                            @\n");// 60
		printf("@                          city: %-2d                          @\n", cID);
		printf("@                     hotel price(%-2d): %-4d                  @\n", hID, hP);
		printf("@                      tour time: %ddays                      @\n", c[cID]->tourTime);
		printf("@                                                            @\n");
		if (0 < i) {
			tID = searchTransport(t, stack[i][0], stack[i - 1][0]);
			printf("@                       transport: %-3d                       @\n", tID);
			printf("@                         price: %-3d                         @\n", t[tID]->price);
		}
	}
	printf("@       Thank you for using our service! See you Again!      @\n");
	printf("@                                                            @\n");
	printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n\n\n");
}