#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "file.h"
#include "func.h"
#include "language.h"
#include "global.h"


/*
 * 简介：输出操作目录
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
 */

int AddPerson(PersonList *PersonList)
{
    char input[20];
    printf("%s",language[1]);   //"请输入添加联系人姓名："
    scanf("%s",PersonList->person[PersonList->lenght].name);
    while (1)
    {
        printf("%s%s%s",language[2],PersonList->person[PersonList->lenght].name,language[3]);    //"请输入" "的性别(M/W)："
        scanf(" %s",input);
        if (checkPersonSex(input[0]))
        {
            PersonList->person[PersonList->lenght].sex = toupper(input[0]);
            break;
        }
        printf("%s\n",language[28]);
    }
    while (1)
    {
        printf("%s%s%s",language[2],PersonList->person[PersonList->lenght].name,language[4]);     //"请输入" "的电话号码："
        scanf(" %s",input);
        if (checkPersonNumber(input))
        {
            strcpy(PersonList->person[PersonList->lenght].phoneNumber,input);
            break;
        }
        printf("%s\n",language[28]);
    }
    printf("%s%s%s",language[2],PersonList->person[PersonList->lenght].name,language[5]);     //"请输入" "的邮箱地址："
    scanf(" %s",PersonList->person[PersonList->lenght].email);
    while (1)
    {
        printf("%s%s%s",language[2],PersonList->person[PersonList->lenght].name,language[6]);     //"请输入" "的邮编："
        scanf(" %s",input);
        if (checkPersonNumber(input))
        {
            PersonList->person[PersonList->lenght].postCode = atoi(input);
            break;
        }
        printf("%s\n",language[28]);
    }
    printf("%s%s%s",language[2],PersonList->person[PersonList->lenght].name,language[7]);     //"请输入" "的地址："
    scanf(" %s",PersonList->person[PersonList->lenght].address);
    while (1)
    {
        printf("%s%s%s",language[8],PersonList->person[PersonList->lenght].name,language[9]);     //"是否把" "设为特别关心(Y/n)："
        scanf(" %s",input);
        if (checkPersonLike(input[0]))
        {
            PersonList->person[PersonList->lenght].like = (tolower(input[0]) == 'y') ? 1 : 0;      //1表示特别关心，0反之
            break;
        }
        printf("%s\n",language[28]);
    }
    Success();   
    PersonList->lenght++;
    return 0;
}

/*
 * 简介：用于查找相应元素对应值并返回物理地址
 */

int FindPerson(PersonList *PersonList)
{
    char findElement[10],findValue[20];
    int findElementKey;
    int findFuzzyIndex[MaxSize];     //保存模糊查找结果 index 数组
    int findFuzzyIndexLenght = 0;         //记录 findFuzzyIndex 长度
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
    printf("%s\n",language[42]);
    return -2;
}

/*
 * 简介：修改联系人
 */

int ChangePerson(PersonList *PersonList)
{
    char chgName[10];       //存储被求改的人姓名
    char chgValue[10];      //存储要修改的属性值
    char elementlist[7][12] = {"name","sex","phoneNumber","email","postCode","address","like"};     //可改属性数组
    int chgElemnt;          //存储修改的属性序号
    int chgIndex;           //存储被修改者物理地址
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
    Success();
    return 0;
}

/*
 * 简介：删除联系人
 */

int RemovePerson(PersonList *PersonList)
{
    char mvName[10];        //存储被删除人姓名
    int removeLenght = 0;      //删除后长度{
    printf("%s",language[31]);  //"请输入被删除联系人名称："
    scanf("%s",mvName);
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
            Success();
    }
    return 0;
}

/*
 * 简介：分享相应联系人联系卡片
 */

int SharePerson(PersonList PersonList,char systemLanguage[10])
{
    char shareName[10];
    printf("%s",language[32]);  //"请输入要分享人的姓名："
    scanf("%s",shareName);
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
    printf("%s\n",language[42]);  //"此联系人不存在!!!\n"
    return 0;
}