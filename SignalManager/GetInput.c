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
	}while(temp[1]!='\0' || !(temp[0]>=L && temp[0]<=R) );
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
	}while(temp[1]!='\0' || !(temp[0]=='Y'||temp[0]=='N'));
	return temp[0];
} //输出给定提示 获取'Y'和'N'

void InputInfo(struct Signal *p)
{
	char temp[8]; //存储未判断合法性的输入数据

	printf("输入信号机名称：");
	scanf("%9s",p->Name);
	while(getchar()!= '\n');

	do
	{
		printf("输入信号机开放状态(0-闭 1-开)：");
		scanf("%7s",temp);
		while(getchar()!= '\n');
	}while(temp[1]!='\0' || !(temp[0]=='0' || temp[0]=='1') ); //输入只能为"0"或"1"
	p->KB=temp[0]-'0';

	do
	{
		printf("输入信号机位置：");
		scanf("%7s",temp);
		while(getchar()!= '\n');
	}while(!(p->Pos=atof(temp))); //输入只能为有效的数字 超过7位只取前7位(含小数点)

	do
	{
		printf("输入信号机性质(0-调车 1-列车)：");
		scanf("%7s",temp);
		while(getchar()!= '\n');
	}while(temp[1]!='\0' || (!(temp[0]=='0' || temp[0]=='1')) ); //输入只能为"0"或"1"
	p->Type=temp[0]-'0';
}