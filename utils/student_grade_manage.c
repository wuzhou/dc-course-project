#include <stdio.h>
#include <string.h>
#include "student_grade_manage.h"


int insertGrade(Student student)
{
	int isSuccess = 0;
	FILE *fp;

	if((fp = fopen(DATAFILE, "a+")) == NULL){
		printf("Can't open %s\n", DATAFILE);
		return isSuccess;
	}

	fprintf(fp, "%s%c", student->student_id, student->grade);
	
	fclose(fp);
	return isSuccess;
}

char lookUpGrade(char *student_id)
{
	char grade = 'n';
	Student *student;
	FILE *fp;

	if((fp = fopen(DATAFILE, "a+")) == NULL){
		printf("Can't open %s\n", DATAFILE);
		return grade;
	}

	while(!feof(fp)){
		student = (Student *)malloc(sizeof(Student));
		fscanf(fp, "%s%c", &student->student_id, &student->grade);
		if(strcmp(student->student_id, student_id) == 0){
			grade = student->grade;
			break;
		}
	}

	return grade;
}
