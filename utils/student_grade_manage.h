#define SIDLEN 3
#define DATAFILE "gradedata.dat"

struct StudentSt
{
	int student_id; //length is 3
	char grade;
	struct StudentSt *next;
};

typedef struct StudentSt Student;

//Functions for managing students' grades
int insertGrade(Student *);
int updateGrade(Student *);
char lookUpGrade(int);
