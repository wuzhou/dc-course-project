#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "student_grade_manage.h"

int main()
{
	Student *student = (Student *)malloc(sizeof(Student));
	student->student_id = 124;
	student->grade = 'B';
//	insertGrade(student);
	updateGrade(student);
	char result = lookUpGrade(124);
	printf("Grade is %c\n", result);
	return 0;
}
