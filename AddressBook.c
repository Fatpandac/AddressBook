/*
 * 简介：程序基本框架
 * 作者：Fatpandac
 * 时间：2021.03.14
 *
 */

#include <stdio.h>

#define Ture 1
#define Flase 0
#define MaxSize 100

typedef struct
{
    char sex;
    char name[10];
    char email[20];
    char address[20];
    char phoneNumber[12];
    int like;
    int postCode;
}Person;

int main(int argc,char *argv[])     //argc 输入参数数量； argv 输入的参数
{
    Person person[MaxSize];
    return 0;
}
