#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <math.h>

#include "theme.h"
#include "file.h"
#include "tuiFunc.h"
#include "control.h"
#include "global.h"

#define DisplayCursor          printf("\33[?25h");
#define UnDisplayCursor        printf("\33[?25l");
#define printTag               "\33[38;2;%d;%d;%dm%s\33[0m"
#define printChooseBodyFormat  "\33[38;2;%d;%d;%dm\33[s%-20s\33[u\33[10C\33[s%-20c\33[u\33[5C\33[s%-20s\33[u\33[15C\33[s%-20s\33[u\33[20C\33[s%-20d\33[u\33[10C\33[s%-20s\33[u\33[20C%-5s\33[0m\n"
#define tuiPrintBodyFormat     "\33[38;2;%d;%d;%dm\33[s%-20s\33[u\33[10C\33[s%-20c\33[u\33[5C\33[s%-20s\33[u\33[15C\33[s%-20s\33[u\33[20C\33[s%-20d\33[u\33[10C\33[s%-20s\33[u\33[20C%-5s\33[0m\n"
#define PrintGuide             printf("\33[%d;%dH\33[s\33[38;2;%d;%d;%dm%s\33[u\33[%dC\33[38;2;%d;%d;%dm"version"\33[0m",windowsInfo.guideElement.positionY,windowsInfo.guideElement.positionX,windowsInfo.guideElement.titleColor.rColor,windowsInfo.guideElement.titleColor.gColor,windowsInfo.guideElement.titleColor.bColor,windowsInfo.guideElement.TitleName,windowsInfo.windowsX-6,windowsInfo.Version.rColor,windowsInfo.Version.gColor,windowsInfo.Version.bColor);

/*
 * 简介：格式化输出标题
 */

char *formatTitle(char *formatContent,TitleElement titleElement)
{
    sprintf(formatContent,"\33[%d;%dH\33[38;2;%d;%d;%dm%s\33[38;2;%d;%d;%dm\33[s%s\33[38;2;%d;%d;%dm%s\33[u\33[38;2;;128;138;135m%c\33[0m",
            titleElement.positionY,titleElement.positionX,
            windowsTag.titleLeft.color.rColor,windowsTag.titleLeft.color.gColor,windowsTag.titleLeft.color.bColor,windowsTag.titleLeft.tag,
            titleElement.titleColor.rColor,titleElement.titleColor.gColor,titleElement.titleColor.bColor,titleElement.TitleName,
            windowsTag.titleRight.color.rColor,windowsTag.titleRight.color.gColor,windowsTag.titleRight.color.bColor,windowsTag.titleRight.tag,
            titleElement.TitleName[0]);
    return formatContent;
}

/*
 * 简介：格式化输出索引
 */

char *formatIndex(char *formatContent,TitleElement titleElement,PersonList PersonList)
{
    sprintf(formatContent,"\33[%d;%dH\33[38;2;%d;%d;%dm%s\33[38;2;%d;%d;%dm%3d/%-3d\33[38;2;%d;%d;%dm%s\33[0m",
            titleElement.positionY,titleElement.positionX,
            windowsTag.titleLeft.color.rColor,windowsTag.titleLeft.color.gColor,windowsTag.titleLeft.color.bColor,windowsTag.titleLeft.tag,
            titleElement.titleColor.rColor,titleElement.titleColor.gColor,titleElement.titleColor.bColor,(PersonList.length == 0) ? 0 : windowsInfo.chooseIndex+1,PersonList.length,
            windowsTag.titleRight.color.rColor,windowsTag.titleRight.color.gColor,windowsTag.titleRight.color.bColor,windowsTag.titleRight.tag);
    return formatContent;
}

/*
 * 简介：格式化输出 TUI 边框标签
 */

char *formatTag(char *formatContent,tag tag)
{
    sprintf(formatContent,printTag,tag.color.rColor,tag.color.gColor,tag.color.bColor,tag.tag);
    return formatContent;
}

/*
 * 简介：初始化界面
 */

