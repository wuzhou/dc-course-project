#include "server_main.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char** argv) {
    const char true = 1;
    const char false = 0;
    const int kMaxReadLength = sizeof(StudentSt);
    char read_buf[kMaxReadLength];
    char peer_server[32] = "";
    int listen_updategrade_pid;
    int listen_lookupgrade_pid;
    int listen_mainupdate_pid;
    char has_new = 0;   //whether has new updates to backup
    int syncfail_count = 0;
    int update_count = 0;   //primary fails after three updates, this is the counter.

    //check argument validity
    if(argc != 3) {
        printf("Usage: server [mode] peer_server_address\n");
        printf("mode=p: primary \t mode=b:backup\n");
        return 0;
    }

    //address of the peer server
    strcpy(peer_server, argv[2]);

    switch(argv[1][0]) {
        case 'p':
            break;
        case 'b':
        i_know_its_dirty:         
            if((listen_mainupdate_pid = fork()) == 0) {
                //in child process
                listen_mainserver_update();
            }
            else {
                //in main process
                listen_mainserver_failure();
                kill(listen_mainupdate_pid, SIGKILL);
                printf("My turn to become primary!\n");
            }
            printf("-----------Main server fail detected-----------\n");
            printf("Switched to main server mode\n");
            break;
        default:
            printf("Usage: server [mode]\n");
            printf("mode=:m primary \t mode=b:backup\n");
            return 0;
    }


    if(pipe(pipe_fd) < 0) {
        printf("not able to create pipe\n");
        return -1;
    }

    //int flags;
    //set pipe to be non-blocking
    if(fcntl(pipe_fd[0], F_SETFL, O_NONBLOCK) < 0) {
        printf("not able to set pipe props\n");
        return -1;
    }

    if((listen_updategrade_pid = fork()) == 0) {
        //in child, process 1
        listen_client_update();
    } else if((listen_lookupgrade_pid = fork()) == 0) {
        //in child, process 2
        listen_client_lookup();
    } else {
        //in parent
        //first student in list
        StudentSt *student_list = NULL;      
        
        //last student in un-backuped student list
        //need this one if sync fails, and some new updates from client
        StudentSt *current_student = NULL; 
        while(1) {
            while( read(pipe_fd[0], read_buf, kMaxReadLength) >0 ) {
                //client sent some update requests
                //printf("new data in pipe detected\ndata:%3d\n",(int) (*read_buf));
                has_new = true;
                if(!current_student){   //no students in list
                    current_student = (StudentSt*)malloc(sizeof(StudentSt));
                    student_list = current_student;
                } else {                //list non-emtpy, append
                    current_student->next = (StudentSt*)malloc(sizeof(StudentSt));
                    current_student = current_student->next;
                }

                current_student->next = NULL;
                //read_buf is in fact a StudentSt
                current_student->student_id = ((StudentSt*)read_buf)->student_id;
                current_student->grade = ((StudentSt*)read_buf)->grade;

                //debug
                //printf("new arrival: id: %d grade: %c\n", 
                 //      current_student->student_id, 
                 //      current_student->grade);
            } //inner while ends
            
            if(has_new) {
                //needs to sync to bakcup
                if(post_update("localhost", student_list)) {
                    //sync successful, cleanup
                    FreeStudentList(student_list);
                    has_new = false;
                    student_list = NULL;
                    current_student = NULL;
                    printf("updates sync-ed with bakcup server\n");
                    update_count++;
                    if(update_count >= 3) {
                        update_count = 0;
                        syncfail_count = 0; //will become backup, reset counters
                        kill(listen_lookupgrade_pid, SIGKILL);
                        kill(listen_updategrade_pid, SIGKILL);
                        post_failure(peer_server);
                        close(pipe_fd[0]);
                        close(pipe_fd[1]);
                        printf("Primary server says goodbye to the evil world.\n\n");
                        printf("Restarting as backup\n");
                        printf("Recovering..........Takes 30 secs.\n");
                        sleep(30);
                        printf("I'm here as the bakcup!\n");
                        printf("--------------------------------------------\n\n");
                        goto i_know_its_dirty;
                        exit(0);//not reached
                    }
                } else {
                    //sync failed, pass~will retry next time
                    //retry limit is 3. After that, save the update for next time
                    syncfail_count ++;
                    if(syncfail_count >= 3) {
                        //limit reached
                        printf("Backup server seems unreachable at the moment.\n");
                        has_new = false;
                        syncfail_count = 0;
                    }
                }
            }
        }
    }
}
