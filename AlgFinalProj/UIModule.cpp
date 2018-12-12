#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "UIModule.h"
#include "customer.h"

userinfo *initUI(cTree *tree) {
	userinfo *user = (userinfo *)malloc(sizeof(userinfo));
	customer *tmp;
	char cmd[100];
	int cmdI;

	while (1) {
		printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
		printf("@                                                            @\n");
		printf("@       Welcome to SKKU TRAVEL RECOMMENDATION SERVICE!       @\n");
		printf("@                                                            @\n");
		printf("@     Before Starting, we'll ask some information of you     @\n");
		printf("@                                                            @\n");
		printf("@    1. If you agree collecting your information, PRESS Y!   @\n");
		printf("@    2. If you don't agree or want to end service, PRESS N.  @\n");
		printf("@    3. If you already used our service, PRESS S.            @\n");
		printf("@                                                            @\n");
		printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
		printf("\n\n>>   셋 중에 하나만 골라 Yes or Yes! (Y/N/S): ");
		scanf("%s", cmd);
		if (strcmp(cmd, "Y") == 0 || strcmp(cmd, "y") == 0) {
			break;
		}
		else if (strcmp(cmd, "N") == 0 || strcmp(cmd, "n")) {
			printf("END PROGRAM. Good Bye!\n");
			return NULL;
		}
		else if (strcmp(cmd, "S") == 0 || strcmp(cmd, "s")) {
			while (1) {
				printf(">>   Then, input your ID (q to end): ");
				scanf("%s", cmd);
				tmp = search(tree, cmd);
				if (strcmp(cmd, "q") == 0) {
					printf("     END PROGRAM. Good Bye!\n");
					return NULL;
				}
				else if (tmp == NULL) {
					printf("     ※ ERROR: ID DOESN'T EXIST!!!\n");
				}
				else {
					ResultUI(tmp);
					break;
				}
			}
		}
		else {
			printf("Wrong Input! please input again..\n");
		}
	}

	printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
	printf("@                                                            @\n");
	printf("@            THANK YOU for chosing our service!!!            @\n");
	printf("@                                                            @\n");
	printf("@                Now, Please fill the format.                @\n");
	printf("@            And the recommendation program start!           @\n");
	printf("@                                                            @\n");
	printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
	
	while (1) {
		printf("\n\n>>   Type your ID, please (string): ");
		scanf("%s", cmd);
		if (search(tree, cmd) != NULL) {
			printf("\n     ※ ERROR: ID ALREADY EXISTS!!!\n");
		}
		else if (strcmp(cmd, "q") == 0) {
			printf("\n     ※ ERROR: YOU CAN'T USE THIS ID.\n");
		}
		else {
			user->key = cmd;
			break;
		}
	}
	printf("\n>>   Type your Destination City, please (0~99): ");
	scanf("%d", &cmdI);
	user->destination = cmdI;

	printf("\n>>   Type your travel budget, please (integer): ");
	scanf("%d", &cmdI);
	user->budget = cmdI;

	printf("\n>>   Type your travel period, please (integer): ");
	scanf("%d", &cmdI);
	user->period = cmdI;
	
	printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
	printf("@                                                            @\n");
	printf("@              There's nothing you have to do!               @\n");
	printf("@                                                            @\n");
	printf("@          Please wait few seconds for calculation..         @\n");
	printf("@                                                            @\n");
	printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");

	return user;
}

void ResultUI(customer *id) {
	printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n"); // 62
	printf("@                                                            @\n");
	printf("@            THANK YOU for waiting our program!!!            @\n");
	printf("@                                                            @\n");
	printf("@                 Now, Let's see the result.                 @\n");
	printf("@                   Your ID: %15s                   @\n", id->key); // 19 24 19
	printf("@                                                            @\n");
	printf("@                                                            @\n");
	printf("@                                                            @\n");
	printf("@                                                            @\n");
	printf("@                                                            @\n");
	printf("@                                                            @\n");
	printf("@                                                            @\n");
	printf("@                                                            @\n");
	printf("@                                                            @\n");
	printf("@                                                            @\n");
	printf("@                                                            @\n");
	printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
}

