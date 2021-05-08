#include <stdio.h>
#include "file.h"
#include "language.h"

/*
 * 简介：将数据保存到文件中
 */

int SavePerson(PersonList PersonList,char systemLanguage[10])
{
    FILE *savePerson = fopen("AddressBook.txt","wb");
    if (savePerson == NULL)
    {
        printf("%s\n",language[43]);    //"写入失败"
        return 0;
    }
    fprintf(savePerson,"%s\n%d\n",systemLanguage,PersonList.lenght);
    for (int i = 0;i < PersonList.lenght;i++)
    {
        fprintf(savePerson,"%s\t%c\t%s\t%s\t%d\t%s\t%d\n",PersonList.person[i].name,PersonList.person[i].sex,PersonList.person[i].phoneNumber,PersonList.person[i].email,PersonList.person[i].postCode,PersonList.person[i].address,PersonList.person[i].like);
    }
    fclose(savePerson);
    return 0;
}

/*
 * 简介：读取文件获取到通讯录数据
 */

int ReadPerson(PersonList *PersonList,char systemLanguage[10])
{
    FILE *readPerson = fopen("AddressBook.txt","rb");
    if (readPerson == NULL)
    {
        /*读取失败 进入初始化并生成 AddressBook.txt */
        FILE *saveFile = fopen("AddressBook.txt","wb");
        fprintf(saveFile,"%s\n%d\n","ZH-CN.txt",0);
        fclose(saveFile);
        readPerson = fopen("AddressBook.txt","rb");
    }
    fscanf(readPerson,"%s\n%d\n",systemLanguage,&PersonList->lenght);
    for (int i = 0;i < PersonList->lenght;i++)
    {
        fscanf(readPerson,"%s\t%c\t%s\t%s\t%d\t%s\t%d\n",PersonList->person[i].name,&PersonList->person[i].sex,PersonList->person[i].phoneNumber,PersonList->person[i].email,&PersonList->person[i].postCode,PersonList->person[i].address,&PersonList->person[i].like);
    }
    fclose(readPerson);
    return 0;
}