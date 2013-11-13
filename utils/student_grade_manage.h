#define SIDLEN 10
#define DATAFILE "gradedata.dat"

struct StudentSt
{
	char student_id[SIDLEN];
	char grade;
};

typedef struct StudentSt Sudent;

//Functions for managing students' grades
int insertGrade(Sudent);
int updateGrade(Sudent);
char lookUpGrade(char *);
