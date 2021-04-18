#ifndef CLIFUNC_H
#define CLIFUNC_H

#define CmdSize             11      //命令操数组长度
//相应操作对应的序号
#define AddOpt              1
#define ChangeOpt           2
#define RemoveOpt           3
#define FindOpt             4
#define ShareOpt            5
#define ResetOpt            6
#define ViewOpt             7
#define HelpOpt             9
#define VersionOpt          10

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
int CLIAddPerson(PersonList *PersonList,int argc,char *argv[]);
int CLIFindPerson(PersonList *PersonList,int argc,char *argv[]);
int CLIRemovePerson(PersonList *PersonList,int argc,char *argv[]);
int CLIChangePerson(PersonList *PersonList,int argc,char *argv[]);
int CLISharePerson(PersonList PersonList,int argc,char *argv[],char systemLanguage[10]);

#endif