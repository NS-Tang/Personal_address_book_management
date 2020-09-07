//תרҵ
//17052106
//������
//2018/12/14
//C++�γ����
//����ͨѶ¼����
//Windows 10/Visual Studio 2017�±�������ͨ��

#pragma once

class Info;//��ǰ������Info

class Address_book//ʹ�õ�ͨѶ¼��
{
protected:
	bool m_changed;//��һ�α�����ȡ���Ƿ���й�����
	std::string m_fname;//��Ӧ�ļ���
	std::list<Info> m_Ab;//ͨѶ¼����
public:
	Address_book() : m_changed(false) {};
	Address_book(const std::string & fname) :m_changed(false), m_fname(fname)
	{
		Read();
	}

	std::list<Info>::iterator Find_Info(const std::string &);//������������

	void	Out_line(std::list<Info>::const_iterator)const;//���һ�˵�����
	void	Out()const;//���ȫ������
	void	Out(std::ofstream &)const;//���ļ����ȫ������
	int		Read();//���ļ��ж�ȡȫ������
	int		Exit();//ѯ���Ƿ񱣴沢�˳�
	int		Find();//���ұ༭����
	int		Save();//����
	void	Add();//�����ϵ��

	void	Continue()const;//���ܽ���ʱ�ȴ�����
	int		SpliceAb();//�ϲ������ļ�
	int		OpenAb();//��һ����Ŀ
	int		SelectFuction();//ѡ���ܽ���
	int		Run();//���е�������
};

class Info
{
protected:
	std::string m_name;//��ϵ������
	std::list<std::string> m_phnums;//��ϵ�˵绰�б�
public:
	friend std::list<Info>::iterator Address_book::Find_Info(const std::string &);
	friend	void	Address_book::Out_line(std::list<Info>::const_iterator)const;
	friend	void	Address_book::Out()const;
	friend	void	Address_book::Out(std::ofstream &)const;
	friend	int		Address_book::Read();
	friend	int		Address_book::Find();
	friend	void	Address_book::Add();

	bool operator< (const Info & i)const//����<�����ڵ���std::list::sort()����ʱ�ıȽ�
	{
		return this->m_name < i.m_name;
	}
};