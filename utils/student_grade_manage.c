#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "student_grade_manage.h"


int insertGrade(Student *student)
{
	int isSuccess = 0;
	FILE *fp;

	if((fp = fopen(DATAFILE, "a+")) == NULL){
		printf("Can't open %s\n", DATAFILE);
		return isSuccess;
	}
	printf("%d .. %c\n", student->student_id, student->grade);
	fprintf(fp, "%3d%c", student->student_id, student->grade);
	
	fclose(fp);
	return isSuccess;
}

char lookUpGrade(int student_id)
{
	char grade = 'n';
	Student *student;
	FILE *fp;

	if((fp = fopen(DATAFILE, "r")) == NULL){
		printf("Can't open %s\n", DATAFILE);
		return grade;
	}

	while(!feof(fp)){
		student = (Student *)malloc(sizeof(Student));
		fscanf(fp, "%3d%c", &student->student_id, &student->grade);
		printf("%d .. %c\n", student->student_id, student->grade);
		if(student->student_id == student_id){
			grade = student->grade;
			break;
		}
	}

	return grade;
}

int updateGrade(Student *student)
{
	int isSuccess = 0;
	Student *studentList = (Student *)malloc(sizeof(Student));
	studentList->next = NULL;
	Student *newStudent;
	FILE *fp;

	if((fp = fopen(DATAFILE, "r")) == NULL){
		printf("Can't read %s\n", DATAFILE);
		return isSuccess;
	}

	while(!feof(fp)){
		newStudent = (Student *)malloc(sizeof(Student));
		fscanf(fp, "%3d%c", &newStudent->student_id, &newStudent->grade);
		printf("r : %d .. %c\n", newStudent->student_id, newStudent->grade);
		if(newStudent->student_id == student->student_id){
			newStudent->grade = student->grade;
		}
		newStudent->next = studentList->next;
		studentList->next = newStudent;
	}
	fclose(fp);

	if((fp = fopen(DATAFILE, "w")) == NULL){
		printf("Can't write %s\n", DATAFILE);
		return isSuccess;
	}

	newStudent = (Student *)malloc(sizeof(Student));
	newStudent = studentList->next->next;
	while(newStudent){
		printf("p : %d .. %c\n", newStudent->student_id, newStudent->grade);
		fprintf(fp, "%3d%c", newStudent->student_id, newStudent->grade);
		newStudent = newStudent->next;
	}
	fclose(fp);
	isSuccess = 1;

	return isSuccess;
}

