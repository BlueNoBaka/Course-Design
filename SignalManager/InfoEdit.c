#include <stdio.h>
#include <stdlib.h>
#include "RSignal.h"
#include "GetInput.h"

extern int amount;
extern struct Signal *Head;

void insert(struct Signal *p_front, struct Signal *p_next)
{
	struct Signal *p1;
	char flag; //记录是否继续添加信号机

	p1=(struct Signal *)malloc(sizeof(struct Signal));
	InputElement(p1,5); //输入信号机信息

	p1->front=p_front; //建立新一项的前驱指针
	p1->next=p_next; //建立新一项的后继指针
	if(p_front!=NULL)
	{
		p_front->next=p1; //修改前一项的后继指针
	}
	else
	{
		Head=p1;
	}
	if(p_next!=NULL)
	{
		p_next->front=p1; //修改后一项的前驱指针
	}
	amount++; //信号机计数器

	flag=InputYN("是否要在其后继续添加信号机？");
	if(flag=='Y')
	{
		insert(p1,p_next);
	}
}

void removeone(struct Signal *p)
{
	if(p==NULL)
	{
		return;
	}

	if(p->next!=NULL)
	{
		p->next->front=p->front;
	} //p不是尾指针时 修改后一项的前驱指针

	if(p->front!=NULL)
	{
		p->front->next=p->next;
	} //p不是头指针时 修改前一项的后继指针
	else
	{
		Head=p->next;
	} //p是头指针 则将后一项定为新的头指针
	amount--;
	free(p);
}

void removeall()
{
	struct Signal *p;
	while(Head!=NULL)
	{
		p=Head->next;
		free(Head);
		amount--;
		Head=p;
	}
}