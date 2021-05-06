#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "language.h"
#include "file.h"
#include "cliFunc.h"
#include "global.h"

Opt optList[CmdSize] = {    
    {"help","-h","[help | -h] <option>\nDisplay all help when option is null or <option> help\n",3,HelpOpt},
    {"help","-h","[help | -h]\nDisplay all help\n",2,HelpOpt},
    {"add","-a","[add | -a] <name> <sex | M/w> <phone number> <email> <postcode> <address> <like | Y/n>\nCreate a new contact\n",9,AddOpt},
    {"list","-ls","[list | -ls]\nDisplay you AddressBook\n",2,ViewOpt},
    {"find","-f","[find | -f] <by element> <value>\nFind the element of the value,start with \"/\" for fuzzy search\n[by element | name | address]\n",4,FindOpt},
    {"remove","-rm","[remove | -rm] <name>\nRemove <name>'s contact\n",3,RemoveOpt},
    {"share","-s","[share | -s] <name>\nShare contact with card\n",3,ShareOpt},
    {"change","-chg","[change | -chg] <name> <element> <value>\nChange the value of the element\n[element | name | sex | phoneNumber | email | address | postCode | like]\n",5,ChangeOpt},
    {"change","-chg","[change | -chg] <name> <element> <value>\nChange the value of the element\n[element | name | sex | phoneNumber | email | address | postCode | like]\n",4,ChangeOpt},
    {"reset","","[reset]\nReset you AddressBook\n",2,ResetOpt},
    {"version","-v","[version | -v]\nDisplay version",2,VersionOpt}
};      //CLI操作数据

/*
 * 简介：用于判断CLI并返回相应操作函数序号
 * 作者：Fatpandac
 * 时间：2021.03.20
 */

int GetOpt(int argc,char *argv[])
{
    for(int i = 0;i < CmdSize;i++)
    {
        if (optList[i].countArgument == argc)
        {
            if (!strcmp(optList[i].longOptName,argv[1]) || !strcmp(optList[i].shortOptName,argv[1]))
            {
                return optList[i].code;
            }
        }
    }
    for (int i = 0;i < CmdSize;i++)
    {
        if (!strcmp(optList[i].longOptName,argv[1]) || !strcmp(optList[i].shortOptName,argv[1]))
        {
            printf("%s",optList[i].optGuide);
            return 0;
        }
    }
    printf("%s\n",language[0]); //"错误命令！！！\n"
    return 0;
}

/*
 * 简介：输出CLI的操作指南
 * 作者：Fatpandac
 * 时间：2021.03.20
 */

void PrintHelp(int argc,char *argv[])
{
    if (argc == 3)
    {
        for (int i = 0;i < CmdSize;i++)
        {
            if (!strcmp(optList[i].longOptName,argv[2]) || !strcmp(optList[i].shortOptName,argv[2]))
            {
                printf("%s\n",optList[i].optGuide);
                break;
            }else if (i+1 == CmdSize){
                printf("%s\n",language[15]);
            }
        }
    }else{
        for (int i = 0;i < CmdSize;i++)
        {
            printf("%s\n",optList[i].optGuide);
            if (!strcmp(optList[i].longOptName,optList[i+1].longOptName))
            {
                i++;
            }
        }
    }
}

/*
 * 简介：通过CLI添加联系人
 * 作者：Fatpandac
 * 时间：2021.04.18
 */

int CLIAddPerson(PersonList *PersonList,int argc,char *argv[])
{
    if ((toupper(argv[3][0]) == 'M' || toupper(argv[3][0]) == 'W') && (tolower(argv[8][0]) == 'y' || tolower(argv[8][0]) == 'n')) //对 sex 和 like 输入进行判断是否为合法输入
    {
        strcpy(PersonList->person[PersonList->lenght].name,argv[2]);
        PersonList->person[PersonList->lenght].sex = toupper(argv[3][0]);
        strcpy(PersonList->person[PersonList->lenght].phoneNumber,argv[4]);
        strcpy(PersonList->person[PersonList->lenght].email,argv[5]);
        PersonList->person[PersonList->lenght].postCode =  atoi(argv[6]);
        strcpy(PersonList->person[PersonList->lenght].address,argv[7]);
        PersonList->person[PersonList->lenght].like = (tolower(argv[8][0]) == 'y') ? 1 : 0 ;
        PersonList->lenght++;
    }else{
        printf("%s\n",language[28]);
    }

    return 0;
}

