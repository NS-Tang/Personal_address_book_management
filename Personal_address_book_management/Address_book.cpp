//转专业
//17052106
//张润生
//2018/12/14
//C++课程设计
//个人通讯录管理
//Windows 10/Visual Studio 2017下编译运行通过

#include "pch.h"
#include "Address_book.h"
#include "Interface.h"


enum { IGNORE_WIDTH = 1024 };


std::list<Info>::iterator Address_book::Find_Info(const std::string & keyword)
{//遍历查找名字
	std::list<Info>::iterator iter = m_Ab.begin();
	for (; iter != m_Ab.end(); iter++)
		if (iter->m_name.find(keyword) < iter->m_name.length())//如果名字与参数部分相同
			return iter;
	return iter;
}

void Address_book::Out_line(const std::list<Info>::const_iterator Info_iter)const
{//输出一人的数据
	using namespace std;
	cout << setw(8) << Info_iter->m_name;
	for (
		list<string>::const_iterator str_iter = Info_iter->m_phnums.begin();
		str_iter != Info_iter->m_phnums.end();
		str_iter++
		)
		cout << setw(16) << *str_iter;
	cout << endl;
}

void Address_book::Out() const
{//输出全部数据
	using namespace std;
	for (
		list<Info>::const_iterator Info_iter = m_Ab.begin();
		Info_iter != m_Ab.end();
		Info_iter++
		)
		Out_line(Info_iter);
}

void Address_book::Out(std::ofstream & outfile)const
{//向文件输出全部数据
	using namespace std;
	for (
		list<Info>::const_iterator Info_iter = m_Ab.begin();
		Info_iter != m_Ab.end();
		Info_iter++
		)
	{
		outfile << setw(8) << Info_iter->m_name;
		for (
			list<string>::const_iterator str_iter = Info_iter->m_phnums.begin();
			str_iter != Info_iter->m_phnums.end();
			str_iter++
			)
		{
			outfile << setw(16) << *str_iter;
		}
		outfile << "\t\\" << endl;//使用'\\'作为一人数据的结束标志。
	}
}

int Address_book::Read()
{//从文件中读取全部数据
	using namespace std;

	ifstream infile(m_fname, ios::in);
	if (!infile)
	{
		cerr << "Read打开文件错误！" << endl;
		return 0;
	}
	while (!infile.eof())
	{
		Info inf;
		infile >> inf.m_name;
		while (!infile.eof())
		{
			string num;
			infile >> num;
			if (0 == num.find('\\') && num.length() == 1)//遇'\\'退出循环
				break;
			inf.m_phnums.push_back(num);
		}
		if (inf.m_name.length() != 0)//如果姓名不为空
			m_Ab.push_back(inf);
	}
	infile.close();
	m_changed = false;//未发生更改
	return 1;
}

int	Address_book::Exit()
{//询问是否保存并退出
	using namespace std;
	while (true)
	{
		char choice = 0;

		const string title = "退出项目，是否保存此次更改？";//交互界面参数
		const int ch_num = 2;
		const string choice_list[ch_num] =
		{
			"y:是",
			"n:否"
		};
		Interface(title, ch_num, choice_list);				//使用交互界面

		cin.clear();
		cin.ignore(IGNORE_WIDTH, '\n');
		cin >> choice;

		system("cls");
		switch (choice)
		{
		case'y':
			Save();
			m_fname.clear();
			m_Ab.clear();
			return 0;
			break;
		case'n':
			m_fname.clear();
			m_Ab.clear();
			return 0;
			break;
		default:
			cout << "输入选择错误！返回选择界面。" << endl;
			break;
		}
		Continue();
	}
}

