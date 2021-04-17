#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

int main()
{
    int tableBoxLenght = 20;
    char languageNameCN[] = "姓名";
    char languageNameUS[] = "Numéro de téléphone";
    char languageNameFC[] = "Adresse";
    wchar_t *wLanguageName;
    swprintf(wLanguageName,0, L"%s", languageNameCN);
    printf("%d\n",strlen(languageNameCN));
    mbstowcs(wLanguageName,languageNameCN,strlen(languageNameCN)+1);
    printf("%d\n",wcslen(wLanguageName));
    return 0;
}