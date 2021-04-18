#ifndef GLOBAL_H
#define GLOBAL_H

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

#define version "0.1.14"

void DisplayVersion();
int fuzzyFind(char cmpValue[20],char findValue[20]);
void DisplayFuzzyPerson(PersonList *PersonList,int findFuzzyIndex[MaxSize],int findFuzzyIndexLenght);
int DisplayPerson(PersonList PersonList,int key,char systemLanguage[10]);
int ResetPerson(PersonList *PersonList);
int Setting(char systemLanguage[10]);

#endif