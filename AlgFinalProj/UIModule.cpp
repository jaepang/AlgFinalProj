#include <stdio.h>
#include <string.h>
#include "UIModule.h"
#include "customer.h"

userinfo *initUI(cTree *tree) {
	userinfo *user;
	char *cmd;
	int cmdI;
	printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
	printf("@                                                            @\n");
	printf("@       Welcome to SKKU TRAVEL RECOMMENDATION SERVICE!       @\n");
	printf("@                                                            @\n");
	printf("@     Before Starting, we'll ask some information of you     @\n");
	printf("@                                                            @\n");
	printf("@     If you agree collecting your information, PRESS Y!     @\n");
	printf("@                                                            @\n");
	printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
	printf("\n\n>>   둘 중에 하나만 골라 Yes or Yes! (Y/N): ");

	while (1) {
		scanf("%s", cmd);
		if (strcmp(cmd, "Y") == 0 || strcmp(cmd, "y") == 0) {
			break;
		}
		else if (strcmp(cmd, "N") == 0 || strcmp(cmd, "n")) {
			printf("OK, Bye...............\n");
			return NULL;
		}
		else {
			printf("Wrong Input! please input again..\n");
		}
	}

	printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
	printf("@                                                            @\n");
	printf("@            THANK YOU for chosing our sercive!!!            @\n");
	printf("@                                                            @\n");
	printf("@                Now, Please fill the format.                @\n");
	printf("@            And the recommendation program start!           @\n");
	printf("@                                                            @\n");
	printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
	
	while (1) {
		printf("\n\n>>   Type your ID, please (string): ");
		scanf("%s", cmd);
		if (search(tree, cmd) == NULL) {
			printf("\n     ※ ERROR: ID ALREADY EXISTS!!!\n");
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
