#include "Hotel.h"
#include "customer.h"
#include "graphNTransport.h"
#include "itinerary.h"
#include <stdio.h>

int stack[100][100];
int top = 0;
gNode* tmpNode;

void push(int num, int day) {
	stack[top][0] = num;
	stack[top++][1] = day;
}
void pop() { top--; }

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
						printf("1");
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
