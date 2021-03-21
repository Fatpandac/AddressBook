#include <stdio.h>
#define N 3

typedef struct student{
    char name[10];
    char add[10];
    int yz;
    int number;
}STU;

void input(STU *p,int n)
{
    int i;
    for(i=0;i < N;i++)
    {
        scanf("%s%s%d%d",p[i].name,p[i].add,&p[i].yz,&p[i].number);
    }
}

void output(STU *p,int n)
{
    printf("\t姓名\t家庭住址\t邮政编码\t电话号码\t\n");
    for(int i=0;i<N;i++)
    {
        printf("\t%s\t%s\t%d\t%d\t\n",p[i].name,p[i].add,p[i].yz,p[i].number);
    }
}

int main()
{
    STU student[N];
    input(student,N);
    output(student,N);
    return 0;
}
