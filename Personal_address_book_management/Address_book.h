//转专业
//17052106
//张润生
//2018/12/14
//C++课程设计
//个人通讯录管理
//Windows 10/Visual Studio 2017下编译运行通过

#pragma once

class Info;//提前声明类Info

class Address_book//使用的通讯录类
{
protected:
	bool m_changed;//上一次保存或读取后是否进行过更改
	std::string m_fname;//对应文件名
	std::list<Info> m_Ab;//通讯录内容
public:
	Address_book() : m_changed(false) {};
	Address_book(const std::string & fname) :m_changed(false), m_fname(fname)
	{
		Read();
	}

	std::list<Info>::iterator Find_Info(const std::string &);//遍历查找名字

	void	Out_line(std::list<Info>::const_iterator)const;//输出一人的数据
	void	Out()const;//输出全部数据
	void	Out(std::ofstream &)const;//向文件输出全部数据
	int		Read();//从文件中读取全部数据
	int		Exit();//询问是否保存并退出
	int		Find();//查找编辑界面
	int		Save();//保存
	void	Add();//添加联系人

	void	Continue()const;//功能结束时等待界面
	int		SpliceAb();//合并两个文件
	int		OpenAb();//打开一个项目
	int		SelectFuction();//选择功能界面
	int		Run();//运行的主界面
};

class Info
{
protected:
	std::string m_name;//联系人名字
	std::list<std::string> m_phnums;//联系人电话列表
public:
	friend std::list<Info>::iterator Address_book::Find_Info(const std::string &);
	friend	void	Address_book::Out_line(std::list<Info>::const_iterator)const;
	friend	void	Address_book::Out()const;
	friend	void	Address_book::Out(std::ofstream &)const;
	friend	int		Address_book::Read();
	friend	int		Address_book::Find();
	friend	void	Address_book::Add();

	bool operator< (const Info & i)const//重载<，用于调用std::list::sort()排序时的比较
	{
		return this->m_name < i.m_name;
	}
};