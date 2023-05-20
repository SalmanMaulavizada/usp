#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include"header.h"



//void parentFunction(char *filename, int (*writePipes)[2], int (*readPipes)[2], int i);
//void childFunction(int (*readPipes)[2], int (*writePipes)[2], int i);
//int calculator(int num1, int num2, char operand);

int main()
{
    remove("result.txt");
    int uspFileCount = 0;
    int filecount = 0;
    DIR *directory = opendir(".");
    if (directory == NULL)
    {
        printf("error when opening directory\n");
    }

    DIR *directoryCheck = opendir(".");
    if (directoryCheck == NULL)
    {
        printf("error when opening directory\n");
    }

    struct dirent *file;
    struct dirent *filecheck;
    while ((filecheck = readdir(directoryCheck)) != NULL)
    {
        filecount++;
    }

    char **array = malloc(filecount * sizeof(char *));
    for (int i = 0; i < filecount; i++)
    {
        array[i] = malloc(20 * sizeof(char));
    }
    int i = 0;

    while ((file = readdir(directory)) != NULL)
    {
        char *end = strrchr(file->d_name, '.');
        if (end != NULL && strcmp(end, ".usp") == 0)
        {
            strcpy(array[i], file->d_name);
            i++;
        }
    }

    uspFileCount = i;
    printf("%d\n", uspFileCount);

    int(*readPipes)[2] = malloc(sizeof(*readPipes) * uspFileCount);
    int(*writePipes)[2] = malloc(sizeof(*writePipes) * uspFileCount);

    for (i = 0; i < uspFileCount; i++)
    {
        if (pipe(writePipes[i]) == -1)
        {
            printf("error with write pipe %d\n", i);
        }

        if (pipe(readPipes[i]) == -1)
        {
            printf("error with read pipe %d\n", i);
        }
    }

    for (i = 0; i < uspFileCount; i++)
    {
        __pid_t pid = fork();

        if (pid == -1)
        {
            printf("forking error\n");
        }

        else if (pid > 0)
        {
            parentFunction(array[i], writePipes, readPipes, i);
            printf("parent here: %d\n", i);

            wait(NULL);
            printf("Child:%d is done\n",i);
        }

        else if (pid == 0)
        {
            printf("child made: %d\n", i);
            childFunction(readPipes, writePipes, i);
        }
    }

    for (i = 0; i < filecount; i++)
    {

        free(array[i]);
    }

    closedir(directory);
    closedir(directoryCheck);

    free(array);

    free(readPipes);
    free(writePipes);
}

int calculator(int num1, int num2, char operand)
{
    int result;
    if (operand == '-')
    {
        result = num1 - num2;
    }
    else if (operand == '/')
    {
        result = num1 / num2;
    }
    else if (operand == '*')
    {
        result = num1 * num2;
    }
    else if (operand == '+')
    {
        result = num1 + num2;
    }
    else
    {
        printf("error calculating\n");
    }
    return result;
}