void InitWindows()
{
    char formatContent[100];
    Clear();
    printf("\33[0;0H\33[0m");
    printf("%s",formatTag(formatContent,windowsTag.leftUp));
    for (int i = 0; i < windowsInfo.windowsX-2; i++)
    {
        printf("%s",formatTag(formatContent,windowsTag.upAndDown));
    }
    printf("%s\n",formatTag(formatContent,windowsTag.rightUp));
    for (int i = 0; i < windowsInfo.windowsY-2; i++)
    {
        printf("%s%*s%s\n",formatTag(formatContent,windowsTag.leftAndRight),windowsInfo.windowsX-2,"",formatTag(formatContent,windowsTag.leftAndRight));
    }
    printf("%s",formatTag(formatContent,windowsTag.leftDown));
    for (int i = 0; i < windowsInfo.windowsX-2; i++)
    {
        printf("%s",formatTag(formatContent,windowsTag.upAndDown));
    }
    printf("%s",formatTag(formatContent,windowsTag.rightDown));
    printf("%s",formatTitle(formatContent,windowsInfo.logoElement));
    printf("%s",formatTitle(formatContent,windowsInfo.fliterElement));
    PrintGuide;
}

/*
 * 简介：清除显示内容
 */
void clearContent()
{
    for (int i = 0; i < windowsInfo.windowsY-2; i++)
    {
        printf("\33[%d;2H%*s\33[0m",i+2,windowsInfo.windowsX-2," ");
    }
}

/*
 * 简介：显示联系人
 */

int DisplayPersion(PersonList personList)
{
    int outLenght = 0;
    char formatContent[windowsInfo.windowsX];
    printf("%s",formatIndex(formatContent,windowsInfo.indexElement,personList));
    if (windowsInfo.chooseIndex >= windowsInfo.windowsY-2)
    {
        outLenght = (windowsInfo.chooseIndex + 1) - (windowsInfo.windowsY - 2);
    }
    for (int i = 0 + outLenght,j = 0; i < personList.length;i++,j++)
    {
        if (j == windowsInfo.windowsY-2) return 0;
        printf("\33[%d;2H\33[0m",j+2);
        if (i == windowsInfo.chooseIndex)
        {
            printf(printChooseBodyFormat,windowsInfo.fouce.rColor,windowsInfo.fouce.gColor,windowsInfo.fouce.bColor,personList.person[i].name,personList.person[i].sex,personList.person[i].phoneNumber,personList.person[i].email,personList.person[i].postCode,personList.person[i].address,(personList.person[i].like == 1) ? "Yes" : (personList.person[i].like == 0) ? "No" : " ");
        }else{
            printf(tuiPrintBodyFormat,windowsInfo.unfouce.rColor,windowsInfo.unfouce.gColor,windowsInfo.unfouce.bColor,personList.person[i].name,personList.person[i].sex,personList.person[i].phoneNumber,personList.person[i].email,personList.person[i].postCode,personList.person[i].address,(personList.person[i].like == 1) ? "Yes" : (personList.person[i].like == 0) ? "No" : " ");
        }
    }
    return 0;
}

/*
 * 简介：过滤联系人
 */

void DoFliter(PersonList personList,char fliterName[5],PersonList *fliterPerson)
{
    int j = 0;
    for (int i = 0; i < personList.length; i++)
    {
        if (fuzzyFind(personList.person[i].name,fliterName))
        {
            fliterPerson->person[j++] = personList.person[i];
            fliterPerson->length = j;
        }
    }
    clearContent();
    DisplayPersion(*fliterPerson);
}

/*
 * 简介：过滤联系人操作
 */

