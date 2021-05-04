#ifndef THEME_H
#define THEME_H

typedef struct rgbcolor
{
    int rColor;
    int gColor;
    int bColor;
}rgbcolor;

typedef struct tag
{
    char tag[10];
    rgbcolor color;
}tag;

typedef struct WindowsTag
{
    tag rightUp;
    tag leftUp;
    tag rightDown;
    tag leftDown;
    tag upAndDown;
    tag leftAndRight;
    tag titleLeft;
    tag titleRight;
}WindowsTag;
WindowsTag windowsTag;

typedef struct TitleElement
{
    char TitleName[90];
    int positionX;
    int positionY;
    rgbcolor titleColor;
}TitleElement;

typedef struct WindowsInfo
{
    int windowsX;
    int windowsY;
    int chooseIndex;
    TitleElement logoElement;
    TitleElement fliterElement;
    TitleElement indexElement;
    TitleElement guideElement;
    rgbcolor Version;
    rgbcolor fouce;
    rgbcolor unfouce;
}WindowsInfo;
WindowsInfo windowsInfo;

void loadingTheme();

#endif