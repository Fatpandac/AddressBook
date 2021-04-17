#ifndef FUNC_H
#define FUNC_H

#ifdef linux
#define Clear() system("clear");
#endif 
#ifdef WIN32
#define Clear() system("cls");      //清除屏幕 windows 中调用 system("cls") Linux 中调用 system("clear")
#endif
#define Success() printf("%s\n",language[47]);
#define Pasue() printf("%s",language[57]);\
                getchar();\
                getchar();      //"敲击任意键继续…" 两个 getchar() 为了防止吃回车现象出现

int Menu();
int Setting(char systemLanguage[10]);
int ResetPerson(PersonList *PersonList);
int DisplayPerson(PersonList PersonList,int key,char systemLanguage[10]);
int SharePerson(PersonList PersonList,int argc,char *argv[],char systemLanguage[10]);
int RemovePerson(PersonList *PersonList,int argc,char *argv[]);
int ChangePerson(PersonList *PersonList,int argc,char *argv[]);
int FindPerson(PersonList *PersonList,int argc,char *argv[]);
int AddPerson(PersonList *PersonList,int argc,char *argv[]);

#endif