void FliterPerson(PersonList personList,PersonList *outputPerson,PersonList *fliterPerson,char *fliterName)
{
    char formatContent[windowsInfo.windowsX],input;
    int i = strlen(fliterName);
    DisplayCursor;
    windowsInfo.chooseIndex = 0;
    strcpy(windowsInfo.fliterElement.TitleName,"f     ");
    printf("%s",formatTitle(formatContent,windowsInfo.fliterElement));
    printf("\33[%d;%dH%s\33[0m",windowsInfo.fliterElement.positionY,windowsInfo.fliterElement.positionX+3,fliterName);
    while (input = my_getche())
    {
        char endFliterName[10] = "";
        if (input == ENTER) break;
        if (input == QUIT)
        {
            fliterPerson->length = 0;
            strcpy(fliterName,"");
            strcpy(windowsInfo.fliterElement.TitleName,"fliter");
            printf("%s",formatTitle(formatContent,windowsInfo.fliterElement));
            break;
        }
        if (input == BACKSPACE)
        {
            if (--i <= 0)
            {
                strcpy(fliterName,"");
                break;
            }
            strncpy(endFliterName,fliterName,strlen(fliterName)-1);
            strcpy(fliterName,endFliterName);
            printf("\33[%d;%dH%-4s\33[38;2;%d;%d;%dm%s\33[0m",windowsInfo.fliterElement.positionY,windowsInfo.fliterElement.positionX+3,fliterName,windowsTag.titleRight.color.rColor,windowsTag.titleRight.color.gColor,windowsTag.titleRight.color.bColor,windowsTag.titleRight.tag);
            DoFliter(personList,fliterName,fliterPerson);
        }else{
            fliterName[i+1] = '\0';
            fliterName[i++] = input;
            DoFliter(personList,fliterName,fliterPerson);
        }
        if (i >= 5)
        {
            strncpy(endFliterName,fliterName,strlen(fliterName)-1);
            strcpy(fliterName,endFliterName);
            printf("\33[%d;%dH%-4s\33[38;2;%d;%d;%dm%s%s\33[0m",windowsInfo.fliterElement.positionY,windowsInfo.fliterElement.positionX+3,fliterName,windowsTag.titleRight.color.rColor,windowsTag.titleRight.color.gColor,windowsTag.titleRight.color.bColor,windowsTag.titleRight.tag);
            break;
        }
        printf("\33[%d;%dH%s\33[0m",windowsInfo.fliterElement.positionY,windowsInfo.fliterElement.positionX+3,fliterName);
    }
    if (i <= 0)
    {
        fliterPerson->length = 0;
        strcpy(fliterName,"");
        strcpy(windowsInfo.fliterElement.TitleName,"fliter");
        printf("%s",formatTitle(formatContent,windowsInfo.fliterElement));
    }
    UnDisplayCursor;
}

/*
 * 简介：删除联系人操作
 */

void TUIRemovePerson(PersonList *personList,PersonList *outputPerson)
{
    int removeLenght = 0,countRemoveTimes = 0;
    for (int i = 0; i < personList->length; i++)
    {
        if (strcmp(personList->person[i].name,outputPerson->person[windowsInfo.chooseIndex].name))
        {
            personList->person[removeLenght++] = personList->person[i];
        }
    }
    countRemoveTimes = personList->length - removeLenght;
    personList->length = removeLenght;
    if (personList != outputPerson)
    {
        removeLenght = 0;
        for (int i = 0; i < outputPerson->length; i++)
        {
            if (strcmp(outputPerson->person[i].name,outputPerson->person[windowsInfo.chooseIndex].name))
            {
                outputPerson->person[removeLenght++] = outputPerson->person[i];
            }
        }
        outputPerson->length = removeLenght;
    }
    windowsInfo.chooseIndex = (windowsInfo.chooseIndex-countRemoveTimes <= 0) ? 0 : windowsInfo.chooseIndex - countRemoveTimes;
}

/*
 * 简介：保存联系人属性
 */