/**
 * used when printing tree
 * add 1 to subtree height
 * because we print line between nodes
*/
int heightPrint(hotel *n) {
	int r = 0, l = 0;
	if (n->right != NULL)
		r = heightPrint(n->right) + 1;
	if (n->left != NULL)
		l = heightPrint(n->left) + 1;
	return 1 + (r > l ? r : l);
}

int print(hotel *n, int isLeft, int offset, int depth, char treeStr[20][255]) {
	char b[5];
	int width = 3;

	if (n == NULL) {
		return 0;
	}

	/* print color and key value */
	sprintf(b, "%c%02d", n->isRed ? 'R' : 'B', n->key);

	int left = print(n->left, 1, offset, depth + 1, treeStr);
	int right = print(n->right, 0, offset + left + width, depth + 1, treeStr);

	for (int i = 0; i < width; i++) {
		treeStr[2 * depth][offset + left + i] = b[i];
	}

	if (depth > 0 && isLeft) {
		for (int i = 0; i < width + right; i++) {
			treeStr[2 * depth - 1][offset + left + width / 2 + i] = '-';
		}

		treeStr[2 * depth - 1][offset + left + width / 2] = '+';
		treeStr[2 * depth - 1][offset + left + width + right + width / 2] = '+';
	}
	else if (depth > 0 && !isLeft) {
		for (int i = 0; i < left + width; i++) {
			treeStr[2 * depth - 1][offset - width / 2 + i] = '-';
		}
		treeStr[2 * depth - 1][offset + left + width / 2] = '+';
		treeStr[2 * depth - 1][offset - width / 2 - 1] = '+';
	}

	return left + width + right;
}

void printTree(hTree *t) {
	char treeStr[20][255];
	int height;
	hotel *root = t->root;
	for (int i = 0; i < 20; i++) {
		sprintf(treeStr[i], "%150s", " ");
	}

	print(root, 0, 0, 0, treeStr);
	height = heightPrint(root);

	for (int i = 0; i < height; i++) {
		printf("%s\n", treeStr[i]);
	}
	printf("\n");
}

/**
 * used when printing tree
 * add 1 to subtree height
 * because we print line between nodes
*/
int heightPrint(customer *n) {
	int r = 0, l = 0;
	if (n->right != NULL)
		r = heightPrint(n->right) + 1;
	if (n->left != NULL)
		l = heightPrint(n->left) + 1;
	return 1 + (r > l ? r : l);
}

int print(customer *n, int isLeft, int offset, int depth, char treeStr[20][255]) {
	char b[20];
	int width = 3;

	if (n == NULL) {
		return 0;
	}

	/* print color and key value */
	sprintf(b, "%c%15s", n->isRed ? 'R' : 'B', n->key);

	int left = print(n->left, 1, offset, depth + 1, treeStr);
	int right = print(n->right, 0, offset + left + width, depth + 1, treeStr);

	for (int i = 0; i < width; i++) {
		treeStr[2 * depth][offset + left + i] = b[i];
	}

	if (depth > 0 && isLeft) {
		for (int i = 0; i < width + right; i++) {
			treeStr[2 * depth - 1][offset + left + width / 2 + i] = '-';
		}

		treeStr[2 * depth - 1][offset + left + width / 2] = '+';
		treeStr[2 * depth - 1][offset + left + width + right + width / 2] = '+';
	}
	else if (depth > 0 && !isLeft) {
		for (int i = 0; i < left + width; i++) {
			treeStr[2 * depth - 1][offset - width / 2 + i] = '-';
		}
		treeStr[2 * depth - 1][offset + left + width / 2] = '+';
		treeStr[2 * depth - 1][offset - width / 2 - 1] = '+';
	}

	return left + width + right;
}

void printTree(cTree *t) {
	char treeStr[20][255];
	int height;
	customer *root = t->root;
	for (int i = 0; i < 20; i++) {
		sprintf(treeStr[i], "%150s", " ");
	}

	print(root, 0, 0, 0, treeStr);
	height = heightPrint(root);

	for (int i = 0; i < height; i++) {
		printf("%s\n", treeStr[i]);
	}
	printf("\n");
}
