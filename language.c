#include <stdio.h>
#include <string.h>
#ifdef linux
#include <dirent.h>
#include <unistd.h>
#endif
#ifdef WIN32
#include <dirent.h>
#include <io.h>
#endif              //在 Linux 和 Windows 不同系统环境下预处理引用不同的库

#include "language.h"
#include "file.h"
/*
 * 简介：加载语言包
 */

int LoadingLanguage(char systemLanguage[10])
{
    char languageFilePath[100];
    strcpy(languageFilePath,exeFilePath);
    strcat(languageFilePath,"/language/");
    strcat(languageFilePath,systemLanguage);
    FILE *langFile = fopen(languageFilePath,"r");
    if (langFile == NULL)
    {
        printf("%s\n","Read failure");
        fclose(langFile);
        return 0;
    }
    for (int i = 0;i <= LanguageLineSize;i++)
    {
        fscanf(langFile,"%[^\n]\n",language[i]);        //读取一整句话
    }
    fclose(langFile);
    return 0;
}

/*
 * 简介：读取 language 文件夹下的语言包，并进行系统语言选择
 */

int GetSelectLanguage(char systemLanguage[10])
{
    char languageDirPath[100];                   //存储 language 文件夹地址   
    char languageDirNameList[20][10];            //存储 language 文件夹下文件名称
    int languageDirNumber = 0;                   //存储 language 文件夹下文件个数
    strcpy(languageDirPath,exeFilePath);
    strcat(languageDirPath,"/language");
#ifdef linux
    DIR *dir;
    struct dirent *ptr;
    if ((dir=opendir(languageDirPath)) == NULL)
    {
        perror("Open dir error...");
        return 0;
    }
    while ((ptr = readdir(dir)) != NULL)
    {
        if(strcmp(ptr->d_name,".")==0 || strcmp(ptr->d_name,"..")==0)
        {
            continue;
        }else if(ptr->d_type == 8){
            strcpy(languageDirNameList[languageDirNumber++],ptr->d_name);
        }else{
            continue;
        }
    }
    closedir(dir);
    opendir("..");      //退回到初始的目录中
#endif
#ifdef WIN32
    struct _finddata_t file;
    intptr_t hFile;
    if (_chdir(languageDirPath))
    {
        printf("Open dir error...");
        return 0;
    }
    hFile = _findfirst("*.txt",&file);
    do{
        strcpy(languageDirNameList[languageDirNumber++],file.name);
    }while (_findnext(hFile,&file) == 0);
    _findclose(hFile);
    _chdir("..");       //退回到初始的目录中
#endif
    for (int i = 0;i < languageDirNumber;i++)
    {
        printf("[%d] %s\n",i+1,languageDirNameList[i]);   
    }
    int selectIndex = 0;                             //选择的语言序号
    while (1)
    {
        printf("%s",language[27]);      //"请输入序号："
        getchar();
        selectIndex = getchar()-48;
        if (selectIndex > 0 && selectIndex < languageDirNumber+1) break;
        printf("%s\n",language[28]);
    }
    strcpy(systemLanguage,languageDirNameList[selectIndex-1]);
    return 0;
}