#include <stdio.h>
#include "interface.h"
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <pthread.h>
#include <string.h>

char* read_pipe = "/tmp/client_interface";
char* write_pipe = "/tmp/interface_client";
char server1[32] = "";
char server2[32] = "";
char* primary_server;
char fail_flag = 0; //flag for server fail event

void *listen_client();
void *listen_server();

int main(int argc, char* argv[]) {

    if(argc != 3) {
        printf("Usage:\ninterface primary_server backup_server\n");
        exit(0);
    }
    
    strcpy(server1, argv[1]);
    strcpy(server2, argv[2]);

    printf("Interface Running!\n");
    printf("Main server: %s\n", server1);
    printf("Backup server :%s\n", server2);


    
    primary_server = server1;

    pthread_t listen_client_thread, listen_server_thread;
    unlink(read_pipe); //remove existing file
    unlink(write_pipe);

    mkfifo(read_pipe, 0777);   //gen pipe
    mkfifo(write_pipe, 0777);

    pthread_create(&listen_client_thread, NULL, listen_client, NULL);
    pthread_create(&listen_client_thread, NULL, listen_server, NULL);


    while(1) {
        if(fail_flag) {
            printf("server fail detected!\n");
            fail_flag = 0;
            if(primary_server == server1) {
                primary_server = server2;
            } else {
                primary_server = server1;
            }
        }
    }


    printf("I shouldn't be here, damn.\n");
    exit(1);
}

void *listen_client() {
    while(1) {  
        int read_pipe_fd = open(read_pipe, O_RDONLY);
        const int kMaxReadLength = 8;
        char buf[kMaxReadLength];
        int id;
        char grade;
        read(read_pipe_fd, buf, kMaxReadLength);
        sscanf(buf, "%3d%c", &id, &grade);
        int write_pipe_fd = open(write_pipe, O_WRONLY);
        if(grade == '*') {  //lookup
           grade = lookup_grade(primary_server, id);
           sprintf(buf, "%c", grade);
           write(write_pipe_fd, buf, kMaxReadLength);
           
        } else {    //update
            printf("updaterequest %3d %c  target:%s \n", id, grade, primary_server);
            StudentSt* student = (StudentSt*) malloc(sizeof(StudentSt));
            student->next = NULL;
            student->student_id = id;
            student->grade = grade;
            UpdateGrade(primary_server, student);
            free(student);
        }
        close(read_pipe_fd);
        close(write_pipe_fd);
    }
}

void* listen_server(void) {
    run_postfailure_svc();
}

