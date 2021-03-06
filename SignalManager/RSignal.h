#ifndef _RSignal_H_
	#define _RSignal_H_

	struct Signal
	{
		char Name[10]; //信号机名称
		int KB; //开放表示 0不开放 1开放
		float Pos; //位置根据平面图位置拟定
		int Type; //信号机性质，列车信号机取1,调车信号机取0
		struct Signal *next,*front; //后一架信号机指针，前一架信号机指针
	};

	void create(); //创建链表 人工录入信号机信息
	void load(); //创建链表 从文件导入信号机信息
	void save(); //导出信号机数据

#endif