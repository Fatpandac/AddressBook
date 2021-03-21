#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define Ture 1
#define Flase -1
#define MaxSize 100     //通讯录数组长度
#define CmdSize 8       //命令操数组长度

typedef struct
{
    char sex;
    char name[10];
    char email[20];
    char address[20];
    char phoneNumber[12];
    int like;
    int postCode;
}Person;        //联系人结构体

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
    char optGuide[100];
    int code;
}Opt;       //CLI结构体

Opt optList[CmdSize] = {
    {"add","-a","[add | -a] <name>\t\t\tCreate a new contact",1},
    {"view","-v","\n[view | -v]\t\t\t\tDisplay you AddressBook",7},
    {"help","-h","\n[help | -h] <option>\t\t\tDisplay all help or <option> help",8},
    {"find","-f","\n[find | -f] <by element> <value>\tFind the element of the value",4},
    {"share","-s","\n[share | -s] <name>\t\t\tShare contact with card",5},
    {"reset","","\n[reset]\t\t\t\t\tReset you AddressBook",6},
    {"change","-chg","\n[change | -chg] <element> <value>\tChange the value of the element",2},
    {"remove","-mv","\n[remove | -mv] <name>\t\t\tRemove <name>'s contact",3},
};      //CLI操作数据

/*
 * 简介：用于判断CLI并返回相应操作函数序号
 * 作者：Fatpandac
 * 时间：2021.03.20
 *
 */

int GetOpt(char *argv[])
{
    for(int i = 0;i < CmdSize;i++)
    {
        if (!strcmp(optList[i].longOptName,argv[1]))
        {
            return optList[i].code;
        }
    }
}

int AddPerson()
{
    printf("This is func of AddPerson");
    return 0;
}

/*
 * 简介：输出CLI的操作指南
 * 作者：Fatpandac
 * 时间：2021.03.20
 *
 */

void PrintHelp()
{
    for (int i = 0;i < CmdSize;i++)
    {
        printf("%s",optList[i].optGuide);
    }
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
    printf("[1] 生成联系方式\n"
           "[2] 修改联系方式\n"
           "[3] 删除联系方式\n"
           "[4] 查找联系方式\n"
           "[5] 分享联系人  \n"
           "[6] 重置通讯录  \n"
           "[0] 退出        \n"
           "请输入对应序号：");
    scanf("%d",&opt);
    return opt;
}

int main(int argc,char *argv[])     //argc 输入参数数量； argv 输入的参数
{
    Person person[MaxSize];
    while(Ture)
    {
        int opt;        //每次循环初始化
        if (argc >= 2)
        {
            opt = GetOpt(argv);
        }else{
            opt = menu();
        }
        switch (opt)
        {
            case 1:
                AddPerson();
                break;
            case 8:
                PrintHelp();
                break;
            case 0:
                exit(0);
            default:
                printf("Err");
        }
        if (argc >= 2) break;
    }
    return 0;
}
