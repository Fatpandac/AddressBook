#include "main.h"

/*
 * 简介：进行 CLI 操作判断，并调用函数
 */

void DoCliOpt(PersonList *PersonList,int argc,char *argv[],char systemLanguage[10])
{
    switch (GetOpt(argc,argv))
    {
        case 1:
            CLIAddPerson(PersonList,argc,argv);
            SavePerson(*PersonList,systemLanguage);
            break;
        case 2:
            CLIChangePerson(PersonList,argc,argv);
            SavePerson(*PersonList,systemLanguage);
            break;
        case 3:
            CLIRemovePerson(PersonList,argc,argv);
            SavePerson(*PersonList,systemLanguage);
            break;
        case 4:
            DisplayPerson(*PersonList,CLIFindPerson(PersonList,argc,argv),systemLanguage);
            break;
        case 5:
            CLISharePerson(*PersonList,argc,argv,systemLanguage);
            break;
        case 6:
            ResetPerson(PersonList);
            SavePerson(*PersonList,systemLanguage);
            break;
        case 7:
            DisplayPerson(*PersonList,-1,systemLanguage);
            break;
        case 9:
            PrintHelp(argc,argv);
            break;
        case 10:
            DisplayVersion();
            break;
        default:
            break;
    }
}

/*
 * 简介：进行普通操作判断，并调用函数
 */

void DoNormalOpt(PersonList *PersonList,char systemLanguage[10])
{
    switch (Menu())
    {
        case 1:
            AddPerson(PersonList);
            SavePerson(*PersonList,systemLanguage);
            break;
        case 2:
            ChangePerson(PersonList);
            SavePerson(*PersonList,systemLanguage);
            break;
        case 3:
            RemovePerson(PersonList);
            SavePerson(*PersonList,systemLanguage);
            break;
        case 4:
            DisplayPerson(*PersonList,FindPerson(PersonList),systemLanguage);
            break;
        case 5:
            SharePerson(*PersonList);
            break;
        case 6:
            ResetPerson(PersonList);
            SavePerson(*PersonList,systemLanguage);
            break;
        case 7:
            DisplayPerson(*PersonList,-1,systemLanguage);
            break;
        case 8:
            Setting(systemLanguage);
            SavePerson(*PersonList,systemLanguage);
            break;
        case 0:
            exit(0);
        default:
            printf("Error\n");
    }
}

int main(int argc,char *argv[])                 //argc 输入参数数量； argv 输入的参数
{
    PersonList PersonList;
    char systemLanguage[20];                    //用于存储程序语言设置
#ifdef WIN32
    if (strcmp(argv[0],"AddressBook"))
    {
        strncpy(exeFilePath,argv[0],strlen(argv[0])-strlen(strrchr(argv[0],'\\')))[strlen(argv[0])-strlen(strrchr(argv[0],'\\'))] = '\0';
    }else{
        strcpy(exeFilePath,".\\");
    }
#endif
#ifdef linux
    if (strcmp(argv[0],"AddressBook")) 
    {
        strncpy(exeFilePath,argv[0],strlen(argv[0])-strlen(strrchr(argv[0],'/')))[strlen(argv[0])-strlen(strrchr(argv[0],'/'))] = '\0';
    }else{
        strcpy(exeFilePath,"./");
    }
    
#endif                                          //初始化执行文件路径
    ReadPerson(&PersonList,systemLanguage);     //读取通信录数据
    LoadingLanguage(systemLanguage);            //加载语言包
    if (!strcmp(argv[argc-1],"TUI")) TUI(&PersonList,systemLanguage);
    if (argc >= 2)                  //当 argc 大于等于二时说明是 CLI 操作
    {
        DoCliOpt(&PersonList,argc,argv,systemLanguage);
    }else{
        while (1)
        {
            DoNormalOpt(&PersonList,systemLanguage);
            Pasue();
            Clear();    
        }
    }
    return 0;
}
