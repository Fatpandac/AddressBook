#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define Ture 1
#define MaxSize 100     //通讯录数组长度
#define CmdSize 10       //命令操数组长度

typedef struct
{
    char name[10];
    char address[20];
    int postCode;
    char sex;
    char email[20];
    char phoneNumber[12];
    int like;
}Person;        //联系人结构体

typedef struct
{
    Person person[MaxSize];
    int lenght;
}PersonList;

/*
 * 简介：定义CLI结构体，并保存操作数据
 * 作者：Fatpandac
 * 时间：2021.03.19
 *
 */

typedef struct
{
    char longOptName[10];
    char shortOptName[5];
    char optGuide[150];
    int countArgument;
    int code;
}Opt;       //CLI结构体

Opt optList[CmdSize] = {
    {"add","-a","[add | -a] <name>\nCreate a new contact\n",3,1},
    {"view","-v","[view | -v]\nDisplay you AddressBook\n",2,7},
    {"help","-h","[help | -h]\nDisplay all help\n",2,8},
    {"help","-h","[help | -h]\nDisplay all help\n",3,8},
    {"find","-f","[find | -f] <by element> <value>\nFind the element of the value\n[by element | name | address]\n",4,4},
    {"share","-s","[share | -s] <name>\nShare contact with card\n",3,5},
    {"reset","","[reset]\nReset you AddressBook\n",2,6},
    {"change","-chg","[change | -chg] <name> <element> <value>\nChange the value of the element\n[element | name | sex | phoneNumber | email | address | postCode | like]\n",5,2},
    {"change","-chg","[change | -chg] <name> <element> <value>\nChange the value of the element\n[element | name | sex | phoneNumber | email | address | postCode | like]\n",4,2},
    {"remove","-mv","[remove | -mv] <name>\nRemove <name>'s contact\n",3,3}
};      //CLI操作数据

/*
 * 简介：用于判断CLI并返回相应操作函数序号
 * 作者：Fatpandac
 * 时间：2021.03.20
 *
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
    printf("%s","错误命令符！！！\n");
    return 0;
}

/*
 * 简介：添加联系人
 * 作者：Fatpandac
 * 时间：2021.03.21
 *
 */

int AddPerson(PersonList *PersonList,int argc,char *argv[])
{
    char input;
    if (argc == optList[0].countArgument)
    {
        strcpy(PersonList->person[PersonList->lenght].name,argv[2]);
    }else{
        printf("%s","请输入添加联系人姓名：");
        scanf("%s",PersonList->person[PersonList->lenght].name);
    }
    printf("%s%s%s","请输入",PersonList->person[PersonList->lenght].name,"的性别(M/W)：");
    scanf(" %c",&PersonList->person[PersonList->lenght].sex);
    printf("%s%s%s","请输入",PersonList->person[PersonList->lenght].name,"的电话号码：");
    scanf(" %s",PersonList->person[PersonList->lenght].phoneNumber);
    printf("%s%s%s","请输入",PersonList->person[PersonList->lenght].name,"的邮箱地址：");
    scanf(" %s",PersonList->person[PersonList->lenght].email);
    printf("%s%s%s","请输入",PersonList->person[PersonList->lenght].name,"的邮编：");
    scanf(" %d",&PersonList->person[PersonList->lenght].postCode);
    printf("%s%s%s","请输入",PersonList->person[PersonList->lenght].name,"的地址：");
    scanf(" %s",PersonList->person[PersonList->lenght].address);
    printf("%s%s%s","是否把",PersonList->person[PersonList->lenght].name,"设为特别关心(Y/n)：");
    scanf(" %c",&input);
    PersonList->person[PersonList->lenght].like = (tolower(input) == 'y') ? 1 : 0;      //1表示特别关心，0反之
    PersonList->lenght++;
    return 0;
}

/*
 * 简介：用于查找相应元素对应值并返回物理地址
 * 作者：Fatpandac
 * 时间：2020.03.22
 *
 */

