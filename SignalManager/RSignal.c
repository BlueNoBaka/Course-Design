#include <stdio.h>
#include <stdlib.h>
#include "RSignal.h"
#include "GetInput.h"

extern int amount;
extern struct Signal *Head;

void create()
{
	struct Signal *p1,*p2;
	char flag; //用于判断是否继续添加信号机
	p1=p2=(struct Signal *)malloc(sizeof(struct Signal));

	InputElement(p1,5); //输入信号机信息
	
	Head=p1; //指定链表的头指针
	Head->front=NULL; //置空第一项的前驱指针
	Head->next=NULL; //置空第一项的后继指针
	amount=1;

	flag=InputYN("是否继续添加信号机？");
	while (flag=='Y')
	{
		flag='\0'; //将是否继续的flag置空
		p2=p1;
		
		p1=(struct Signal *)malloc(sizeof(struct Signal));
		InputElement(p1,5); //输入信号机信息

		p1->front=p2; //建立新一项的前驱指针
		p2->next=p1; //修改前一项的后继指针
		p1->next=NULL; //置空新一项的后继指针
		amount++;

	flag=InputYN("是否继续添加信号机？");
	}
}

void load()
{
	FILE *fp=NULL;
	fpos_t position; //用于记录目前在文件中的位置
	struct Signal *p1,*p2;

	fp=fopen("SignalData.txt","r");
	if(fp==NULL)
	{
		printf("文件不存在！\n");
		system("pause");
		return;
	}

	fgetpos(fp,&position);
	fseek(fp,0,SEEK_END);
	if(ftell(fp)==0)
	{
		printf("文件为空！\n");
		system("pause");
		return;
	}

	fsetpos(fp, &position);
	p1=p2=(struct Signal *)malloc(sizeof(struct Signal));

	fscanf(fp,"%s\t%d\t%f\t%d\n",p1->Name,&p1->KB,&p1->Pos,&p1->Type);
	Head=p1; //指定链表的头指针
	Head->front=NULL; //置空第一项的前驱指针
	Head->next=NULL; //置空第一项的后继指针
	amount=1;

	while (!feof(fp))
	{
		p2=p1;
		
		p1=(struct Signal *)malloc(sizeof(struct Signal));
		fscanf(fp,"%s\t%d\t%f\t%d\n",p1->Name,&p1->KB,&p1->Pos,&p1->Type);

		p1->front=p2; //建立新一项的前驱指针
		p2->next=p1; //修改前一项的后继指针
		p1->next=NULL; //置空新一项的后继指针
		amount++;
	}
	fclose(fp);
}