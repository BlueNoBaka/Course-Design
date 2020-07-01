#ifndef _Info_Query_H_
	#define _Info_Query_H_

	struct Signal *Query_name_Accurate(char *); //根据准确的信号机名称查找信号机信息
	void Query_name_Fuzzy(char *); //查找所有名称中包含关键词的信号机 输出所有结果
	void showone(struct Signal *p); //输出一台信号机的信息
	void showall(); //输出所有信号机的信息

#endif
