#include <stdio.h>
#include <stdlib.h>

void menu();

int main()
{
	printf("**************\n");
	printf("Welcome!\n");
	printf("**************\n");

	menu();

	int choice;
	while(1){
		printf("Chose a menu number: ");
		scanf("%d", &choice);

		switch(choice){
			case 1:
				//do something
				break;
			case 2:
				//do somthing
				break;
			case 0:
				exit(0);
				break;
			default:
				printf("Please chose a right menu number.");
		}
	}
	return 0;
}

void menu()
{
	printf("1. Look up Grade.\n");

	printf("2. Update Grade.\n");
	
	printf("0. Exit.\n");
}