void SavePersonElement(PersonList *personList,PersonList *outputPerson,int *elementIndex,char elementValue[20],int savePositionY,int *changeValueLenght)
{
    int inPersonListIndex = -1;
    for (int i = 0; i < personList->length; i++)
    {
        if (!strcmp(personList->person[i].name,outputPerson->person[windowsInfo.chooseIndex].name)) inPersonListIndex = i;
    }
    if (inPersonListIndex == -1) inPersonListIndex = personList->length;
    switch (*elementIndex)
    {
        case 0:
            strcpy(personList->person[inPersonListIndex].name,elementValue);
            strcpy(outputPerson->person[windowsInfo.chooseIndex].name,elementValue);
            break;
        case 1:
            if (checkPersonSex(elementValue[0]))
            {
                personList->person[inPersonListIndex].sex = toupper(elementValue[0]);
                outputPerson->person[windowsInfo.chooseIndex].sex = toupper(elementValue[0]);
            }else{
                printf("\33[%d;2H\33[s%-*s\33[u\33[0m",savePositionY,windowsInfo.windowsX-2,"Plase input M/w,Hit any key to continue...");
                strcpy(elementValue,"");
                *changeValueLenght--;*elementIndex-=1;
                my_getch();
                printf("\33[%d;2H\33[s%-*s\33[u\33[0m",savePositionY,windowsInfo.windowsX-2," ");
            }
            break;
        case 2:
            if (checkPersonNumber(elementValue))
            {
                strcpy(personList->person[inPersonListIndex].phoneNumber,elementValue);
                strcpy(outputPerson->person[windowsInfo.chooseIndex].phoneNumber,elementValue);
            }else{
                printf("\33[%d;2H\33[s%-*s\33[u\33[0m",savePositionY,windowsInfo.windowsX-2,"Plase input the correct phone number,Hit any key to continue...");
                strcpy(elementValue,"");
                *changeValueLenght = 0;*elementIndex-=1;
                my_getch();
                printf("\33[%d;2H\33[s%-*s\33[u\33[0m",savePositionY,windowsInfo.windowsX-2," ");
            }
            break;
        case 3:
            strcpy(personList->person[inPersonListIndex].email,elementValue);
            strcpy(outputPerson->person[windowsInfo.chooseIndex].email,elementValue);
            break;
        case 4:
            if (checkPersonNumber(elementValue))
            {
                personList->person[inPersonListIndex].postCode   = atoi(elementValue);
                outputPerson->person[windowsInfo.chooseIndex].postCode = atoi(elementValue);
            }else{
                printf("\33[%d;2H\33[s%-*s\33[u\33[0m",savePositionY,windowsInfo.windowsX-2,"Plase input the correct postcode,Hit any key to continue...");
                strcpy(elementValue,"");
                *changeValueLenght = 0;*elementIndex-=1;
                my_getch();
                printf("\33[%d;2H\33[s%-*s\33[u\33[0m",savePositionY,windowsInfo.windowsX-2," ");
            }
            break;
        case 5:
            strcpy(personList->person[inPersonListIndex].address,elementValue);
            strcpy(outputPerson->person[windowsInfo.chooseIndex].address,elementValue);
            break;
        case 6:
            if (checkPersonLike(elementValue[0]))
            {
                personList->person[inPersonListIndex].like = (toupper(elementValue[0]) == 'Y') ? 1 : 0;
                outputPerson->person[windowsInfo.chooseIndex].like = (toupper(elementValue[0]) == 'Y') ? 1 : 0;
            }else{
                printf("\33[%d;2H\33[s%-*s\33[u\33[0m",savePositionY,windowsInfo.windowsX-2,"Plase input Y/N,Hit any key to continue...");
                strcpy(elementValue,"");
                *changeValueLenght--;*elementIndex-=1;
                my_getch();
                printf("\33[%d;2H\33[s%-*s\33[u\33[0m",savePositionY,windowsInfo.windowsX-2," ");
            }
            break;
        default:
            break;
    }
}

/*
 * 简介：元素输出
 */

