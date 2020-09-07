//转专业
//17052106
//张润生
//2018/12/14
//C++课程设计
//个人通讯录管理
//Windows 10/Visual Studio 2017下编译运行通过

#pragma once

#include "pch.h"

enum//界面设置
{
	WIDTH = 65,//框宽
	LEFT_BLANK = 20,//左边留的空白宽度
	TITLE_OFFSET = 0,//标题偏移量（0为居中，左负右正）
	CHOICE_TITLE_OFFSET = 32,//选择标题偏移量（左对齐）
	CHOICE_GROUP_OFFSET = 35//选项列表偏移量（左对齐）
};

void InterfaceCentered(const int offset, const std::string &content)//居中输出，指定偏移量。
{
	using namespace std;
	int right_offset = (WIDTH + content.length() + 2 * offset - 1) / 2;
	cout << setw(LEFT_BLANK) << '|' << setw(right_offset) << content << setw(WIDTH - right_offset) << '|' << endl;
}

void InterfaceLeft(const int offset, const std::string &content)//左对齐输出，指定偏移量。
{
	using namespace std;
	cout << setw(LEFT_BLANK - 1) << ' ' << setiosflags(ios::left) << setw(offset) << '|' << setw(WIDTH - offset) << content << resetiosflags(ios::left) << '|' << endl;
}

void Interface//交互界面
(
	const std::string	&title,//交互界面标题
	const unsigned int & ch_num,//选项数量
	const std::string	*choice//选项字符串数组
)
{
	using namespace std;
	cout << endl << endl;
	cout << setw(LEFT_BLANK) << '|' << setfill('*') << setw(WIDTH) << '|' << endl;
	cout.fill(' ');
	cout << setw(LEFT_BLANK) << '|' << setw(WIDTH) << '|' << endl;
	InterfaceCentered(TITLE_OFFSET, title);
	cout << setw(LEFT_BLANK) << '|' << setw(WIDTH) << '|' << endl;
	InterfaceLeft(CHOICE_TITLE_OFFSET, "选择：");
	for (size_t i = 0; i < ch_num; i++)
		InterfaceLeft(CHOICE_GROUP_OFFSET, choice[i]);
	cout << setw(LEFT_BLANK) << '|' << setw(WIDTH) << '|' << endl;
	InterfaceCentered(0, "Copyright(c) by 张润生.All rights reserved.");
	cout << setw(LEFT_BLANK) << '|' << setw(WIDTH) << '|' << endl;
	cout << setw(LEFT_BLANK) << '|' << setfill('*') << setw(WIDTH) << '|' << endl;
	cout.fill(' ');
}