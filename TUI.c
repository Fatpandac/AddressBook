#include <stdio.h>

#include "file.h"
#include "theme.h"
#include "control.h"
#include "tuiFunc.h"
#include "TUI.h"

/*
 * 简介：TUI 操作主函数
 */

int TUI(PersonList *personList,char systemLanguage[])
{
    loadingTheme();
    PersonList *outputPerson;   //用于存储输出的联系人列表指针
    PersonList fliterPerson;    //用于存储筛选后联系人列表指针
    fliterPerson.lenght = 0;    //初始化筛选联系人结构体
    char fliterName[10] = "";    //用于存储筛选内容
    outputPerson = personList;  //将初始联系人列表赋值给输出指针变量 
    InitWindows();
    DisplayPersion(*outputPerson);
    control(personList,outputPerson,&fliterPerson,fliterName,systemLanguage);
    return 0;
}