int FindPerson(PersonList *PersonList,int argc,char *argv[])
{
    char findElement[10],findValue[20];
    int findElementKey;
    if (argc == optList[4].countArgument)
    {
        strcpy(findElement,argv[2]);
        strcpy(findValue,argv[3]);
        for (int i = 0;i < PersonList->lenght;i++)
        {
            if (!strcmp(findElement,"name"))
            {
                if (!strcmp(PersonList->person[i].name,findValue))
                {
                    return i;
                }
            }else if (!strcmp(findElement,"address"))
            {
                if (!strcmp(PersonList->person[i].name,findValue))
                {
                    return i;
                }
            }
        }
    }else{
        printf("%s%s%s"
               ,"[1] 名字查找\n"
               ,"[2] 地址查找\n"
               ,"请输入相应查找方式序号：");
        scanf("%d",&findElementKey);
        printf("%s","请输入查找的内容：");
        scanf("%s",findValue);
        for (int i = 0;i < PersonList->lenght;i++)
        {
           if (findElementKey-1 == 0)
           {
               if (!strcmp(PersonList->person[i].name,findValue))
               {
                    return i;
               }
           }else if (findElementKey-1 == 1){
                if (!strcmp(PersonList->person[i].address,findValue))
                {
                    return i;
                }
           }
        }
    }
    return -1;
}

/*
 * 简介：修改联系人
 * 作者：Fatpandac
 * 时间：2021.03.23
 *
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
                for (int i = 0;i < 7;i++)
                {
                    if (!strcmp(elementlist[i],argv[3]))
                    {
                        chgElemnt = i+1;
                        break;
                    }
                }
            }else{
                printf("%s%s",argv[2],"不存在!!! 请重新输入\n");
                return 0;
            }
        }
        if (chgElemnt <= 0 || chgElemnt > 7)
        {
            printf("%s\n","不存在此属性，请重新输入");
            return 0;
        }
        if ((chgElemnt == 2 || chgElemnt == 7) && argc == 5)
        {
            printf("%s\n","更改此属性不需要值!!!");
            return 0;
        }       //当更改值为 sex 或 like 是不用输入
        if (argc == optList[7].countArgument && chgElemnt != 2 && chgElemnt != 7)
        {
            strcpy(chgValue,argv[4]);
        }else if (chgElemnt != 2 && chgElemnt != 7){
            printf("%s\n","未输入修改值");
            return 0;
        }
    }else{
        printf("%s","请输入要修改的人名：");
        scanf("%s",chgName);
        for (int i = 0;i < PersonList->lenght;i++)
        {
            if (!strcmp(PersonList->person[i].name,chgName))
            {
                chgIndex = i;
            }else{
                printf("%s%s",chgName,"不存在！！！\n请重新输入\n");
                return 0;
            }
        }
        while (Ture)
        {
            printf("%s%s%s%s%s%s"
                   ,"[1] 修改联系人姓名\n"
                   ,"[2] 修改联系人性别\n"
                   ,"[3] 修改联系人电话\n"
                   ,"[4] 修改联系人邮箱\n"
                   ,"[5] 修改联系人邮编\n"
                   ,"[6] 修改联系人地址\n");
            printf("%s\n",(PersonList->person[chgIndex].like == 1) ? "[7] 修改为不关注" : "[7] 修改为关注");
            printf("%s","请输入相应序号：");
            scanf("%d",&chgElemnt);
            if (chgElemnt > 0 && chgElemnt <= 7) break;//判断是否输入错误
            printf("%s\n","输入错误，请重新输入\n");
        }
        if (chgElemnt != 2 || chgElemnt != 7)
        {
            printf("%s","请输入更改的值：");
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
            printf("%s\n","更改失败！！！");
    }
    return 0;
}

/*
 * 简介：删除联系人
 * 作者：Fatpandac
 * 时间：2021.03.22
 *
 */

