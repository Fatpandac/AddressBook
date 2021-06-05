#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "language.h"
#include "file.h"
#include "global.h"

/*
 * 简介：检测性别输入是否正确
 */

int checkPersonSex(char personSex)
{
    return (toupper(personSex) == 'M' || toupper(personSex) == 'W') ? 1 : 0;
}

/*
 * 简介：检测电话号码以及邮编输入是否正确
 */

int checkPersonNumber(char inputNumber[15])
{
    int i = 0;
    while (inputNumber[i] != '\0')
    {
        if (inputNumber[i] < 48 || inputNumber[i++] > 58) return 0;
    }
    return 1;
}

/*
 * 简介：检测关心是否输入正确
 */

int checkPersonLike(char personLike)
{
    return (toupper(personLike) == 'Y' || toupper(personLike) == 'N') ? 1 : 0;
}

/*
 * 简介：模糊查找
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
 */

void DisplayFuzzyPerson(PersonList *PersonList,int findFuzzyIndex[MaxSize],int findFuzzyIndexLenght)
{
    printf(printTitleFormat,language[33],language[34],language[35],language[36],language[37],language[38],language[39]);   //"联系人","性别","电话","电子邮箱","邮编","地址","关心"
    for (int i = 0;i < findFuzzyIndexLenght;i++)
    {
        printf(printBodyFormat,PersonList->person[findFuzzyIndex[i]].name,PersonList->person[findFuzzyIndex[i]].sex,PersonList->person[findFuzzyIndex[i]].phoneNumber,PersonList->person[findFuzzyIndex[i]].email,PersonList->person[findFuzzyIndex[i]].postCode,PersonList->person[findFuzzyIndex[i]].address,(PersonList->person[findFuzzyIndex[i]].like == 1) ? language[40]:language[41]);
    }
}

/*
 * 简介：输出联系人信息
 */

int DisplayPerson(PersonList PersonList,int key,char systemLanguage[10])        //key 用于保存指定输出地址，为 -2、-1、其他 时分别表示为 不输出、全输出、输出对应
{
    if (PersonList.length <= 0 && key != -2) 
    {
        printf("%s\n",language[58]);
        return 0;
    }                              //在没有数据的时候输出
    if (key == -2) return 0;
    printf(printTitleFormat,language[33],language[34],language[35],language[36],language[37],language[38],language[39]);   //"联系人","性别","电话","电子邮箱","邮编","地址","关心"
    if (key == -1){
        for (int i = 0;i < PersonList.length;i++)
        {
            printf(printBodyFormat,PersonList.person[i].name,PersonList.person[i].sex,PersonList.person[i].phoneNumber,PersonList.person[i].email,PersonList.person[i].postCode,PersonList.person[i].address,(PersonList.person[i].like == 1) ? language[40]:language[41]);
        }
    }else{
        int i = key;
        printf(printBodyFormat,PersonList.person[i].name,PersonList.person[i].sex,PersonList.person[i].phoneNumber,PersonList.person[i].email,PersonList.person[i].postCode,PersonList.person[i].address,(PersonList.person[i].like == 1) ? language[40]:language[41]);
    }
    return 0;
}

/*
 * 简介：重置通讯录
 */

int ResetPerson(PersonList *PersonList)
{
    PersonList->length = 0;
    Success();
    return 0;
}

/*
 * 简介：输出版本信息
 */

void DisplayVersion()
{
    printf("VERSION:%s\n",version);
}


/*
 * 简介：输出开发人员及版本信息
 */

void DisplayDevelopers()
{
    Clear();
    printf("MAIN PROGRAME\n");
    printf("---------------------\n");
    printf("Zheng TingFei\n\n");
    printf("OTHER PROGRAME\n");
    printf("---------------------\n");
    printf("Liu SiLi\nZhu TianWen\nPeng YuTing\n\n");
    DisplayVersion();
}

/*
 * 简介：设置程序语言以及显示开发人员操作
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
