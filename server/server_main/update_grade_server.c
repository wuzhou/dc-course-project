#include <stdio.h>
#include "update_grade.h"
#include "server_main.h"

char DoUpdate(StudentSt *stu) {
    //debug
    //printf("Doupdate receives: id %d grade %c\n", stu->student_id, stu->grade);
    updateGrade(stu);
    extern int pipefd;
    do {
        printf("Primary server receives student_id=%3d from client\n", stu->student_id);
        printf("His/Her grade is %c\n", stu->grade);
        // printf("gonna write to pipe\n");
        int temp_bytes_written = write(pipe_fd[1], stu, sizeof(StudentSt));
        //printf("writting finished %d bytes written\n", temp_bytes_written);
        //printf("sizeof(studentst) is %ld\n", sizeof(StudentSt));
        stu = stu->next;
    } while(stu != NULL);
    //printf("quit from DoUpdate\n");
}

char* updategrade_1_svc(StudentSt *argp, struct svc_req *rqstp) {
    static char result;
    DoUpdate(argp);

    return &result;
}
