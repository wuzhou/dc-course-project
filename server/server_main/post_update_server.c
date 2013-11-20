/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "post_update.h"
#include "server_main.h"

void test(StudentSt *stu) {
 
    updateGrade(stu);
    do {
        printf("Server receives student_id=%d\n", stu->student_id);
        printf("His/Her grade is %c\n", stu->grade);
        stu = stu->next;
    } while(stu != NULL);
}

int *
postupdate_1_svc(StudentSt *argp, struct svc_req *rqstp)
{
	static int  result;
    test(argp);
	/*
	 * insert server code here
	 */

	return &result;
}