int RemovePerson(PersonList *PersonList,int argc,char *argv[])
{
    char mvName[10];        //存储被删除人姓名
    if (argc == optList[9].countArgument)
    {
        strcpy(mvName,argv[2]);
    }else{
        printf("%s","请输入被删除联系人名称：");
        scanf("%s",mvName);
    }
    for (int i = 0;i < PersonList->lenght;i++)
    {
        if (!strcmp(PersonList->person[i].name,mvName))
        {
            for (int j = i;j <= PersonList->lenght;j++)
            {
                PersonList->person[j] = PersonList->person[j+1];
            }
        }
    }
    PersonList->lenght--;
    return 0;
}

/*
 * 简介：分享相应联系人联系卡片
 * 作者：Fatpandac
 * 时间：2021.03.24
 *
 */
int SharePerson(PersonList PersonList,int argc,char *argv[])
{
    char shareName[10];
    if (argc == optList[5].countArgument)
    {
       strcpy(shareName,argv[2]);
    }else{
        printf("%s","请输入要分享人的姓名：");
        scanf("%s",shareName);
    }
    for (int i = 0;i < PersonList.lenght;i++)
    {
        if (!strcmp(PersonList.person[i].name,shareName))
        {
            printf("%s","+-----------------------------+\n");
            printf("|%11s:%-20s|\n","联系人",PersonList.person[i].name);
            printf("%s","+-----------------------------+\n");
            printf("|%10s:%-20c|\n","性别",PersonList.person[i].sex);
            printf("%s","+-----------------------------+\n");
            printf("|%10s:%-20s|\n","电话",PersonList.person[i].phoneNumber);
            printf("%s","+-----------------------------+\n");
            printf("|%10s:%-20s|\n","电子邮箱",PersonList.person[i].email);
            printf("%s","+-----------------------------+\n");
            printf("|%10s:%-20d|\n","邮编",PersonList.person[i].postCode);
            printf("%s","+-----------------------------+\n");
            printf("|%10s:%-20s|\n","地址",PersonList.person[i].address);
            printf("%s","+-----------------------------+\n");
            return 0;
        }
    }
    printf("%s","此联系人不存在!!!\n");
    return 0;
}

/*
 * 简介：输出联系人信息
 * 作者：Fatpandac
 * 时间：2021.03.22
 *
 */
int DisplayPerson(PersonList PersonList,int key)        //key 用于保存指定输出地址，为-1时全输出
{
    printf("%-13s%-8s%-15s%-24s%-10s%-22s%s\n","联系人","性别","电话","电子邮箱","邮编","地址","关心");
    if (key == -1)
    {
        for (int i = 0;i < PersonList.lenght;i++)
        {
            printf("%-10s%-6c%-13s%-20s%-8d%-20s",PersonList.person[i].name,PersonList.person[i].sex,PersonList.person[i].phoneNumber,PersonList.person[i].email,PersonList.person[i].postCode,PersonList.person[i].address);
            printf("%4s\n",(PersonList.person[i].like == 1) ? "是":"否");
        }
    }else{
        int i = key;
        printf("%-10s%-6c%-13s%-20s%-8d%-20s",PersonList.person[i].name,PersonList.person[i].sex,PersonList.person[i].phoneNumber,PersonList.person[i].email,PersonList.person[i].postCode,PersonList.person[i].address);
        printf("%4s\n",(PersonList.person[i].like == 1) ? "是":"否");
    }
    return 0;
}

/*
 * 简介：输出CLI的操作指南
 * 作者：Fatpandac
 * 时间：2021.03.20
 *
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
            }
        }
    }else{
        for (int i = 0;i < CmdSize;i++)
        {
            printf("%s\n",optList[i].optGuide);
        }
    }
}

/*
 * 简介：重置通讯录
 * 作者：Fatpandac
 * 时间：2021.03.20
 *
 */
int ResetPerson(PersonList *PersonList)
{
    PersonList->lenght = 0;
    return 0;
}

