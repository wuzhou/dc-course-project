#include <stdio.h>
#include <stdlib.h>

void menu();

int main()
{
	char host[] = "localhost";
    printf("**************\n");
	printf("Welcome!\n");
	printf("**************\n");

	menu();

    int id;
    char grade;

	int choice;
	while(1){
		printf("Chose a menu number(9 to show menu): ");
		scanf("%d", &choice);
        getchar(); //clear "\n" in buffer

		switch(choice){
			case 1:
				//do something
                printf("The student_id to look up: \n");
                scanf("%3d", &id);
                getchar();
                char grade = interface_lookup_grade(id);
                printf("Student %3d has grade %c\n", id, grade);
				break;
			case 2:
				//do somthing
                printf("Student id: \n");
                scanf("%3d", &id);
                getchar(); //to clear "\n" in buffer
                printf("Student %3d 's grade is(Pls be nice, prof~):\n", id);
                scanf("%c", &grade);
                getchar();  //same
                //UpdateGrade(host, student); //removed for test nov22
                interface_update_grade(id, grade);
				break;
			case 0:
				exit(0);
				break;
            case 9:
                menu();
                break;
			default:
				printf("Invalid input. Behave yourself:)\n");
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

