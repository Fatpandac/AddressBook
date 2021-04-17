#ifndef FILE_H
#define FILE_H

#define MaxSize            100     //通讯录数组长度

/*
 * 简介：定义联系人以及通讯录结构体
 * 作者：Fatpandac
 * 时间：2020.03.26
 */

typedef struct Person
{
    char name[10];
    char address[20];
    int postCode;
    char sex;
    char email[20];
    char phoneNumber[12];
    int like;
}Person;        //联系人结构体

typedef struct PersonList
{
    Person person[MaxSize];
    int lenght;
}PersonList;

int SavePerson(PersonList PersonList,char systemLanguage[10]);
int ReadPerson(PersonList *PersonList,char systemLanguage[10]);

#endif