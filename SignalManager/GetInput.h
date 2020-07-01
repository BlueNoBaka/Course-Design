#ifndef _GetInput_H_
	#define _GetInput_H_

	char InputOption(char L, char R); //输入选项，获取一个在给定L、R之间的字符
	char InputYN(char *warning); //输出给定提示，要求输入Y或N
	void InputElement(struct Signal *p,int opt); //用于修改指定信号机的某一项信息 opt为5时输入所有信息

#endif