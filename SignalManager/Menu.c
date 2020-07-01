#include <stdio.h>
#include <stdlib.h>
#include "RSignal.h"
#include "InfoEdit.h"
#include "InfoQuery.h"
#include "GetInput.h"

extern int amount;
extern struct Signal *Head;

void MenuTitle(char *);
void MainMenu_1();
void MainMenu_2();
void MainMenu_3();
struct Signal *SelectFromList();
void EditMenu(struct Signal *);

void MenuTitle(char *title)
{
	system("cls");
	printf("==========信号机管理系统==========\n");
	printf("当前信号机数量：%d\n\n",amount);
	printf("【%s】\n",title); //在【】内显示当前菜单的名称
}

void MainMenu()
{
	char option; //存储用户选择
	int flag=1; //为0时退出主菜单 程序结束

	while(flag)
	{
		MenuTitle("主菜单");
		printf("1.信号机生成登记\n");
		printf("2.信号机信息修改\n");
		printf("3.信号机信息查询\n");
		printf("0.保存信号机信息并退出\n");

		option=InputOption('0','3');
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
				system("pause");
				flag=0;
			}
			break;
		}
	}
}



void MainMenu_1()
{
	char option;
	if(amount>0)
	{
		option=InputYN("该操作会清除原有的信号机数据，你确定要继续吗？");
		if(option=='N')
		{
			return; //返回主菜单
		}
		else if(option=='Y')
		{
			removeall(); //清除原有数据
		}
	} //已有信号机数据时进行提示

	MenuTitle("信号机生成登记");
	printf("1.从文件中导入\n");
	printf("2.人工录入\n");

	option=InputOption('1','2');
	switch(option)
	{
	case '1':
		load();
		break;
	case '2':
		create();
		break;
	}
}

void MainMenu_2()
{
	char option;
	struct Signal *target; //存储选中信号机的指针
	if(amount==0)
	{
		printf("当前信号机数量为0，请先录入信号机数据！\n");
		system("pause");
		return;
	}

	MenuTitle("信号机信息修改");
	printf("1.增加信号机\n");
	printf("2.编辑信号机信息\n");
	printf("3.删除一台信号机\n");
	printf("4.删除所有信号机\n");
	printf("0.返回主菜单\n");

	option=InputOption('0','4');
	switch(option)
	{
	case '1':
		printf("选择与目标插入位置相邻的信号机\n");
		system("pause");
		target=SelectFromList();
		if(target==NULL)
		{
			return;
		}
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
		printf("选择需要编辑的信号机\n");
		system("pause");
		target=SelectFromList();
		if(target==NULL)
		{
			return;
		}
		EditMenu(target); //编辑菜单
		break;
	case '3':
		printf("选择需要删除的信号机\n");
		system("pause");
		target=SelectFromList();
		removeone(target);
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
	struct Signal *result; //存储精确查找的返回值
	if(amount==0)
	{
		printf("当前信号机数量为0，请先录入信号机数据！\n");
		system("pause");
		return;
	}

	MenuTitle("信息查询");
	printf("1.根据信号机名称精确查找\n");
	printf("2.根据信号机名称模糊查找\n");
	printf("3.查看所有信号机的信息\n");
	printf("0.返回主菜单\n");

	option=InputOption('0','3');
	switch(option)
	{
	case '1':
		printf("【精确查找】输入信号机名称：");
		scanf("%9s",key);
		while(getchar()!= '\n');
		result=Query_name_Accurate(key);
		if(result==NULL)
		{
			printf("未找到该信号机！\n");
			system("pause");
			break;
		}
		showone(result);
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
		showall(); //显示所有信号机数据
		system("pause");
		break;
	case '0':
		break;
	}
}

struct Signal *SelectFromList()
{
	char option; //记录用户输入的选项
	int i,count=0; //count用于记录列表所显示的最后一台信号机
	struct Signal *opt[7]; //记录列表选项对应的信号机指针
	struct Signal *p=Head;

	while(1)
	{
		for(i=0;i<7;i++)
		{
			opt[i]=NULL;
		} //初始化备选列表
		do
		{
			opt[count%7]=p;
			count++;
			if(p->next==NULL)
			{
				count--;
				break;
			} //到达最后一台信号机
			p=p->next;
		}while(count%7 && count<=amount); //载入选项对应的指针

		MenuTitle("信号机列表");
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
			break;
		case '0':
			return NULL;
		}
	}
}

void EditMenu(struct Signal *p)
{
	int flag=1;
	char option;
	while(flag)
	{
		MenuTitle("编辑选项");
		printf("1.名称\n");
		printf("2.开放状态\n");
		printf("3.位置\n");
		printf("4.性质\n");
		printf("0.编辑完成\n");
		printf("\n信号机\t开放\t位置\t性质\n");
		showone(p);
		option=InputOption('0','4');
		switch(option)
		{
		case '1':
			InputElement(p,1);
			break;
		case '2':
			InputElement(p,2);
			break;
		case '3':
			InputElement(p,3);
			break;
		case '4':
			InputElement(p,4);
			break;
		case '0':
			flag=0;
			break;
		}
	}
}
