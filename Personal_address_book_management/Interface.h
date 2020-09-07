//תרҵ
//17052106
//������
//2018/12/14
//C++�γ����
//����ͨѶ¼����
//Windows 10/Visual Studio 2017�±�������ͨ��

#pragma once

#include "pch.h"

enum//��������
{
	WIDTH = 65,//���
	LEFT_BLANK = 20,//������Ŀհ׿��
	TITLE_OFFSET = 0,//����ƫ������0Ϊ���У���������
	CHOICE_TITLE_OFFSET = 32,//ѡ�����ƫ����������룩
	CHOICE_GROUP_OFFSET = 35//ѡ���б�ƫ����������룩
};

void InterfaceCentered(const int offset, const std::string &content)//���������ָ��ƫ������
{
	using namespace std;
	int right_offset = (WIDTH + content.length() + 2 * offset - 1) / 2;
	cout << setw(LEFT_BLANK) << '|' << setw(right_offset) << content << setw(WIDTH - right_offset) << '|' << endl;
}

void InterfaceLeft(const int offset, const std::string &content)//����������ָ��ƫ������
{
	using namespace std;
	cout << setw(LEFT_BLANK - 1) << ' ' << setiosflags(ios::left) << setw(offset) << '|' << setw(WIDTH - offset) << content << resetiosflags(ios::left) << '|' << endl;
}

void Interface//��������
(
	const std::string	&title,//�����������
	const unsigned int & ch_num,//ѡ������
	const std::string	*choice//ѡ���ַ�������
)
{
	using namespace std;
	cout << endl << endl;
	cout << setw(LEFT_BLANK) << '|' << setfill('*') << setw(WIDTH) << '|' << endl;
	cout.fill(' ');
	cout << setw(LEFT_BLANK) << '|' << setw(WIDTH) << '|' << endl;
	InterfaceCentered(TITLE_OFFSET, title);
	cout << setw(LEFT_BLANK) << '|' << setw(WIDTH) << '|' << endl;
	InterfaceLeft(CHOICE_TITLE_OFFSET, "ѡ��");
	for (size_t i = 0; i < ch_num; i++)
		InterfaceLeft(CHOICE_GROUP_OFFSET, choice[i]);
	cout << setw(LEFT_BLANK) << '|' << setw(WIDTH) << '|' << endl;
	InterfaceCentered(0, "Copyright(c) by ������.All rights reserved.");
	cout << setw(LEFT_BLANK) << '|' << setw(WIDTH) << '|' << endl;
	cout << setw(LEFT_BLANK) << '|' << setfill('*') << setw(WIDTH) << '|' << endl;
	cout.fill(' ');
}