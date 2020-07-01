#include <stdio.h>
#include <stdlib.h>
#include "RSignal.h"

char InputOption(char L, char R)
{
	char temp[8]; //存储未判断合法性的输入数据
	do
	{
		printf("\n输入选项编号进行选择：");
		scanf("%7s",temp);
		while(getchar()!= '\n');
	}while(temp[1]!='\0' || !(temp[0]>=L && temp[0]<=R) ); //只允许输入一个字符(\n不计)，输入字符必须在给定的L与R之间
	return temp[0];
} //用于获取用户输入的编号

char InputYN(char *warning)
{
	char temp[8]; //存储未判断合法性的输入数据
	do
	{
		printf("%s(Y/N)",warning); //提示内容通过参数传入
		scanf("%7s",temp);
		while(getchar()!= '\n');
	}while(temp[1]!='\0' || !(temp[0]=='Y'||temp[0]=='N')); //只允许输入一个字符(\n不计)，输入字符必须为Y或N
	return temp[0];
} //输出给定提示 获取'Y'和'N'

void InputElement(struct Signal *p,int opt)
{
	char temp[8]; //存储未判断合法性的输入数据
	
	switch(opt)
	{
	case 1:
		printf("输入信号机名称：");
		scanf("%9s",p->Name);
		while(getchar()!= '\n');
		break;
	case 2:
		do
		{
			printf("输入信号机开放状态(0-闭 1-开)：");
			scanf("%7s",temp);
			while(getchar()!= '\n');
		}while(temp[1]!='\0' || !(temp[0]=='0' || temp[0]=='1') ); //输入只能为'0'或'1'
		p->KB=temp[0]-'0';
		break;
	case 3:
		do
		{
			printf("输入信号机位置：");
			scanf("%7s",temp);
			while(getchar()!= '\n');
		}while(!(p->Pos=atof(temp))); //输入只能为有效的数字 超过7位只取前7位(含小数点)
		break;
	case 4:
		do
		{
			printf("输入信号机性质(0-调车 1-列车)：");
			scanf("%7s",temp);
			while(getchar()!= '\n');
		}while(temp[1]!='\0' || (!(temp[0]=='0' || temp[0]=='1')) ); //输入只能为"0"或"1"
		p->Type=temp[0]-'0';
		break;
	case 5:
		InputElement(p,1);
		InputElement(p,2);
		InputElement(p,3);
		InputElement(p,4);
		break; //输入所有信息
	}
}