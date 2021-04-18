#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "file.h"
#include "func.h"
#include "language.h"
#include "cliFunc.h"

#define VERSION            "0.1.14"


/*
 * 简介：输出操作目录
 * 作者：Fatpandac
 * 时间：2021.03.20
 */
int Menu()
{
    int opt;
    printf("%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s"
           ,language[48]
           ,language[49]
           ,language[50]
           ,language[51]
           ,language[52]
           ,language[53]
           ,language[54]
           ,language[55]
           ,language[56]
           ,language[27]);    //"[1] 生成联系方式" "[2] 修改联系方式" "[3] 删除联系方式" "[4] 查找联系方式" "[5] 分享联系人  " "[6] 重置通讯录  " "[7] 显示通讯录列表" "[8] 设置" "[0] 退出        " "请输入相应序号："
    scanf("%d",&opt);
    return opt;
}


/*
 * 简介：添加联系人
 * 作者：Fatpandac
 * 时间：2021.03.21
 */

int AddPerson(PersonList *PersonList,int argc,char *argv[])
{
    char input;
    if (argc == optList[2].countArgument)
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
       }else{
           printf("%s\n",language[28]);
       }
    }else{
        printf("%s",language[1]);   //"请输入添加联系人姓名："
        scanf("%s",PersonList->person[PersonList->lenght].name);
        while (1)
        {
            printf("%s%s%s",language[2],PersonList->person[PersonList->lenght].name,language[3]);    //"请输入" "的性别(M/W)："
            scanf(" %c",&input);
            if (toupper(input) == 'M' || toupper(input) == 'W')
            {
                PersonList->person[PersonList->lenght].sex = input;
                break;
            }
            printf("%s\n",language[28]);
        }
        printf("%s%s%s",language[2],PersonList->person[PersonList->lenght].name,language[4]);     //"请输入" "的电话号码："
        scanf(" %s",PersonList->person[PersonList->lenght].phoneNumber);
        printf("%s%s%s",language[2],PersonList->person[PersonList->lenght].name,language[5]);     //"请输入" "的邮箱地址："
        scanf(" %s",PersonList->person[PersonList->lenght].email);
        printf("%s%s%s",language[2],PersonList->person[PersonList->lenght].name,language[6]);     //"请输入" "的邮编："
        scanf(" %d",&PersonList->person[PersonList->lenght].postCode);
        printf("%s%s%s",language[2],PersonList->person[PersonList->lenght].name,language[7]);     //"请输入" "的地址："
        scanf(" %s",PersonList->person[PersonList->lenght].address);
        while (1)
        {
            printf("%s%s%s",language[8],PersonList->person[PersonList->lenght].name,language[9]);     //"是否把" "设为特别关心(Y/n)："
            scanf(" %c",&input);
            if (tolower(input) == 'y' || tolower(input) == 'n')
            {
                PersonList->person[PersonList->lenght].like = (tolower(input) == 'y') ? 1 : 0;      //1表示特别关心，0反之
                break;
            }
            printf("%s\n",language[28]);
        }
        Success();
    }
    PersonList->lenght++;
    return 0;
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
 * 简介：用于查找相应元素对应值并返回物理地址
 * 作者：Fatpandac
 * 时间：2020.03.22
 */

