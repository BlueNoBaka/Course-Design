#include <stdio.h>
#include <stdlib.h>
#include "RSignal.h"
#include "InfoEdit.h"
#include "InfoQuery.h"
#include "GetInput.h"

extern int amount;
extern struct Signal *Head;

void MainMenu_1();
void MainMenu_2();
void MainMenu_3();
struct Signal *selectfromlist();

void MainMenu()
{
	char option;
	system("cls");
	printf("==========信号机管理系统==========\n");
	printf("当前信号机数量：%d\n\n",amount);
	printf("【主菜单】\n");
	printf("1.信号机生成登记\n");
	printf("2.信号机信息修改\n");
	printf("3.信号机信息查询\n");
	printf("0.保存信号机信息并退出\n");

	option=InputOption('0','4');
	switch(option)
	{
	case '1':
		MainMenu_1();
		break;
	case '2':
		MainMenu_2();
		break;
	case '3':
		MainMenu_3();
		break;
	case '0':
		option=InputYN("保存后将自动退出程序，你确定要继续吗？");
		if(option=='Y')
		{
		save();
		removeall();
		printf("信号机数据已保存至\"SignalData.txt\"，即将退出程序\n");
		exit(0);
		}
		break;
	}
}



void MainMenu_1()
{
	char temp='\0';
	if(amount>0)
	{
		temp=InputYN("继续进行该操作将会覆盖原有的信号机数据，你确定要继续吗？");
	} //已有信号机数据时进行提示

	if(temp=='N')
	{
		return;
	}
	else if(temp=='Y')
	{
		removeall();
	}
	
	system("cls");
	printf("【信号机生成登记】\n");
	printf("1.从文件中读取\n");
	printf("2.人工录入\n");

	temp=InputOption('1','2');
	switch(temp)
	{
	case '1':
		load();
		break;
	case '2':
		create(); //信号机生成登记(信息录入)
		break;
	}
}

void MainMenu_2()
{
	char option;
	struct Signal *target;
	if(Head==NULL)
	{
		printf("当前信号机数量为0，请先录入信号机数据！\n");
		system("pause");
		return;
	}

	system("cls");
	printf("==========信号机管理系统==========\n");
	printf("当前信号机数量：%d\n\n",amount);
	printf("【信号机信息修改】\n");
	printf("1.增加信号机\n");
	printf("2.修改信号机信息\n");
	printf("3.删除一台信号机\n");
	printf("4.删除所有信号机\n");
	printf("0.返回上级菜单\n");

	option=InputOption('0','4');
	switch(option)
	{
	case '1':
		printf("请选择与目标插入位置相邻的信号机\n");
		system("pause");
		target=selectfromlist();
		printf("1.插入在所选信号机前\n");
		printf("2.插入在所选信号机后\n");
		option=InputOption('1','2');
		switch(option)
		{
		case '1':
			insert(target->front,target);
			break;
		case '2':
			insert(target,target->next);
			break;
		}
		break;
	case '2':
		target=selectfromlist();
		printf("请输入修改后的信息：\n");
		InputInfo(target);
		system("pause");
		break;
	case '3':
		target=selectfromlist();
		removeone(target);
		system("pause");
		break;
	case '4':
		option=InputYN("进行该操作将会清空原有的信号机数据，你确定要继续吗？");
		if(option=='Y')
		{
			removeall();
			printf("已删除所有信号机\n");
			system("pause");
		}
		break;
	case '0':
		break;
	}
}

void MainMenu_3()
{
	char option;
	char key[10]; //存储搜索关键词
	if(Head==NULL)
	{
		printf("当前信号机数量为0，请先录入信号机数据！\n");
		system("pause");
	}
	else
	{
		system("cls");
		printf("==========信号机管理系统==========\n");
		printf("当前信号机数量：%d\n\n",amount);
		printf("【信息查询】\n");
		printf("1.根据信号机名称精确查找\n");
		printf("2.根据信号机名称模糊查找\n");
		printf("3.查看所有信号机的信息\n");
		printf("0.返回上级菜单\n");

		option=InputOption('0','3');
		switch(option)
		{
		case '1':
			printf("【精确查找】输入信号机名称：");
			scanf("%9s",key);
			while(getchar()!= '\n');
			showone(Query_name_Accurate(key));
			system("pause");
			break;
		case '2':
			printf("【模糊查找】输入查找关键字：");
			scanf("%9s",key);
			while(getchar()!= '\n');
			Query_name_Fuzzy(key);
			system("pause");
			break;
		case '3':
			showall(); //显示信号机数据
			system("pause");
			break;
		case '0':
			break;
		}
	}
}

struct Signal *selectfromlist()
{
	char option;
	int i,count=0;
	struct Signal *opt[7];
	struct Signal *p=Head;
	
	while(1)
	{
		for(i=0;i<7;i++)
		{
			opt[i]=NULL;
		}
		do
		{
			opt[count%7]=p;
			count++;
			if(p->next==NULL)
			{
				count--;
				break;
			}
			p=p->next;
		}while(count%7 && count<=amount);

		system("cls");
		printf("==========信号机管理系统==========\n");
		printf("当前信号机数量：%d\n\n",amount);
		printf("【信号机列表】\n");
		printf("选项\t信号机\t开放\t位置\t性质\n");
		for(i=0;i<7;i++)
		{
			if(opt[i]!=NULL)
			{
				printf("%d.\t",i+1);
				showone(opt[i]);
			}
		}
		printf("\n8.上一页\n");
		printf("9.下一页\n");
		printf("0.返回主菜单\n");

		option=InputOption('0','9');
		if(option>='1' && option<='7')
		{
			return(opt[option-'1']);
		}
		switch(option)
		{
		case '8':
				if(count<=7)
				{
					count=0;
					p=Head;
					printf("已到达首页！\n");
					system("pause");
					break;
				}
				do
				{
					p=p->front;
					count--;
				}while(count%7);
				for(i=0;i<7;i++)
				{
					p=p->front;
					count--;
				}
			break;
		case '9':
			if(count==amount-1)
			{
				while(count%7)
				{
					p=p->front;
					count--;
				}
				printf("已到达末页！\n");
				system("pause");
				break;
			}
			//下一页
			break;
		case '0':
			return NULL;
		}
	}
}
