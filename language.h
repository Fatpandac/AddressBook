#ifndef LANGUAGEFILE_H
#define LANGUAGEFILE_H
#define LanguageLineSize   60     //语言包总行数

char language[LanguageLineSize][60];      //定义语言数组，用于保存对应语言包数据

extern int LoadingLanguage(char systemLanguage[10]);
extern int GetSelectLanguage(char systemLanguage[10]);

#endif