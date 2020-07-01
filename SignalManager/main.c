#include <stdlib.h>
#include "RSignal.h"

void MainMenu();

int amount; //记录信号机数量
struct Signal *Head; //链表头指针

int main(void)
{
	system("title 信号机管理系统"); //修改程序窗口标题
	MainMenu(); //主菜单
	return 0;
}
