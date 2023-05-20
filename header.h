#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

void parentFunction(char *filename, int (*writePipes)[2], int (*readPipes)[2], int i);
void childFunction(int (*readPipes)[2], int (*writePipes)[2], int i);


int calculator(int num1, int num2, char operand);