int Address_book::Find()
{//查找编辑界面
	using namespace std;

	string keyword;
	cout << "请输入要查找的名字（或名字的一部分）：";
	cin >> keyword;
	const list<Info>::iterator fresult = Find_Info(keyword);//保存查找结果（对应元素迭代器）
	if (m_Ab.end() == fresult)//迭代器越界
	{
		cout << "未找到该联系人！" << endl;
		return 0;
	}

	while (true)
	{
		char choice = 0;

		const string title = "编辑";			//交互界面参数
		const int ch_num = 7;
		string choice_list[ch_num] =
		{
			"n:更改姓名",
			"a:添加电话号码",
			"c:删除该名下的全部电话号码",
			"d:删除此联系人",
			"p:删除指定电话号码",
			"e:退出查找编辑"
		};
		if (fresult->m_phnums.size() <= 1)//不显示在某些条件下不应使用的功能
			choice_list[4] = '\0';
		if (fresult->m_phnums.empty())
			choice_list[2] = '\0';
		Interface(title, ch_num, choice_list);	//调用交互界面
		cout << setw(8) << "姓名" << setw(16) << "电话号码" << endl;
		Out_line(fresult);//输出个人信息

		cin.clear();
		cin.ignore(IGNORE_WIDTH, '\n');
		cin >> choice;
		system("cls");

		if (fresult->m_phnums.size() <= 1 && 'p' == choice ||
			fresult->m_phnums.empty() && 'c' == choice)
			choice = '\0';//不显示的选项设置为错误输入

		string str_in;//要添加的电话号码
		unsigned int uint_in;//电话号码序号
		list<string>::iterator num_iter = fresult->m_phnums.begin();//用于删除操作的迭代器

		switch (choice)
		{
		case'n':
			cout << "请输入更改后的姓名：" << endl;
			cin >> (fresult->m_name);
			cout << "更改成功！" << endl;
			m_changed = true;
			break;
		case'a':
			cout << "请输入要添加的电话号码：" << endl;
			cin >> str_in;
			fresult->m_phnums.push_back(str_in);
			cout << "添加成功！" << endl;
			m_changed = true;
			break;
		case'c':
			cout << "删除该姓名下的全部电话号码" << endl;
			fresult->m_phnums.clear();
			cout << "删除成功！" << endl;
			m_changed = true;
			break;
		case'p':
			cout << "删除一个电话号码，请输入该电话号码序号（从1开始）：";
			cin >> uint_in;
			for (size_t i = 0; i < uint_in - 1; i++)
				num_iter++;
			fresult->m_phnums.begin();
			fresult->m_phnums.erase(num_iter);
			cout << "删除成功！" << endl;
			m_changed = true;
			break;
		case'd':
			cout << "删除此联系人" << endl;
			m_Ab.erase(fresult);
			cout << "删除成功！" << endl;
			m_changed = true;
			return 0;
			break;
		case'e':
			cout << "退出查找" << endl;
			return 0;
			break;
		default:
			cout << "输入选择错误！返回选择界面。" << endl;
			break;
		}
		Continue();
	}
}

int Address_book::Save()
{//保存
	using namespace std;
	if (m_fname.empty())
	{
		cout << "请输入要保存到的文件名，程序将新建该文件：" << endl;
		cin >> m_fname;
	}
	ofstream outfile(m_fname, ios::out | ios::trunc);//打开，若无则新建。
	if (!outfile)
	{
		cerr << "Save打开文件错误！" << endl;
		return 0;
	}
	cout << "保存中. . ." << endl;
	Out(outfile);
	cout << "保存成功！" << endl;
	outfile.close();
	m_changed = false;
	return 1;
}

void Address_book::Add()
{//添加联系人
	using namespace std;

	Info inf;

	cout << "请输入要添加的联系人姓名：" << endl;
	cin >> inf.m_name;
	cout << "请输入联系人的电话号码（可以是多个,输入空白符后输入\\截止）：" << endl;
	string num;
	while (true)
	{
		cin >> num;
		if (0 == num.find('\\') && num.length() == 1)
			break;
		inf.m_phnums.push_back(num);
	}
	m_Ab.push_back(inf);
	cout << "添加成功！" << endl;
	m_changed = true;
}

void Address_book::Continue()const
{//功能结束时等待界面
	using namespace std;
	cout << "请按任意键继续. . .";
	cin.clear();
	cin.ignore(IGNORE_WIDTH, '\n');
	cin.get();
	system("cls");
	cin.putback('\n');
}

