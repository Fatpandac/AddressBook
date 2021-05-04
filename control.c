#include <stdio.h>
#include <stdlib.h>

#ifdef WIN32
#include <conio.h>
#endif

#include "file.h"
#include "theme.h"
#include "tuiFunc.h"
#include "control.h"

/*
 * 简介: 兼容linux，实现 getche()
 */

char my_getche()
{
#ifdef linux
    char c;
    system("stty -icanon");
    c=getchar();
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

char my_getch()
{
#ifdef linux
    char c;
    system("stty -echo");  //不回显
    system("stty -icanon");//设置一次性读完操作，如使用getchar()读操作，不需要按enter
    c=getchar();
    system("stty icanon");//取消上面的设置
    system("stty echo");//回显
    return c;
#endif
#ifdef WIN32
    return getch();
#endif
}

/*
 * 简介：判断对应操作并调用
 */

int control(PersonList *personList,PersonList *outputPerson,PersonList *fliterPerson,char fliterName[6],char *systemLanguage)
{
    while (1)
    {
        int ch;
        printf("\33[?25l");
        printf("\33[%d;%dH\33[0m",windowsInfo.windowsY+1,windowsInfo.windowsX+2);
        ch = my_getch();
        char systemTheme[50];
        if ( ch == 0xe0 )    
        {
            ch=my_getch();
            ch+=80; 
        }
        switch (ch)
        {
        case UP:
        case W_UP:
        case K_UP:
            windowsInfo.chooseIndex -= (windowsInfo.chooseIndex-1 < 0) ? 0 : 1;
            DisplayPersion(*outputPerson);
            break;
        case DOWN:
        case S_DOWN:
        case J_DOWN:
            windowsInfo.chooseIndex += (windowsInfo.chooseIndex+1 >= outputPerson->lenght) ? 0 : 1;
            DisplayPersion(*outputPerson);
            break;
        case FLITER:
            FliterPerson(*personList,outputPerson,fliterPerson,fliterName);
            outputPerson = (fliterPerson->lenght != 0) ? fliterPerson : personList;
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
            DisplayPersion(*outputPerson);
            break;
        case ADD:
            TUIAddPerson(personList,outputPerson);
            SavePerson(*personList,systemLanguage);
            DisplayPersion(*outputPerson);
            break;
        case QUIT:
        case Q_QUIT:
            exit(0);
        }
    }
}