#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "student_grade_manage.h"


 void FreeStudentList(Student *student) {
    Student *tmp;
    while(1) {
        tmp = student->next;
        free(student);
        student= tmp;
        if(student == NULL) {
            break;
        }
    }
}


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

    student = (Student *)malloc(sizeof(Student));
	while(1){
		fscanf(fp, "%3d%c", &student->student_id, &student->grade);
		//printf("%d .. %c\n", student->student_id, student->grade);
		if(feof(fp)) {
            break;
        }
        if(student->student_id == student_id){
			grade = student->grade;
			break;
		}
	}
    free(student);
    fclose(fp);

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
        FreeStudentList(studentList);
		return isSuccess;
	}

	Student *lastStudent = NULL;
	while(1){
        newStudent = (Student *)malloc(sizeof(Student));
		fscanf(fp, "%3d%c", &newStudent->student_id, &newStudent->grade);
        if(feof(fp)) {
            //feof(fp) is true when you are at EOF ANNNNND you actually try to read
            free(newStudent);       //garbage data and not in the linklist, free here
            break;
        }
		printf("Reads:\tStudent:%d\tGrade:%c\n", newStudent->student_id, newStudent->grade);
		if(newStudent->student_id == student->student_id){
			newStudent->grade = student->grade;
		}
        
        // do this to avoid the bug lead by wrong eof?
		//newStudent->next = studentList->next;
		//studentList->next = newStudent;

        //why not fix the bug and keep things in place:)
        if(studentList->next == NULL) {
            //link to studentList if it's the first node
            studentList->next = newStudent;
            lastStudent = newStudent;
        }
        lastStudent->next = newStudent;
        lastStudent = newStudent;
        lastStudent->next = NULL;   //avoid garbage
	}
	fclose(fp);

	if((fp = fopen(DATAFILE, "w")) == NULL){
		printf("Can't write %s\n", DATAFILE);
        FreeStudentList(studentList);
		return isSuccess;
	}

	//newStudent is just a pointer to existing elements, why need to malloc here..
    //newStudent = (Student *)malloc(sizeof(Student));
    
    //is the next->next because stulist->next pts to a student(0,0)
    //due to while(feof(fp)) leads 1 extra read?
	//newStudent = studentList->next->next;
    newStudent = studentList->next;    //list has a dummy header, next is first element
	while(newStudent){
		printf("Writes:\tStudent:%d\tGrade:%c\n", newStudent->student_id, newStudent->grade);
		fprintf(fp, "%03d%c\n", newStudent->student_id, newStudent->grade);
		newStudent = newStudent->next;
	}
	fclose(fp);
	isSuccess = 1;
    
    FreeStudentList(studentList);
	return isSuccess;
}

