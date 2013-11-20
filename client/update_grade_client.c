#include <stdio.h>
#include "update_grade.h"

char UpdateGrade(char *host, StudentSt* student) {
    CLIENT *clnt;
    char  *result_1;
    StudentSt  updategrade_1_arg;
    #ifndef DEBUG
        clnt = clnt_create (host, UPDATEGRADE_PROG, UPDATEGRADE_VERS, "udp");
        if (clnt == NULL) {
            clnt_pcreateerror (host);
            exit (1);
        }
    #endif

    result_1 = updategrade_1(student, clnt);
    if(result_1 == NULL) {
        clnt_perror(clnt, "call failed");
    }

    #ifndef DEBUG
        clnt_destroy(clnt);
    #endif
    return *result_1; 
}

/*
int main(void) {
    int student_id;
    char grade;
    StudentSt stu = {1, 'A', NULL};

    while(1) {
        scanf("%3d", &student_id);
        scanf("%c", &grade);
        stu.student_id = student_id;
        stu.grade = grade;
        stu.next = NULL;
        grade = UpdateGrade("localhost", &stu);
    }

}*/
