#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef WIN32
#include <conio.h>
#endif
#ifdef linux
#include <termios.h>
#include <unistd.h>
#endif

#include "file.h"
#include "theme.h"
#include "tuiFunc.h"
#include "control.h"

/*
 * 简介: 兼容linux，实现 getche()
 */

int my_getche()
{
#ifdef linux
    int c;
    system("stty -icanon");
    c = getchar();
    system("stty icanon");
    return c; 
#endif
#ifdef WIN32
    return getche();
#endif
}

/*
 * 简介: 兼容linux，实现 getch()
 */

int my_getch()
{
#ifdef linux
    char c;
    system("stty -icanon"); //关闭终端缓冲区
    system("stty -echo"); //关闭终端回显
    c = getchar();
    system("stty icanon"); //打开终端缓冲区
    system("stty echo"); //打开终端回显
    return c;
#endif
#ifdef WIN32
    return getch();
#endif
}

/*
 * 简介：判断对应操作并调用
 */

int control(PersonList *personList,PersonList *outputPerson,PersonList *fliterPerson,char *fliterName,char *systemLanguage)
{
    while (1)
    {
        int ch;
        printf("\33[?25l");
        printf("\33[%d;%dH\33[0m",windowsInfo.windowsY-1,windowsInfo.windowsX-5);
        ch = my_getch();
        if ( ch == 0xe0 )    
        {
            ch = my_getch();
            ch += 80; 
        }
        switch (ch)
        {
        case W_UP:
        case K_UP:
            windowsInfo.chooseIndex -= (windowsInfo.chooseIndex-1 < 0) ? 0 : 1;
            DisplayPersion(*outputPerson);
            break;
        case S_DOWN:
        case J_DOWN:
            windowsInfo.chooseIndex += (windowsInfo.chooseIndex+1 >= outputPerson->length) ? 0 : 1;
            DisplayPersion(*outputPerson);
            break;
        case FLITER:
            FliterPerson(*personList,outputPerson,fliterPerson,fliterName);
            outputPerson = (fliterPerson->length != 0) ? fliterPerson : personList;
            DisplayPersion(*outputPerson);
            break;
        case CHANGE:
            TUIChangePerson(personList,outputPerson);
            SavePerson(*personList,systemLanguage);
            DisplayPersion(*outputPerson);
            break;
        case REMOVE:
            TUIRemovePerson(personList,outputPerson);
            SavePerson(*personList,systemLanguage);
            clearContent();
            DisplayPersion(*outputPerson);
            break;
        case ADD:
            TUIAddPerson(personList,outputPerson);
            SavePerson(*personList,systemLanguage);
            clearContent();
            DisplayPersion(*outputPerson);
            break;
        case QUIT:
        case Q_QUIT:
            printf("\33[%d;0H\33[0m",windowsInfo.windowsY+2);
            printf("\33[?25h");
            exit(0);
        }
    }
}