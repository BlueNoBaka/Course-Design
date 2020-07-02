#ifndef _InfoEdit_H_
	#define _InfoEdit_H_

	void insert(struct Signal *, struct Signal *); //在相邻信号机间插入一台新信号机
	void removeone(struct Signal *); //删除一条指定的信号机数据
	void removeall(); //删除所有信号机数据

#endif