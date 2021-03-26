#include <stdio.h>
#include <string.h>

void change(char sentens[10])
{
    strcpy(sentens,"No");
}

int main()
{
    char sentens[10];
    strcpy(sentens,"OK");
    printf("%s",sentens);
    change(sentens);
    printf("%s",sentens);
}