/*
 * 简介：将数据保存到文件中
 * 作者：Fatpandac
 * 时间：2021.03.25
 *
 */

int SavePerson(PersonList PersonList,char language[10])
{
    FILE *savePerson = fopen("AddressBook.txt","wb");
    if (savePerson == NULL)
    {
        printf("%s\n","写入失败");
        return 0;
    }
    fprintf(savePerson,"系统语言为%s\n",language);
    fprintf(savePerson,"共有%d位联系人\n",PersonList.lenght);
    for (int i = 0;i < PersonList.lenght;i++)
    {
        fprintf(savePerson,"%s\t%c\t%s\t%s\t%d\t%s\t%d\n",PersonList.person[i].name,PersonList.person[i].sex,PersonList.person[i].phoneNumber,PersonList.person[i].email,PersonList.person[i].postCode,PersonList.person[i].address,PersonList.person[i].like);
    }
    fclose(savePerson);
    return 0;
}

/*
 * 简介：读取文件获取到通讯录数据
 * 作者：Fatpandac
 * 时间：2021.03.25
 */

int ReadPerson(PersonList *PersonList,char *language)
{
    FILE *readPerson = fopen("AddressBook.txt","rb");
    if (readPerson == NULL)
    {
        printf("%s\n","读取失败");
        return 0;
    }
    fscanf(readPerson,"系统语言为%s\n",language);
    fscanf(readPerson,"共有%d位联系人\n",&PersonList->lenght);
    for (int i = 0;i < PersonList->lenght;i++)
    {
        fscanf(readPerson,"%s\t%c\t%s\t%s\t%d\t%s\t%d\n",PersonList->person[i].name,&PersonList->person[i].sex,PersonList->person[i].phoneNumber,PersonList->person[i].email,&PersonList->person[i].postCode,PersonList->person[i].address,&PersonList->person[i].like);
    }
    fclose(readPerson);
    return 0;
}
/*
 * 简介：输出操作目录
 * 作者：Fatpandac
 * 时间：2021.03.20
 *
 */

int menu()
{
    int opt;
    printf("%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s"
           ,"[1] 生成联系方式"
           ,"[2] 修改联系方式"
           ,"[3] 删除联系方式"
           ,"[4] 查找联系方式"
           ,"[5] 分享联系人  "
           ,"[6] 重置通讯录  "
           ,"[7] 显示通讯录列表"
           ,"[0] 退出        "
           ,"请输入对应序号：");
    scanf("%d",&opt);
    return opt;
}

int main(int argc,char *argv[])     //argc 输入参数数量； argv 输入的参数
{
    PersonList PersonList;
    char language[10];      //用于存储程序语言设置
    strcpy(language,"CN.txt");  //初始化默认为中文
    ReadPerson(&PersonList,language);
    while(Ture)
    {
        int opt;        //每次循环初始化,用于存储操作序号
        if (argc >= 2)
        {
            opt = GetOpt(argc,argv);
        }else{
            opt = menu();
        }
        switch (opt)
        {
            case 1:
                AddPerson(&PersonList,argc,argv);
                SavePerson(PersonList,language);
                break;
            case 2:
                ChangePerson(&PersonList,argc,argv);
                SavePerson(PersonList,language);
                break;
            case 3:
                RemovePerson(&PersonList,argc,argv);
                SavePerson(PersonList,language);
                break;
            case 4:
                DisplayPerson(PersonList,FindPerson(&PersonList,argc,argv));
                break;
            case 5:
                SharePerson(PersonList,argc,argv);
                break;
            case 6:
                ResetPerson(&PersonList);
                SavePerson(PersonList,language);
                break;
            case 7:
                DisplayPerson(PersonList,-1);
                break;
            case 8:
                PrintHelp(argc,argv);
                break;
            case 0:
                exit(0);
            default:
                printf("Err");
        }
        if (argc >= 2) break;
        system("pause");
        system("cls");
    }
    return 0;
}
