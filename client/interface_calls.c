#include <stdio.h>
#include <fcntl.h>
#define kMaxReadLength 16

char *write_pipe = "/tmp/client_interface";
char *read_pipe = "/tmp/interface_client";

char buf[kMaxReadLength];

char interface_lookup_grade(int id) {
    int write_fd = open(write_pipe, O_WRONLY);
    sprintf(buf, "%3d*", id);
    printf("dbg: buf is:%s\n", buf);
    fflush(stdout);
    write(write_fd, buf, kMaxReadLength);
    close(write_fd);

    int read_fd = open(read_pipe, O_RDONLY);
    read(read_fd, buf, kMaxReadLength);
    char result;
    sscanf(buf, "%c", &result);
    return result;
}

char interface_update_grade(int id, char grade) {
    //returns 1 if successful
    //0 if not
    int write_fd = open(write_pipe, O_WRONLY);
    sprintf(buf, "%3d%c", id, grade);
    write(write_fd, buf, kMaxReadLength);
    close(write_fd);

    int read_fd = open(read_pipe, O_RDONLY);
    read(read_fd, buf, kMaxReadLength);
    char result;
    sscanf(buf, "%c", &result);
    return result;
}