/*
 * 简介：通过CLI查找相应元素对应值并返回
 * 作者：Fatpandac
 * 时间：2021.04.18
 */

int CLIFindPerson(PersonList *PersonList,int argc,char *argv[])
{
    char findElement[10],findValue[20];
    int findElementKey;
    int findFuzzyIndex[MaxSize];     //保存模糊查找结果 index 数组
    int findFuzzyIndexLenght = 0;         //记录 findFuzzyIndex 长度
    strcpy(findElement,argv[2]);
    strcpy(findValue,argv[3]);
    if (findValue[0] == '/'){
        strncpy(findValue,findValue+1,strlen(findValue));        //消除模糊匹配区别符
        for (int j = 0,k = 0;j < PersonList->lenght;j++)
        {
            if (!strcmp(findElement,"name"))
            {   
                if (fuzzyFind(PersonList->person[j].name,findValue))
                {
                    findFuzzyIndex[k++] = j;
                    findFuzzyIndexLenght++;
                }
            }else if (!strcmp(findElement,"address")){
                if (fuzzyFind(PersonList->person[j].address,findValue))
                {
                    findFuzzyIndex[k++] = j;
                    findFuzzyIndexLenght++;
                }
            }
        }
        (findFuzzyIndexLenght == 0) ? printf("%s\n",language[42]) : DisplayFuzzyPerson(PersonList,findFuzzyIndex,findFuzzyIndexLenght);
        return -2;
    }else{
        for (int i = 0;i < PersonList->lenght;i++)
        {
            if (!strcmp(findElement,"name"))
            {
                if (!strcmp(PersonList->person[i].name,findValue))
                {
                    return i;
                }
            }else if (!strcmp(findElement,"address")){
                if (!strcmp(PersonList->person[i].name,findValue))
                {
                    return i;
                }
            }
        }
    }
    printf("%s\n",language[42]);
    return -2;
}

/*
 * 简介：通过CLI删除联系人
 * 作者：Fatpandac
 * 时间：2021.03.22
 */

int CLIRemovePerson(PersonList *PersonList,int argc,char *argv[])
{
    char mvName[10];        //存储被删除人姓名
    int removeLenght = 0;      //删除后长度
    strcpy(mvName,argv[2]);
    for (int i = 0;i < PersonList->lenght;i++)
    {
        if (strcmp(PersonList->person[i].name,mvName))
        {
           PersonList->person[removeLenght++] = PersonList->person[i];
        }    
    }  
    if (removeLenght == PersonList->lenght){
            printf("%s\n",language[42]);
    }else{
            PersonList->lenght = removeLenght;
    }
    return 0;
}

/*
 * 简介：CLI操作修改联系人
 * 作者：Fatpandac
 * 时间：2021.03.23
 */