int Address_book::SpliceAb()
{//合并两个文件
	using namespace std;
	string spliced_fname;//被合并的文件
	cout << "将文件1合并入文件0（保留文件1）" << endl;
	cout << "文件1：";//被合并的文件
	cin >> spliced_fname;
	cout << "文件0：";//合并入的文件
	cin >> m_fname;
	Address_book spliced_Ab(spliced_fname);//为被合并的文件创造一个通讯录对象
	ofstream outfile(m_fname, ios::app);//以追加方式打开合并入的文件
	if (!outfile)
	{
		cerr << "SpliceAb打开文件出错！" << endl;
		return 0;
	}
	spliced_Ab.Out(outfile);//将文件1的内容写在文件0后面
	cout << "合并成功！";
	outfile.close();
	return 1;
}

int Address_book::OpenAb()
{//打开一个项目
	using namespace std;

	cout << "打开已有文件，请输入文件名：" << endl;
	cin >> m_fname;

	if (!Read())//若读取失败
		return 0;
	cout << "打开成功！" << endl;
	Continue();
	SelectFuction();//进入选择功能界面
	return 1;
}

int Address_book::SelectFuction()
{//选择功能界面
	using namespace std;
	while (true)
	{
		char choice = 0;

		const string title = m_fname.empty() ? "新建项目" : "项目" + m_fname;	//交互界面参数
		const int ch_num = 7;
		string choice_list[ch_num] =
		{
		"r:排序（按联系人名字编码）",
		"c:清除全部数据",
		"a:添加联系人",
		"s:保存",
		"f:查找编辑",
		"o:输出全部",
		"e:退出项目"
		};

		if (m_Ab.size() <= 1)
			choice_list[0] = '\0';
		if (m_Ab.empty())
		{
			choice_list[1] = '\0';
			choice_list[4] = '\0';
			choice_list[5] = '\0';
		}
		if (!m_changed)
			choice_list[3] = '\0';
		Interface(title, ch_num, choice_list);									//进入交互界面

		cin.clear();
		cin.ignore(IGNORE_WIDTH, '\n');
		cin >> choice;
		system("cls");

		if (m_Ab.size() <= 1 && 'r' == choice ||
			m_Ab.empty() && ('c' == choice || 'f' == choice || 'o' == choice) ||
			!m_changed&&'s' == choice)
			choice = '\0';

		switch (choice)
		{
		case'r'://排序（按联系人名字编码）
			m_Ab.sort();
			cout << "排序成功！" << endl;
			m_changed = true;
			break;
		case'c'://清除全部数据
			m_Ab.clear();
			cout << "清除成功！" << endl;
			m_changed = true;
			break;
		case'a'://添加联系人
			Add();
			break;
		case's'://保存
			Save();
			break;
		case'f'://查找编辑
			Find();
			break;
		case'o'://输出全部
			cout << setw(8) << "姓名" << setw(16) << "电话号码" << endl;
			Out();
			break;
		case'e'://退出项目
			if (m_changed)
				Exit();
			m_Ab.clear();
			return 0;
			break;
		default:
			cout << "输入选择错误！返回选择界面。" << endl;
			break;
		}
		Continue();
	}
}

int Address_book::Run()
{//运行的主界面
	using namespace std;
	cin.putback('\n');//在cin中预写一个'\n'，确保清空缓冲区时操作统一
	while (true)
	{
		char choice = 0;

		const string title = "通讯录";			//交互界面参数
		const int ch_num = 4;
		const string choice_list[ch_num] =
		{
			"n:新建通讯录",
			"o:打开已有项目",
			"s:合并已有项目",
			"e:退出程序"
		};
		Interface(title, ch_num, choice_list);	//调用交互界面
			
		cin.clear();
		cin.ignore(IGNORE_WIDTH, '\n');
		cin >> choice;

		system("cls");
		switch (choice)
		{
		case'n'://新建通讯录
			m_changed = false;
			m_fname.clear();
			m_Ab.clear();
			SelectFuction();
			break;
		case'o'://打开已有项目
			OpenAb();
			break;
		case's'://合并已有项目
			SpliceAb();
			break;
		case'e'://退出程序
			return 0;
			break;
		default:
			cout << "输入选择错误！返回选择界面。" << endl;
			break;
		}
		Continue();
	}
}