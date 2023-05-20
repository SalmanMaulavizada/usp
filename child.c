#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include"header.h"












void childFunction(int (*readPipes)[2], int (*writePipes)[2], int i)
{
       close(readPipes[i][0]);
    close(writePipes[i][1]);
    char str[200];
    int n;
    char fileid[200];
    char num1[10];
    char num2[10];
    char opernd;
    char converted[5];
    read(writePipes[i][0], &n, sizeof(int));
    int x = read(writePipes[i][0], str, n);
    close(writePipes[i][0]);
    //printf("yo: %d\n", x);
    close(writePipes[i][0]);

   // printf("here it is: %s\n", str);
    int readed = 0;
    int fd = open(str, O_RDONLY);
    if (fd == -1)
    {
        printf("error opening file to read from\n");
    }
    while (read(fd, fileid + readed, 1) > 0)
    {
        if (fileid[readed] == '\n')
        {
            break;
        }
        readed++;
    }
    fileid[readed] = '\0';

    readed = 0;

    while (read(fd, num1 + readed, 1) > 0)
    {
        if (num1[readed] == '\n')
        {
            break;
        }
        readed++;
    }
    num1[readed] = '\0';

    read(fd, &opernd, 1);
    readed = 0;
    char p;
    read(fd, &p, 1);
    while (read(fd, num2 + readed, 1) > 0)
    {
        if (num2[readed] == '\n')
        {
            break;
        }
        readed++;
    }
    num2[readed] = '\0';

    //printf("fileid: %s\n", fileid);
   // printf("num1: %s\n", num1);
   // printf("opernd: %c\n", opernd);
   // printf("num2: %s\n", num2);

    int result = calculator(atoi(num1), atoi(num2), opernd);
    printf("answer is :%d\n", result);

    snprintf(converted, sizeof(converted), ":%d", result);
    strcat(fileid, converted);
    int length = strlen(fileid) + 1;
    write(readPipes[i][1], &length, sizeof(int));
    write(readPipes[i][1], fileid, strlen(fileid) + 1);
    close(readPipes[i][1]);
    


    exit(0);
}