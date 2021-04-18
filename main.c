#include "main.h"

int main(int argc,char *argv[])         //argc 输入参数数量； argv 输入的参数
{
    PersonList PersonList;
    char systemLanguage[10];            //用于存储程序语言设置
    strcpy(systemLanguage,"CN.txt");    //初始化默认为中文
    ReadPerson(&PersonList,systemLanguage);     //读取通信录数据
    LoadingLanguage(systemLanguage);    //加载语言包
    while(Ture)
    {
        int opt;                        //每次循环初始化,用于存储操作序号
        if (argc >= 2)                  //当 argc 大于等于二时说明是 CLI 操作
        {
            opt = GetOpt(argc,argv);
        }else{
            opt = Menu();
        }
        switch (opt)
        {
            case 1:
                AddPerson(&PersonList,argc,argv);
                SavePerson(PersonList,systemLanguage);
                break;
            case 2:
                ChangePerson(&PersonList,argc,argv);
                SavePerson(PersonList,systemLanguage);
                break;
            case 3:
                RemovePerson(&PersonList,argc,argv);
                SavePerson(PersonList,systemLanguage);
                break;
            case 4:
                DisplayPerson(PersonList,FindPerson(&PersonList,argc,argv),systemLanguage);
                break;
            case 5:
                SharePerson(PersonList,argc,argv,systemLanguage);
                break;
            case 6:
                ResetPerson(&PersonList);
                SavePerson(PersonList,systemLanguage);
                break;
            case 7:
                DisplayPerson(PersonList,-1,systemLanguage);
                break;
            case 8:
                Setting(systemLanguage);
                SavePerson(PersonList,systemLanguage);
                break;
            case 9:
                if (argc < 2)
                {
                    printf("Error\n");
                    break;
                }//避免在使用非CLI时调用
                PrintHelp(argc,argv);
                break;
            case 10:
                if (argc < 2)
                {
                    printf("Error\n");
                    break;
                }
                DisplayVersion();
                break;
            case 0:
                exit(0);
            default:
                printf("Error\n");
                break;
        }
        if (argc >= 2) break;
        Pasue();
        Clear();    
    }
    return 0;
}
