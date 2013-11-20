#define SIDLEN 3
#define DATAFILE "gradedata.dat"

#ifndef student_struct
#define student_struct
struct StudentSt
{
	int student_id; //length is 3
	char grade;
	struct StudentSt *next;
};
typedef struct StudentSt Student;
typedef struct StudentSt StudentSt;
#endif

//Functions for managing students' grades
int insertGrade(Student *);
int updateGrade(Student *);
char lookUpGrade(int);
void FreeStudentList(StudentSt *);
