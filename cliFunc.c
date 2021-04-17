#include <stdio.h>
#include <string.h>
#include "language.h"
#include "cliFunc.h"

Opt optList[CmdSize] = {    
    {"help","-h","[help | -h] <option>\nDisplay all help when option is null or <option> help\n",3,HelpOpt},
    {"help","-h","[help | -h]\nDisplay all help\n",2,HelpOpt},
    {"add","-a","[add | -a] <name> <sex | M/w> <phone number> <email> <postcode> <address> <like | Y/n>\nCreate a new contact\n",9,AddOpt},
    {"view","-v","[view | -v]\nDisplay you AddressBook\n",2,ViewOpt},
    {"find","-f","[find | -f] <by element> <value>\nFind the element of the value,start with \"/\" for fuzzy search\n[by element | name | address]\n",4,FindOpt},
    {"remove","-mv","[remove | -mv] <name>\nRemove <name>'s contact\n",3,RemoveOpt},
    {"share","-s","[share | -s] <name>\nShare contact with card\n",3,ShareOpt},
    {"change","-chg","[change | -chg] <name> <element> <value>\nChange the value of the element\n[element | name | sex | phoneNumber | email | address | postCode | like]\n",5,ChangeOpt},
    {"change","-chg","[change | -chg] <name> <element> <value>\nChange the value of the element\n[element | name | sex | phoneNumber | email | address | postCode | like]\n",4,ChangeOpt},
    {"reset","","[reset]\nReset you AddressBook\n",2,ResetOpt}
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