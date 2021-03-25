#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int data;
    struct node *next;

}lian;      //定义链表结构体lian

void Biao(lian *head,int i)     //生成新节点连接到链表并赋值
{
    lian *nullNextNode = head;
    while (1)
    {
        if (nullNextNode->next != NULL)
        {
            nullNextNode = nullNextNode->next;
            printf("ed");
        }else{
            printf("a");
            nullNextNode = (lian * )malloc(sizeof(lian));
            nullNextNode->data = i++;
            nullNextNode->next = NULL;
            break;
        }
    }
    printf("%d\n%d",nullNextNode->data);
}

int main()
{
    lian head;
    head.next = NULL;
    int i = 0;
    Biao(&head,i);
    Biao(&head,i);
    printf("%d\n%d",head.next->data,head.next->next->data);
}

