#include <stdio.h>
#include <string.h>
#include "RSignal.h"

void showone(struct Signal *);

extern int amount;
extern struct Signal *Head;


struct Signal *Query_name_Accurate(char key[])
{
	struct Signal *p;
	p=Head;
	do
	{
		if(!strcmp(p->Name,key))
		{
			return p;
		}
		p=p->next;
	}while(p->next!=NULL);
	return NULL;
}

void Query_name_Fuzzy(char key[])
{
	struct Signal *p;
	int count=0;
	p=Head;
	printf("信号机\t开放\t位置\t性质\n");
	do
	{
		if(strstr(p->Name,key))
		{
			showone(p);
			count++;
		}
		p=p->next;
	}while(p!=NULL);
	
	printf("查找到%d条相关信息\n",count);
}

void showone(struct Signal *p)
{
	if(p!=NULL)
	{
		printf("%s\t%1d\t%.2f\t%1d\n",p->Name,p->KB,p->Pos,p->Type); //输出可能满足条件的信号机之一

	}
}

void showall()
{
	struct Signal *p;
	printf("%d Records\n",amount);
	p=Head;
	if (Head!=NULL) //存在信号机时
	{
		printf("信号机\t开放\t位置\t性质\n");
		do
		{
			printf("%s\t%1d\t%.2f\t%1d\n",p->Name,p->KB,p->Pos,p->Type); //输出每架信号机的信息
			p=p->next;
		} while (p!=NULL);		
	}
}