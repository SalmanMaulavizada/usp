#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include"header.h"







void parentFunction(char *filename, int (*writePipes)[2], int (*readPipes)[2], int i)
{
    close(writePipes[i][0]);
    close(readPipes[i][1]);
    int n = strlen(filename) + 1;
    int length;
    char fileid[20];
    int fd;
    fd = open("result.txt", O_APPEND | O_CREAT | O_WRONLY, 0777);
    write(writePipes[i][1], &n, sizeof(int));
    ssize_t x = write(writePipes[i][1], filename, strlen(filename) + 1);
    close(writePipes[i][1]);
    //printf("%ld : wrote\n", x);
    read(readPipes[i][0], &length, sizeof(int));
    //printf("length: %d\n", length);
    //printf("%ld\n", 
    read(readPipes[i][0], fileid, length);
    close(readPipes[i][0]);
    //printf("fileid is : %s\n", fileid);
    fileid[length - 1] = '\0';
    //printf("%ld", 
    write(fd, fileid, strlen(fileid));
    write(fd, "\n", 1);
}