int CLIChangePerson(PersonList *PersonList,int argc,char *argv[])
{
    char chgName[10];       //存储被求改的人姓名
    char chgValue[10];      //存储要修改的属性值
    char elementlist[7][12] = {"name","sex","phoneNumber","email","postCode","address","like"};     //可改属性数组
    int chgElemnt;          //存储修改的属性序号
    int chgIndex;           //存储被修改者物理地址
    for (int i = 0;i < PersonList->lenght;i++)
    {
        if (!strcmp(PersonList->person[i].name,argv[2]))
        {
            strcpy(chgName,argv[2]);
            chgIndex = i;
            if (!PersonList->lenght) printf("%s\n",language[58]);
            for (int i = 0;i < 7;i++)
            {
                if (!strcmp(elementlist[i],argv[3]))
                {
                    chgElemnt = i+1;
                    break;
                }
            }
            break;
        }else if (i+1 == PersonList->lenght){
            printf("%s%s",argv[2],language[14]);    //"不存在!!! 请重新输入\n"
            return 0;
        }
    }
    if (chgElemnt <= 0 || chgElemnt > 7)
    {
        printf("%s\n",language[15]);    //"不存在此属性，请重新输入"
        return 0;
    }
    if ((chgElemnt == 2 || chgElemnt == 7) && argc == 5)
    {
        printf("%s\n",language[16]);    //"更改此属性不需要值!!!"
        return 0;
    }       //当更改值为 sex 或 like 是不用输入
    if (argc == optList[7].countArgument && chgElemnt != 2 && chgElemnt != 7)
    {
        strcpy(chgValue,argv[4]);
    }else if (chgElemnt != 2 && chgElemnt != 7){
        printf("%s\n",language[17]);    //"未输入修改值"
        return 0;
    }
    switch (chgElemnt)
    {
        case 1:
            strcpy(PersonList->person[chgIndex].name,chgValue);
            break;
        case 2:
            PersonList->person[chgIndex].sex = (PersonList->person[chgIndex].sex == 'M') ? 'W' : 'M';
            break;
        case 3:
            strcpy(PersonList->person[chgIndex].phoneNumber,chgValue);
            break;
        case 4:
            strcpy(PersonList->person[chgIndex].email,chgValue);
            break;
        case 5:
            PersonList->person[chgIndex].postCode = atoi(chgValue);
            break;
        case 6:
            strcpy(PersonList->person[chgIndex].address,chgValue);
            break;
        case 7:
            PersonList->person[chgIndex].like = (PersonList->person[chgIndex].like == 0) ? 1 : 0;
            break;
        default:
            printf("%s\n",language[30]);    //"更改失败！！！"
    }
    return 0;
}

/*
 * 简介：CLI操作分享相应联系人联系卡片
 * 作者：Fatpandac
 * 时间：2021.03.24
 */

int CLISharePerson(PersonList PersonList,int argc,char *argv[],char systemLanguage[10])
{
    char shareName[10];
    strcpy(shareName,argv[2]);
    for (int i = 0;i < PersonList.lenght;i++)
    {
        if (!strcmp(PersonList.person[i].name,shareName))
        {
            printf("%s","+----------------------------------------+\n");
            printf("|\33[s%s\33[u\33[%dC\33[s%s\33[u\33[%dC|\33[0m\n",language[33],20,PersonList.person[i].name,20);    //"联系人"
            printf("%s","+----------------------------------------+\n");
            printf("|\33[s%s\33[u\33[%dC\33[s%c\33[u\33[%dC|\33[0m\n",language[34],20,PersonList.person[i].sex,20);     //"性别"
            printf("%s","+----------------------------------------+\n");
            printf("|\33[s%s\33[u\33[%dC\33[s%s\33[u\33[%dC|\33[0m\n",language[35],20,PersonList.person[i].phoneNumber,20);     //"电话"
            printf("%s","+----------------------------------------+\n");
            printf("|\33[s%s\33[u\33[%dC\33[s%s\33[u\33[%dC|\33[0m\n",language[36],20,PersonList.person[i].email,20);   //"电子邮箱"
            printf("%s","+----------------------------------------+\n");
            printf("|\33[s%s\33[u\33[%dC\33[s%d\33[u\33[%dC|\33[0m\n",language[37],20,PersonList.person[i].postCode,20);    //"邮编"
            printf("%s","+----------------------------------------+\n");
            printf("|\33[s%s\33[u\33[%dC\33[s%s\33[u\33[%dC|\33[0m\n",language[38],20,PersonList.person[i].address,20);     //"地址"
            printf("%s","+----------------------------------------+\n");
            return 0;
        }
    }
    printf("%s",language[42]);  //"此联系人不存在!!!\n"
    return 0;
}