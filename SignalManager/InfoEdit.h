#ifndef _InfoEdit_H_
	#define _InfoEdit_H_

	void insert(struct Signal *, struct Signal *);
	void removeone(struct Signal *);
	void removeall(); //释放内存 删除所有信号机数据
	void save();

#endif