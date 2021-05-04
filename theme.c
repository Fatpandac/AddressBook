#include <stdio.h>
#include <string.h>

#include "file.h"
#include "control.h"
#include "theme.h"

WindowsTag windowsTag = {{"┐",{239, 141, 204}},
                         {"┌",{239, 239, 204}},
                         {"┘",{175, 239, 204}},
                         {"└",{131, 239, 204}},
                         {"─",{190, 138, 204}},
                         {"│",{239, 239, 204}},
                         {"┤",{131, 239, 204}},
                         {"├",{239, 239, 204}}};
                    

WindowsInfo windowsInfo = {90,20,
                          0,
                          {"AddressBook",4,1,{190, 138, 204}},
                          {"fliter",17,1,{190, 138, 204}},
                          {"index",80,20,{0,255,0}},
                          {"w/k/↑ s/j/↓: navigate, esc/Q: close, R: remove, C: change, A: add",1,21,{255,147,192}},
                          {255,0,0},
                          {0,255,0},
                          {0,0,255}};

/*
 * 简介：加载界面符号
 */

void loadingWindowsTag(char content[50])
{
    sscanf(content,"rightUpTag:%s",windowsTag.rightUp.tag);
    sscanf(content,"rightUpColor:(%d,%d,%d)",&windowsTag.rightUp.color.rColor,&windowsTag.rightUp.color.gColor,&windowsTag.rightUp.color.bColor);
    sscanf(content,"leftUpTag:%s",windowsTag.leftUp.tag);
    sscanf(content,"leftUpColor:(%d,%d,%d)",&windowsTag.leftUp.color.rColor,&windowsTag.leftUp.color.gColor,&windowsTag.leftUp.color.bColor);
    sscanf(content,"rightDownTag:%s",windowsTag.rightDown.tag);
    sscanf(content,"rightDownColor:(%d,%d,%d)",&windowsTag.rightDown.color.rColor,&windowsTag.rightDown.color.gColor,&windowsTag.rightDown.color.bColor);
    sscanf(content,"leftDownTag:%s",windowsTag.leftDown.tag);
    sscanf(content,"leftDownColor:(%d,%d,%d)",&windowsTag.leftDown.color.rColor,&windowsTag.leftDown.color.gColor,&windowsTag.leftDown.color.bColor);
    sscanf(content,"upAndDownTag:%s",windowsTag.upAndDown.tag);
    sscanf(content,"upAndDownColor:(%d,%d,%d)",&windowsTag.upAndDown.color.rColor,&windowsTag.upAndDown.color.gColor,&windowsTag.upAndDown.color.bColor);
    sscanf(content,"leftAndRightTag:%s",windowsTag.leftAndRight.tag);
    sscanf(content,"leftAndRightColor:(%d,%d,%d)",&windowsTag.leftAndRight.color.rColor,&windowsTag.leftAndRight.color.gColor,&windowsTag.leftAndRight.color.bColor);
    sscanf(content,"titleLeftTag:%s",windowsTag.titleLeft.tag);
    sscanf(content,"titleLeftColor:(%d,%d,%d)",&windowsTag.titleLeft.color.rColor,&windowsTag.titleLeft.color.gColor,&windowsTag.titleLeft.color.bColor);
    sscanf(content,"titleRightTag:%s",windowsTag.titleRight.tag);
    sscanf(content,"titleRightColor:(%d,%d,%d)",&windowsTag.titleRight.color.rColor,&windowsTag.titleRight.color.gColor,&windowsTag.titleRight.color.bColor);
}

/*
 * 简介：加载界面信息
 */

void loadingWindowsInfo(char *content)
{
    sscanf(content,"logoElementColor:(%d,%d,%d)",&windowsInfo.logoElement.titleColor.rColor,&windowsInfo.logoElement.titleColor.gColor,&windowsInfo.logoElement.titleColor.bColor);
    sscanf(content,"fliterElementColor:(%d,%d,%d)",&windowsInfo.fliterElement.titleColor.rColor,&windowsInfo.fliterElement.titleColor.gColor,&windowsInfo.fliterElement.titleColor.bColor);
    sscanf(content,"indexElementColor:(%d,%d,%d)",&windowsInfo.indexElement.titleColor.rColor,&windowsInfo.indexElement.titleColor.gColor,&windowsInfo.indexElement.titleColor.bColor);
    sscanf(content,"guideElementColor:(%d,%d,%d)",&windowsInfo.guideElement.titleColor.rColor,&windowsInfo.guideElement.titleColor.gColor,&windowsInfo.guideElement.titleColor.bColor);
    sscanf(content,"fouceColor:(%d,%d,%d)",&windowsInfo.fouce.rColor,&windowsInfo.fouce.gColor,&windowsInfo.fouce.bColor);
    sscanf(content,"unfouceColor:(%d,%d,%d)",&windowsInfo.unfouce.rColor,&windowsInfo.unfouce.gColor,&windowsInfo.unfouce.bColor);
    sscanf(content,"versionColor:(%d,%d,%d)",&windowsInfo.Version.rColor,&windowsInfo.Version.gColor,&windowsInfo.Version.bColor);
}

/*
 * 简介：加载主题
 */

void loadingTheme()
{
    int contentLenght = 0,isWindowsTag = 0,c;
    char content[100];
    FILE *themeFile = fopen("theme.txt","r+");
    if (themeFile != NULL)
    {
        while(c = fgetc(themeFile))
        {
            if (c != ' ' && c != '\n' && c != EOF)
            {
                content[contentLenght+1] = '\0';
                content[contentLenght++] = c;
            }
            if(c == '\n' || c == EOF)
            {
                contentLenght = 0;
                if (!strcmp("windowsTag",content)) isWindowsTag = 1;
                if (!strcmp("windowsInfo",content)) isWindowsTag = 0;
                if (isWindowsTag)
                {
                    loadingWindowsTag(content);
                }else{
                    loadingWindowsInfo(content);
                }
                if (c == EOF) break;
            }
        }
    }
}
