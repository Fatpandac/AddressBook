#include <stdio.h>
#include <stdlib.h>
#include "language.h"
#include "file.h"
#include "global.h"

/*
 * 简介：输出版本信息
 * 作者：Fatpandac
 * 时间：2021.04.18
 */

void DisplayVersion()
{
    printf("VERSION:%s\n",version);
}

/*
 * 简介：模糊查找
 * 作者：Fatpandac
 * 时间：2021.04.04
 */

int fuzzyFind(char cmpValue[20],char findValue[20])
{
    int i = 0,j = 0;
    while (cmpValue[i] != '\0')
    {
        if (cmpValue[i] == findValue[j])
        {
            i++;
            j++;
        }else{
            i = i - j + 1;
            j = 0;
        }
        if (findValue[j] == '\0') return 1;
    }
    return 0;
}

/*
 * 简介：输出模糊查找结果
 * 作者：Fatpandac
 * 时间：2021.04.04
 */
void DisplayFuzzyPerson(PersonList *PersonList,int findFuzzyIndex[MaxSize],int findFuzzyIndexLenght)
{
    printf("%-15s\t%-5s\t%-15s\t%-20s\t%-10s\t%-10s\t%s\n",language[33],language[34],language[35],language[36],language[37],language[38],language[39]);   //"联系人","性别","电话","电子邮箱","邮编","地址","关心"
    for (int i = 0;i < findFuzzyIndexLenght;i++)
    {
        printf("%-15s\t%-5c\t%-15s\t%-20s\t%-10d\t%-10s",PersonList->person[findFuzzyIndex[i]].name,PersonList->person[findFuzzyIndex[i]].sex,PersonList->person[findFuzzyIndex[i]].phoneNumber,PersonList->person[findFuzzyIndex[i]].email,PersonList->person[findFuzzyIndex[i]].postCode,PersonList->person[findFuzzyIndex[i]].address);
        printf("\t%s\n",(PersonList->person[findFuzzyIndex[i]].like == 1) ? language[40]:language[41]);   //"是" "否"
    }
}

/*
 * 简介：输出联系人信息
 * 作者：Fatpandac
 * 时间：2021.03.22
 */

int DisplayPerson(PersonList PersonList,int key,char systemLanguage[10])        //key 用于保存指定输出地址，为 -2、-1、其他 时分别表示为 不输出、全输出、输出对应
{
    if (PersonList.lenght <= 0 && key != -2) 
    {
        printf("%s\n",language[58]);
        return 0;
    }                              //在没有数据的时候输出
    if (key == -2) return 0;
    printf("%-15s\t%-5s\t%-15s\t%-20s\t%-10s\t%-10s\t%s\n",language[33],language[34],language[35],language[36],language[37],language[38],language[39]);   //"联系人","性别","电话","电子邮箱","邮编","地址","关心"
    if (key == -1){
        for (int i = 0;i < PersonList.lenght;i++)
        {
            printf("%-15s\t%-5c\t%-15s\t%-20s\t%-10d\t%-10s",PersonList.person[i].name,PersonList.person[i].sex,PersonList.person[i].phoneNumber,PersonList.person[i].email,PersonList.person[i].postCode,PersonList.person[i].address);
            printf("\t%s\n",(PersonList.person[i].like == 1) ? language[40]:language[41]);   //"是" "否"
        }
    }else{
        int i = key;
        printf("%-15s\t%-5c\t%-15s\t%-20s\t%-10d\t%-10s",PersonList.person[i].name,PersonList.person[i].sex,PersonList.person[i].phoneNumber,PersonList.person[i].email,PersonList.person[i].postCode,PersonList.person[i].address);
        printf("\t%s\n",(PersonList.person[i].like == 1) ? language[40]:language[41]);   //"是" "否"
    }
    return 0;
}

/*
 * 简介：重置通讯录
 * 作者：Fatpandac
 * 时间：2021.03.20
 */
int ResetPerson(PersonList *PersonList)
{
    PersonList->lenght = 0;
    Success();
    return 0;
}

/*
 * 简介：输出开发人员及版本信息
 * 作者：Fatpandac
 * 时间：2021.03.26
 */

void DisplayDevelopers()
{
    Clear();
    printf("MAIN PROGRAME\n");
    printf("---------------------\n");
    printf("Zheng TingFei\n\n");
    printf("OTHER PROGRAME\n");
    printf("---------------------\n");
    printf("Liu SiLi\nZhu TianWen\n\n");
    printf("TRANSLATION\n");
    printf("---------------------\n");
    printf("EN: Peng YuTing\n\n");
    DisplayVersion();
}

/*
 * 简介：设置程序语言以及显示开发人员操作
 * 作者：Fatpandac
 * 时间：2020.03.26
 */

int Setting(char systemLanguage[10])
{
    int choose;
    printf("%s\n%s\n%s"
           ,language[45]
           ,language[46]
           ,language[27]);    //"[1] 更改语言" "[2] 制作人员" "请输入相应序号："
    scanf("%d",&choose);
    if (choose != 1 && choose != 2)
    {
        printf("%s\n",language[28]);    //"输入错误,请重新输入"
        return 0;
    }
    if (choose == 1)
    {
        GetSelectLanguage(systemLanguage);
        LoadingLanguage(systemLanguage);
        printf("%s\n",language[47]);  //"更改成功"
        return 0;
    }else{
        DisplayDevelopers();
    }
    return 0;
}