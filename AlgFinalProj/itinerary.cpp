#include "Hotel.h"
#include "customer.h"
#include "graphNTransport.h"
#include "itinerary.h"
#include "UIModule.h"
#include <stdio.h>

int stack[100][100];
// stack [a][0] = city number
// stack [a][1] = city tour time
// stack [a][2] = Hotel price to live at that city

int top = 0;
gNode* tmpNode;

void routeFinding(customer* person, city* now, int nowIndex, city** city, int nowT, int back);
void moneyCalculate(customer* person, city* now, city** city);

void push(int num, int day) {
	stack[top][0] = num;
	stack[top++][1] = day;
}
void pop() { top--; }

void itinerary(customer* person, city* now, city** city, userinfo *user) {
	routeFinding(person, person->destination, user->destination, city, 0, 0);
	moneyCalculate(person, person->destination, city);
}

void routeFinding(customer* person, city* now, int nowIndex, city** city, int nowT, int back) {
	int flag = 0, back_flag;
	printf("start");
	if (top < 0) {
		printf("there's no way satisfying conditions\n");

	}

		/* ==================== Going Forward ========================= */
		if (back == 0) {
			for (int i = 0; i < top; i++) {
				printf("stack: %d %d\n", stack[i][0], stack[i][1]);
			}

			if (now == NULL) return;

			tmpNode = now->head;
			flag = 0;


			if (nowT + now->tourTime == person->period) {
				printf("sID: %d, nowT: %d tourTime: %d\n", nowIndex, nowT, now->tourTime);
				printf("finish");
				push(nowIndex, now->tourTime);
				nowT += now->tourTime;
				return;
			}
			else if (nowT + now->tourTime < person->period) {
				printf("sID: %d, nowT: %d tourTime: %d\n", nowIndex, nowT, now->tourTime);
				nowT += now->tourTime;
				while (tmpNode != NULL) {
					printf("0");
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
					printf("No route here way!\n");
					tmpNode = city[stack[top - 1][0]]->head;

					back_flag = 1;
					while (tmpNode->sID != nowIndex) {
						printf("2");
						back_flag++;
						tmpNode = tmpNode->next;
					}

					return routeFinding(person, city[stack[top - 1][0]], stack[top - 1][0], city, nowT, back_flag);
				}

				push(nowIndex, now->tourTime);
				return routeFinding(person, city[tmpNode->sID], tmpNode->sID, city, nowT, 0);
			}

			else {
				printf("going back index: %d time: %d\n", nowIndex, now->tourTime);

				for (int i = 1;; i++) {
					if (top - i <= 0) {
						printf("There's no way at all\n");
						return;
					}

					tmpNode = city[stack[top - i][0]]->head;
					back_flag = 1;
					while (tmpNode->sID != nowIndex) {
						printf("-1");
						back_flag++;
						tmpNode = tmpNode->next;
					}
					if (tmpNode == NULL) {
						printf("continue\n");
						nowIndex = stack[top - i][0];
						continue;
					}
					else {
						top -= i;
						break;
					}
				}
				return routeFinding(person, city[stack[top - 1][0]], stack[top - 1][0], city, nowT, back_flag);
			}
		}

		/* ==================== Going Back ========================= */
		else {
			tmpNode = now->head;

			if (tmpNode != NULL) {
				for (int i = 0; i < back; i++) {
					tmpNode = tmpNode->next;
				}

				// Stack Check
				while (tmpNode != NULL) {
					printf("4");
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
						printf("sID: %d, nowT: %d \n", tmpNode->sID, nowIndex);
						printf("1");
						back_flag++;
						tmpNode = tmpNode->next;
					}

					return routeFinding(person, city[stack[top - 1][0]], stack[top - 1][0], city, nowT, back_flag);
				}

				return routeFinding(person, city[tmpNode->sID], tmpNode->sID, city, nowT, 0);
			}
			else if (top - 2 < 0) {
				printf("there's no route");
				return;
			}
			else {
				back_flag = 0;
				tmpNode = city[stack[top - 2][0]]->head;
				while (tmpNode != NULL) {
					printf("5");
					if (tmpNode->sID == stack[top - 1][0]) {
						pop();
						break;
					}
					else {
						back_flag++;
						tmpNode = tmpNode->next;
					}
				}
				return routeFinding(person, city[stack[top - 1][0]], stack[top - 1][0], city, nowT-stack[top][1], back_flag);
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
	//printf("\nmean money: %d\n", meanMoney);

	for (int i = top - 1; i >= 0; i--) {
		tmpHotel = search_p(city[i]->hotelTree, meanMoney);
		//printf("Hotel money: %d\n", tmpHotel->key);
		stack[i][2] = tmpHotel->key;
		person->budget -= (tmpHotel->key)*stack[i][1];
	}
	//printf("Left money: %d\n", person->budget);
}