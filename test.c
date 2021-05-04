#include <stdio.h>
#include <stdlib.h>

int my_getch()
{
#ifdef linux
    char c;
    system("stty -echo");  //不回显
    system("stty -icanon");//设置一次性读完操作，如使用getchar()读操作，不需要按enter
    c = getchar();
    system("stty icanon");//取消上面的设置
    system("stty echo");//回显
    return c;
#endif
#ifdef WIN32
    return getch();
#endif
}

int main()
{
    int ch;
    do{
        ch=my_getch();  //从键盘读入
        //若关于键盘管理的知识积累不够，请暂时不必搞懂这个if语句中的处理
        if ( ch == 0xe0 )    
        {
            ch=my_getch();
            ch+=80; 
        }
        //从下面开始读懂程序
        if ( ch == 161 )
            printf("PageDown\n");
        else if ( ch == 153 )
            printf("PageUp\n");
        else
            printf("ch=%c keyValue=%d\n", ch, ch);
    } while (ch != 27 ); //ESC 退出
    return 0;
}