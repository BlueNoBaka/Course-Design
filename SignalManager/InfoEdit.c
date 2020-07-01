#include <stdio.h>
#include <stdlib.h>
#include "RSignal.h"
#include "InfoQuery.h"

extern int amount;
extern struct Signal *Head;

void InputInfo(struct Signal *);

void insert(struct Signal *p_front, struct Signal *p_next)
{
	struct Signal *p1;
	char flag;

	p1=(struct Signal *)malloc(sizeof(struct Signal));
	InputInfo(p1); //输入信号机信息

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

	while(!(flag=='Y'||flag=='N'))
	{
		printf("是否要在%s后继续添加信号机？(Y/N)",p1->Name);
		flag=getchar();
		while(getchar()!='\n');
	}
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
	}
	if(p->front!=NULL)
	{
		p->front->next=p->next;
	}
	else
	{
		Head=p->next;
	}
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

void save()
{
	FILE *fp=NULL;
	struct Signal *p;
	
	fp=fopen("SignalData.txt","w");
	p=Head;
	if (Head!=NULL) //存在信号机时
	{
		do
		{
			fprintf(fp,"%s\t%1d\t%.2f\t%1d\n",p->Name,p->KB,p->Pos,p->Type); //输出每架信号机的信息
			p=p->next;
		} while (p!=NULL);
	}
	fclose(fp);
}