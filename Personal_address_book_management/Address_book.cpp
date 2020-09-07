//תרҵ
//17052106
//������
//2018/12/14
//C++�γ����
//����ͨѶ¼����
//Windows 10/Visual Studio 2017�±�������ͨ��

#include "pch.h"
#include "Address_book.h"
#include "Interface.h"


enum { IGNORE_WIDTH = 1024 };


std::list<Info>::iterator Address_book::Find_Info(const std::string & keyword)
{//������������
	std::list<Info>::iterator iter = m_Ab.begin();
	for (; iter != m_Ab.end(); iter++)
		if (iter->m_name.find(keyword) < iter->m_name.length())//������������������ͬ
			return iter;
	return iter;
}

void Address_book::Out_line(const std::list<Info>::const_iterator Info_iter)const
{//���һ�˵�����
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
{//���ȫ������
	using namespace std;
	for (
		list<Info>::const_iterator Info_iter = m_Ab.begin();
		Info_iter != m_Ab.end();
		Info_iter++
		)
		Out_line(Info_iter);
}

void Address_book::Out(std::ofstream & outfile)const
{//���ļ����ȫ������
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
		outfile << "\t\\" << endl;//ʹ��'\\'��Ϊһ�����ݵĽ�����־��
	}
}

int Address_book::Read()
{//���ļ��ж�ȡȫ������
	using namespace std;

	ifstream infile(m_fname, ios::in);
	if (!infile)
	{
		cerr << "Read���ļ�����" << endl;
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
			if (0 == num.find('\\') && num.length() == 1)//��'\\'�˳�ѭ��
				break;
			inf.m_phnums.push_back(num);
		}
		if (inf.m_name.length() != 0)//���������Ϊ��
			m_Ab.push_back(inf);
	}
	infile.close();
	m_changed = false;//δ��������
	return 1;
}

int	Address_book::Exit()
{//ѯ���Ƿ񱣴沢�˳�
	using namespace std;
	while (true)
	{
		char choice = 0;

		const string title = "�˳���Ŀ���Ƿ񱣴�˴θ��ģ�";//�����������
		const int ch_num = 2;
		const string choice_list[ch_num] =
		{
			"y:��",
			"n:��"
		};
		Interface(title, ch_num, choice_list);				//ʹ�ý�������

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
			cout << "����ѡ����󣡷���ѡ����档" << endl;
			break;
		}
		Continue();
	}
}

int Address_book::Find()
{//���ұ༭����
	using namespace std;

	string keyword;
	cout << "������Ҫ���ҵ����֣������ֵ�һ���֣���";
	cin >> keyword;
	const list<Info>::iterator fresult = Find_Info(keyword);//������ҽ������ӦԪ�ص�������
	if (m_Ab.end() == fresult)//������Խ��
	{
		cout << "δ�ҵ�����ϵ�ˣ�" << endl;
		return 0;
	}

	while (true)
	{
		char choice = 0;

		const string title = "�༭";			//�����������
		const int ch_num = 7;
		string choice_list[ch_num] =
		{
			"n:��������",
			"a:��ӵ绰����",
			"c:ɾ�������µ�ȫ���绰����",
			"d:ɾ������ϵ��",
			"p:ɾ��ָ���绰����",
			"e:�˳����ұ༭"
		};
		if (fresult->m_phnums.size() <= 1)//����ʾ��ĳЩ�����²�Ӧʹ�õĹ���
			choice_list[4] = '\0';
		if (fresult->m_phnums.empty())
			choice_list[2] = '\0';
		Interface(title, ch_num, choice_list);	//���ý�������
		cout << setw(8) << "����" << setw(16) << "�绰����" << endl;
		Out_line(fresult);//���������Ϣ

		cin.clear();
		cin.ignore(IGNORE_WIDTH, '\n');
		cin >> choice;
		system("cls");

		if (fresult->m_phnums.size() <= 1 && 'p' == choice ||
			fresult->m_phnums.empty() && 'c' == choice)
			choice = '\0';//����ʾ��ѡ������Ϊ��������

		string str_in;//Ҫ��ӵĵ绰����
		unsigned int uint_in;//�绰�������
		list<string>::iterator num_iter = fresult->m_phnums.begin();//����ɾ�������ĵ�����

		switch (choice)
		{
		case'n':
			cout << "��������ĺ��������" << endl;
			cin >> (fresult->m_name);
			cout << "���ĳɹ���" << endl;
			m_changed = true;
			break;
		case'a':
			cout << "������Ҫ��ӵĵ绰���룺" << endl;
			cin >> str_in;
			fresult->m_phnums.push_back(str_in);
			cout << "��ӳɹ���" << endl;
			m_changed = true;
			break;
		case'c':
			cout << "ɾ���������µ�ȫ���绰����" << endl;
			fresult->m_phnums.clear();
			cout << "ɾ���ɹ���" << endl;
			m_changed = true;
			break;
		case'p':
			cout << "ɾ��һ���绰���룬������õ绰������ţ���1��ʼ����";
			cin >> uint_in;
			for (size_t i = 0; i < uint_in - 1; i++)
				num_iter++;
			fresult->m_phnums.begin();
			fresult->m_phnums.erase(num_iter);
			cout << "ɾ���ɹ���" << endl;
			m_changed = true;
			break;
		case'd':
			cout << "ɾ������ϵ��" << endl;
			m_Ab.erase(fresult);
			cout << "ɾ���ɹ���" << endl;
			m_changed = true;
			return 0;
			break;
		case'e':
			cout << "�˳�����" << endl;
			return 0;
			break;
		default:
			cout << "����ѡ����󣡷���ѡ����档" << endl;
			break;
		}
		Continue();
	}
}