void TableInput(PersonList *personList,PersonList *outputPerson)
{
    char ch,changeValue[20] = " ",tmpChangeValue[20];
    int elementPreSpace[9] = {2,12,17,32,52,62,82,87,93};
    int changePositionY = (windowsInfo.chooseIndex >= windowsInfo.windowsY-2) ? windowsInfo.windowsY-1 : windowsInfo.chooseIndex+2;
    int changePositionX = elementPreSpace[0];
    int changeIndex = 0,changeValueLenght = 0;
    while (ch = my_getche())
    {
        if (ch == TAB)
        {
            changeIndex += 1;
            changeIndex %= 7;
            changeValueLenght = 0;
            strcpy(changeValue," ");
            printf("\33[%d;2H"printChooseBodyFormat,changePositionY,windowsInfo.fouce.rColor,windowsInfo.fouce.gColor,windowsInfo.fouce.bColor,outputPerson->person[windowsInfo.chooseIndex].name,outputPerson->person[windowsInfo.chooseIndex].sex,outputPerson->person[windowsInfo.chooseIndex].phoneNumber,outputPerson->person[windowsInfo.chooseIndex].email,outputPerson->person[windowsInfo.chooseIndex].postCode,outputPerson->person[windowsInfo.chooseIndex].address,(outputPerson->person[windowsInfo.chooseIndex].like == 1) ? "Yes" : (outputPerson->person[windowsInfo.chooseIndex].like == 0) ? "No" : " ");
            if (outputPerson->person[outputPerson->length-1].postCode == -1) printf("\33[%d;52H%s\33[0m",(windowsInfo.chooseIndex >= windowsInfo.windowsY-2) ? windowsInfo.windowsY-1 : windowsInfo.chooseIndex+2,"  ");
            changePositionX = elementPreSpace[changeIndex];
            printf("\33[%d;%dH\33[s%*s\33[u\33[0m",changePositionY,changePositionX,elementPreSpace[changeIndex+1] - elementPreSpace[changeIndex],changeValue);
        } else if (ch == ENTER){
            if (changeValueLenght != 0)
            {
                SavePersonElement(personList,outputPerson,&changeIndex,changeValue,changePositionY,&changeValueLenght);
            }
            changeIndex += 1;
            changeIndex %= 7;
            changeValueLenght = 0;
            strcpy(changeValue,"");
            printf("\33[%d;2H"printChooseBodyFormat,changePositionY,windowsInfo.fouce.rColor,windowsInfo.fouce.gColor,windowsInfo.fouce.bColor,outputPerson->person[windowsInfo.chooseIndex].name,outputPerson->person[windowsInfo.chooseIndex].sex,outputPerson->person[windowsInfo.chooseIndex].phoneNumber,outputPerson->person[windowsInfo.chooseIndex].email,outputPerson->person[windowsInfo.chooseIndex].postCode,outputPerson->person[windowsInfo.chooseIndex].address,(outputPerson->person[windowsInfo.chooseIndex].like == 1) ? "Yes" : (outputPerson->person[windowsInfo.chooseIndex].like == 0) ? "No" : " ");
            if (outputPerson->person[outputPerson->length-1].postCode == -1) printf("\33[%d;52H%s\33[0m",(windowsInfo.chooseIndex >= windowsInfo.windowsY-2) ? windowsInfo.windowsY-1 : windowsInfo.chooseIndex+2,"  ");
            changePositionX = elementPreSpace[changeIndex];
            printf("\33[%d;%dH\33[s%*s\33[u\33[0m",changePositionY,changePositionX,elementPreSpace[changeIndex+1] - elementPreSpace[changeIndex],changeValue);
        }else if(ch == BACKSPACE){
            if (--changeValueLenght <= 0) strcpy(changeValue," ");
            changePositionX -= (changePositionX-1 >= elementPreSpace[changeIndex]) ? 1 : 0;
            strncpy(tmpChangeValue,changeValue,strlen(changeValue)-1);
            strcpy(changeValue,tmpChangeValue);
            (changePositionX > elementPreSpace[changeIndex]) ? printf(" \33[%d;%dH\33[s   \33[u",changePositionY,changePositionX) : printf("\33[%d;%dH\33[s   \33[u",changePositionY,elementPreSpace[changeIndex]);
        }else{
            changeValue[changeValueLenght+1] = '\0';
            changeValue[changeValueLenght++] = ch;
            changePositionX++;
        }
        if (ch == QUIT)
        {
            UnDisplayCursor;
            if (outputPerson->person[outputPerson->length-1].postCode == -1) printf("\33[%d;52H%s\33[0m",(windowsInfo.chooseIndex >= windowsInfo.windowsY-2) ? windowsInfo.windowsY-1 : windowsInfo.chooseIndex+2,"  ");
            break;
        }
    }
}

