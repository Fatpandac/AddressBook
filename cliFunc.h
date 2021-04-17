#ifndef CLIFUNC_H
#define CLIFUNC_H

#define CmdSize            10      //命令操数组长度
//相应操作对应的序号
#define HelpOpt 9
#define AddOpt  1
#define ViewOpt 7
#define FindOpt 4
#define RemoveOpt 3
#define ShareOpt 5
#define ChangeOpt 2
#define ResetOpt 6

typedef struct Opt
{
    char longOptName[10];
    char shortOptName[5];
    char optGuide[150];
    int countArgument;
    int code;
}Opt;       //CLI结构体

Opt optList[CmdSize];

int GetOpt(int argc,char *argv[]);
void PrintHelp(int argc,char *argv[]);

#endif