int Address_book::Save()
{//����
	using namespace std;
	if (m_fname.empty())
	{
		cout << "������Ҫ���浽���ļ����������½����ļ���" << endl;
		cin >> m_fname;
	}
	ofstream outfile(m_fname, ios::out | ios::trunc);//�򿪣��������½���
	if (!outfile)
	{
		cerr << "Save���ļ�����" << endl;
		return 0;
	}
	cout << "������. . ." << endl;
	Out(outfile);
	cout << "����ɹ���" << endl;
	outfile.close();
	m_changed = false;
	return 1;
}

void Address_book::Add()
{//�����ϵ��
	using namespace std;

	Info inf;

	cout << "������Ҫ��ӵ���ϵ��������" << endl;
	cin >> inf.m_name;
	cout << "��������ϵ�˵ĵ绰���루�����Ƕ��,����հ׷�������\\��ֹ����" << endl;
	string num;
	while (true)
	{
		cin >> num;
		if (0 == num.find('\\') && num.length() == 1)
			break;
		inf.m_phnums.push_back(num);
	}
	m_Ab.push_back(inf);
	cout << "��ӳɹ���" << endl;
	m_changed = true;
}

void Address_book::Continue()const
{//���ܽ���ʱ�ȴ�����
	using namespace std;
	cout << "�밴���������. . .";
	cin.clear();
	cin.ignore(IGNORE_WIDTH, '\n');
	cin.get();
	system("cls");
	cin.putback('\n');
}

int Address_book::SpliceAb()
{//�ϲ������ļ�
	using namespace std;
	string spliced_fname;//���ϲ����ļ�
	cout << "���ļ�1�ϲ����ļ�0�������ļ�1��" << endl;
	cout << "�ļ�1��";//���ϲ����ļ�
	cin >> spliced_fname;
	cout << "�ļ�0��";//�ϲ�����ļ�
	cin >> m_fname;
	Address_book spliced_Ab(spliced_fname);//Ϊ���ϲ����ļ�����һ��ͨѶ¼����
	ofstream outfile(m_fname, ios::app);//��׷�ӷ�ʽ�򿪺ϲ�����ļ�
	if (!outfile)
	{
		cerr << "SpliceAb���ļ�����" << endl;
		return 0;
	}
	spliced_Ab.Out(outfile);//���ļ�1������д���ļ�0����
	cout << "�ϲ��ɹ���";
	outfile.close();
	return 1;
}

int Address_book::OpenAb()
{//��һ����Ŀ
	using namespace std;

	cout << "�������ļ����������ļ�����" << endl;
	cin >> m_fname;

	if (!Read())//����ȡʧ��
		return 0;
	cout << "�򿪳ɹ���" << endl;
	Continue();
	SelectFuction();//����ѡ���ܽ���
	return 1;
}

int Address_book::SelectFuction()
{//ѡ���ܽ���
	using namespace std;
	while (true)
	{
		char choice = 0;

		const string title = m_fname.empty() ? "�½���Ŀ" : "��Ŀ" + m_fname;	//�����������
		const int ch_num = 7;
		string choice_list[ch_num] =
		{
		"r:���򣨰���ϵ�����ֱ��룩",
		"c:���ȫ������",
		"a:�����ϵ��",
		"s:����",
		"f:���ұ༭",
		"o:���ȫ��",
		"e:�˳���Ŀ"
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
		Interface(title, ch_num, choice_list);									//���뽻������

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
		case'r'://���򣨰���ϵ�����ֱ��룩
			m_Ab.sort();
			cout << "����ɹ���" << endl;
			m_changed = true;
			break;
		case'c'://���ȫ������
			m_Ab.clear();
			cout << "����ɹ���" << endl;
			m_changed = true;
			break;
		case'a'://�����ϵ��
			Add();
			break;
		case's'://����
			Save();
			break;
		case'f'://���ұ༭
			Find();
			break;
		case'o'://���ȫ��
			cout << setw(8) << "����" << setw(16) << "�绰����" << endl;
			Out();
			break;
		case'e'://�˳���Ŀ
			if (m_changed)
				Exit();
			m_Ab.clear();
			return 0;
			break;
		default:
			cout << "����ѡ����󣡷���ѡ����档" << endl;
			break;
		}
		Continue();
	}
}

int Address_book::Run()
{//���е�������
	using namespace std;
	cin.putback('\n');//��cin��Ԥдһ��'\n'��ȷ����ջ�����ʱ����ͳһ
	while (true)
	{
		char choice = 0;

		const string title = "ͨѶ¼";			//�����������
		const int ch_num = 4;
		const string choice_list[ch_num] =
		{
			"n:�½�ͨѶ¼",
			"o:��������Ŀ",
			"s:�ϲ�������Ŀ",
			"e:�˳�����"
		};
		Interface(title, ch_num, choice_list);	//���ý�������
			
		cin.clear();
		cin.ignore(IGNORE_WIDTH, '\n');
		cin >> choice;

		system("cls");
		switch (choice)
		{
		case'n'://�½�ͨѶ¼
			m_changed = false;
			m_fname.clear();
			m_Ab.clear();
			SelectFuction();
			break;
		case'o'://��������Ŀ
			OpenAb();
			break;
		case's'://�ϲ�������Ŀ
			SpliceAb();
			break;
		case'e'://�˳�����
			return 0;
			break;
		default:
			cout << "����ѡ����󣡷���ѡ����档" << endl;
			break;
		}
		Continue();
	}
}