int FindPerson(PersonList *PersonList,int argc,char *argv[])
{
    char findElement[10],findValue[20];
    int findElementKey;
    int findFuzzyIndex[MaxSize];     //保存模糊查找结果 index 数组
    int findFuzzyIndexLenght = 0;         //记录 findFuzzyIndex 长度
    if (argc == optList[4].countArgument)
    {
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
    }else{
        while (1)
        {
            printf("%s\n%s\n%s"
                ,language[10]
                ,language[11]
                ,language[12]);    //"[1] 名字查找\n" "[2] 地址查找\n" "请输入相应查找方式序号："
            scanf("%d",&findElementKey);
            if (findElementKey > 0 && findElementKey <= 2) break;
            printf("%s\n",language[28]);
        }
        findElementKey--;       //转换查询地址为实际物理地址
        printf("%s\n",language[59]);  //"请输入查找的内容(以“/”开始进行模糊查找)："
        scanf("%s",findValue);
        if (findValue[0] == '/'){
            strncpy(findValue,findValue+1,strlen(findValue));        //消除模糊匹配区别符
            for (int j = 0,k = 0;j < PersonList->lenght;j++)
            {
                if (findElementKey == 0)
                {   
                    if (fuzzyFind(PersonList->person[j].name,findValue))
                    {
                        findFuzzyIndex[k++] = j;
                        findFuzzyIndexLenght++;
                    }
                    
                }else if (findElementKey == 1){
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
                if (findElementKey == 0)
                {
                    if (!strcmp(PersonList->person[i].name,findValue))
                    {
                        return i;
                    }
                }else if (findElementKey == 1){
                    if (!strcmp(PersonList->person[i].address,findValue))
                    {
                        return i;
                    }
                }
            }
        }
    }
    printf("%s\n",language[42]);
    return -2;
}

/*
 * 简介：修改联系人
 * 作者：Fatpandac
 * 时间：2021.03.23
 */

int ChangePerson(PersonList *PersonList,int argc,char *argv[])
{
    char chgName[10];       //存储被求改的人姓名
    char chgValue[10];      //存储要修改的属性值
    char elementlist[7][12] = {"name","sex","phoneNumber","email","postCode","address","like"};     //可改属性数组
    int chgElemnt;          //存储修改的属性序号
    int chgIndex;           //存储被修改者物理地址
    if (argc == optList[7].countArgument || argc == optList[8].countArgument)
    {
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
    }else{
        printf("%s",language[18]);  //"请输入要修改的人名："
        scanf("%s",chgName);
        if (!PersonList->lenght) printf("%s\n",language[58]);
        for (int i = 0;i < PersonList->lenght;i++)
        {
            if (!strcmp(PersonList->person[i].name,chgName))
            {
                chgIndex = i;
                break;
            }else if (i+1 == PersonList->lenght){
                printf("%s%s",chgName,language[14]);    //"不存在！！！请重新输入\n"
                return 0;
            }
        }
        while (1)
        {
            printf("%s\n%s\n%s\n%s\n%s\n%s\n"
                   ,language[19]
                   ,language[20]
                   ,language[21]
                   ,language[22]
                   ,language[23]
                   ,language[24]);    //"[1] 修改联系人姓名\n" "[2] 修改联系人性别\n" "[3] 修改联系人电话\n" "[4] 修改联系人邮箱\n" "[5] 修改联系人邮编\n" "[6] 修改联系人地址\n"
            printf("%s\n",(PersonList->person[chgIndex].like == 1) ? language[25] : language[26] );     //"[7] 修改为不关注" "[7] 修改为关注"
            printf("%s\n",language[56]);
            printf("%s",language[27]);  //"请输入相应序号："
            scanf("%d",&chgElemnt);
            if (!chgElemnt) return 0;   //退出修改
            if (chgElemnt > 0 && chgElemnt <= 7) break;//判断是否输入错误
            printf("%s\n",language[28]);    //"输入错误，请重新输入\n"
        }
        if (chgElemnt != 2 && chgElemnt != 7)
        {
            printf("%s",language[29]);  //"请输入更改的值："
            scanf("%s",chgValue);
        }
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
    if (argc != optList[7].countArgument && argc != optList[8].countArgument) Success();    //CLI 操作不反馈
    return 0;
}

/*
 * 简介：删除联系人
 * 作者：Fatpandac
 * 时间：2021.03.22
 */

int RemovePerson(PersonList *PersonList,int argc,char *argv[])
{
    char mvName[10];        //存储被删除人姓名
    int removeLenght = 0;      //删除后长度
    if (argc == optList[5].countArgument)
    {
        strcpy(mvName,argv[2]);
    }else{
        printf("%s",language[31]);  //"请输入被删除联系人名称："
        scanf("%s",mvName);
    } 
    for (int i = 0;i < PersonList->lenght;i++)
    {
        if (strcmp(PersonList->person[i].name,mvName))
        {
           strcpy (PersonList->person[removeLenght].name , PersonList->person[i].name);
           removeLenght++;
        }    
    }  
     if (removeLenght == PersonList->lenght){
            printf("%s\n",language[42]);
    }else{
            PersonList->lenght = removeLenght;
            Success();
    }
    return 0;
}

/*
 * 简介：分享相应联系人联系卡片
 * 作者：Fatpandac
 * 时间：2021.03.24
 */

int SharePerson(PersonList PersonList,int argc,char *argv[],char systemLanguage[10])
{
    char shareName[10];
    if (argc == optList[5].countArgument)
    {
       strcpy(shareName,argv[2]);
    }else{
        printf("%s",language[32]);  //"请输入要分享人的姓名："
        scanf("%s",shareName);
    }
    for (int i = 0;i < PersonList.lenght;i++)
    {
        if (!strcmp(PersonList.person[i].name,shareName))
        {
            printf("%s","┌───────────────────────────────────────────────────────┐\n");
            printf("│%-30s\t%-20s\t│\n",language[33],PersonList.person[i].name);    //"联系人"
            printf("%s","├───────────────────────────────────────────────────────┤\n");
            printf("│%-30s\t%-20c\t│\n",language[34],PersonList.person[i].sex);     //"性别"
            printf("%s","├───────────────────────────────────────────────────────┤\n");
            printf("│%-30s\t%-20s\t│\n",language[35],PersonList.person[i].phoneNumber);     //"电话"
            printf("%s","├───────────────────────────────────────────────────────┤\n");
            printf("│%-30s\t%-20s\t│\n",language[36],PersonList.person[i].email);   //"电子邮箱"
            printf("%s","├───────────────────────────────────────────────────────┤\n");
            printf("│%-30s\t%-20d\t│\n",language[37],PersonList.person[i].postCode);    //"邮编"
            printf("%s","├───────────────────────────────────────────────────────┤\n");
            printf("│%-30s\t%-20s\t│\n",language[38],PersonList.person[i].address);     //"地址"
            printf("%s","└───────────────────────────────────────────────────────┘\n");
            return 0;
        }
    }
    printf("%s",language[42]);  //"此联系人不存在!!!\n"
    return 0;
}

/*
 * 简介：输出联系人信息
 * 作者：Fatpandac
 * 时间：2021.03.22
 */

int DisplayPerson(PersonList PersonList,int key,char systemLanguage[10])        //key 用于保存指定输出地址，为-1时全输出
{
    if (PersonList.lenght <= 0 && key != -2) 
    {
        printf("%s\n",language[58]);
        return 0;
    }                              //在没有数据的时候输出
    if (key == -2) return 0;      //key 为 -2、-1、其他 时分别表示为 不输出、全输出、输出对应
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

void DisplayVersion()
{
    printf("VERSION:%s\n",VERSION);
}

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