#include <stdio.h>
#include <stdlib.h>
#include "RSignal.h"

void MainMenu();
void removeall();

int amount; //记录信号机数量
struct Signal *Head; //链表头指针

int main(void)
{
	system("title 信号机管理系统"); //修改程序窗口标题
	MainMenu(); //主菜单
	save();
	removeall();
	printf("信号机数据已保存至\"Signal.txt\"，即将退出程序\n");
	system("pause");
	return 0;
}