/*
 * 简介：修改联系人
 */

void TUIChangePerson(PersonList *personList,PersonList *outputPerson)
{
    DisplayCursor;
    printf("\33[%d;%dH\33[s%*s\33[u\33[0m",(windowsInfo.chooseIndex >= windowsInfo.windowsY-2) ? windowsInfo.windowsY-1 : windowsInfo.chooseIndex+2,2,10,"");
    TableInput(personList,outputPerson);
    UnDisplayCursor;
}

/*
 * 简介：初始化联系人
 */

void InitPerson(Person *initPerson)
{
    strcpy(initPerson->name," ");
    initPerson->sex = ' ';
    strcpy(initPerson->phoneNumber," ");
    strcpy(initPerson->email," ");
    initPerson->postCode = -1;
    strcpy(initPerson->address," ");
    initPerson->like = -1;
}

/*
 * 简介：检测联系人是否输入全
 */

int checkInputPerson(Person *checkPerson)
{
    if (!strcmp(checkPerson->name," ")) return 0;
    if (checkPerson->sex == ' ') return 0;
    if (!strcmp(checkPerson->phoneNumber," ")) return 0;
    if (!strcmp(checkPerson->email," ")) return 0;
    if (checkPerson->postCode == -1) return 0;
    if (!strcmp(checkPerson->address," ")) return 0;
    if (checkPerson->like == -1) return 0;
    return 1;
}

/*
 * 简介：进入动画
 */
double easein(double progressRate)
{
    return pow(progressRate,5);
}

/*
 * 简介：退出动画
 */
double easeout(double progressRate)
{
    return (1-pow((progressRate-1),4));
}

/*
 * 简介：添加联系人操作
 */

void TUIAddPerson(PersonList *personList,PersonList *outputPerson)
{
    char ch,changeValue[20] = " ",tmpChangeValue[20];
    double progressRate;
    int elementPreSpace[8] = {2,12,17,32,52,62,82,87};
    int addPositionY,addPositionX = elementPreSpace[4],preChooseIndex = windowsInfo.chooseIndex;
    InitPerson(&outputPerson->person[outputPerson->length]);
    progressRate = 0;   //初始化
    do{
        progressRate += 1.0/(outputPerson->length - preChooseIndex);
        DisplayPersion(*outputPerson);
        usleep(easein(progressRate)*10000);
        if (outputPerson->person[outputPerson->length].postCode == -1) printf("\33[%d;52H%s\33[0m",(windowsInfo.chooseIndex >= windowsInfo.windowsY-2) ? windowsInfo.windowsY-1 : windowsInfo.chooseIndex+2,"  ");
        if (outputPerson->length == 0) break;
    }while (++windowsInfo.chooseIndex != outputPerson->length);
    outputPerson->length++;
    DisplayPersion(*outputPerson);
    if (outputPerson->person[outputPerson->length-1].postCode == -1) printf("\33[%d;52H%s\33[0m",(windowsInfo.chooseIndex >= windowsInfo.windowsY-2) ? windowsInfo.windowsY-1 : windowsInfo.chooseIndex+2,"  ");
    DisplayCursor;
    printf("\33[%d;2H\33[0m",(windowsInfo.chooseIndex >= windowsInfo.windowsY-2) ? windowsInfo.windowsY-1 : windowsInfo.chooseIndex+2);
    TableInput(personList,outputPerson);
    if (checkInputPerson(&outputPerson->person[outputPerson->length-1]))
    {
        personList->length += (outputPerson == personList) ? 0 : 1;
    }else{
        outputPerson->length -= (outputPerson->length == 0) ? 0 : 1;
        progressRate = 0;   //初始化
        do{
            progressRate += 1.0/(outputPerson->length - preChooseIndex);
            DisplayPersion(*outputPerson);
            usleep(easeout(progressRate)*10000);
            if (outputPerson->length == 0) break;
        }while (--windowsInfo.chooseIndex != preChooseIndex);
    }
}
