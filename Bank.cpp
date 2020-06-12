#include "Bank.h"
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <string>
using namespace std;

int YH::useracnum = 0;

consumer::consumer(double m, int id, const string Name, const string PassWord)
{
	ID = id;
	name = Name;
	money = m;
	passwd = PassWord;
}

consumer::consumer()
{
	ID = 0;
	name = '0';
	money = 0;
	passwd = '0';
}

void consumer::setid(int id)
{
	ID = id;
}

void consumer::setmoney(double m)
{
	money = m;
}

void consumer::setname(string nam)
{
	name = nam;
}

void consumer::setpassword(string passw)
{
	passwd = passw;
}

int consumer::get_id() const
{
	return ID;
}

double consumer::get_money() const
{
	return money;
}

string consumer::get_name() const
{
	return name;
}

string consumer::get_passwd() const
{
	return passwd;
}

void consumer::display()
{
	system("cls");
	cout << "**********************************" << endl;
	cout << "* 用户姓名：" << name << endl;
	cout << "* 帐号： " << ID << endl;
	cout << "* 余额: " << money << endl;
	cout << "**********************************" << endl;
}

/*存钱*/
void consumer::savemoney()
{
	double smoney;
	int judge = 1;
	while (judge)
	{
		cout << "请输入存款金额: ";
		cin >> smoney;
		while (smoney <= 0)
		{
			cout << "请输入大于零的金额！！！" << endl;
			cout << "请输入存款金额：" << endl;
			cin >> smoney;
		}
		money += smoney;
		cout << "存款成功！！！" << endl;
		cout << "是否需要继续存款：\n 是：1或其他数字；否：0" << endl;
		cin >> judge;
	}
}

/*取钱*/
void consumer::fetchmoney()
{
	if (money <= 0)
	{
		cout << "你的账户余额小于等于0！！请先充值！！" << endl;
		return;
	}
	double fmoney;
	int judge = 1;
	while (judge)
	{
		cout << "请输入要取出的金额：";
		cin >> fmoney;
		while (fmoney <= 0)
		{
			cout << "请输入大于零的金额！！！" << endl;
			cout << "请输入存款金额：" << endl;
			cin >> fmoney;
		}
		if (money - fmoney < 0)
		{
			cout << "对不起，您的账户余额不足！！！" << endl;
		}
		else
		{
			money -= fmoney;
			cout << "取款成功！！！" << endl;
			cout << "是否需要继续取款：是：1或者其他数字；否：0" << endl;
			cin >> judge;
		}
	}
}

void consumer::changemoney(double changemoney)
{
	money += changemoney;
}

YH::YH()
{
}

/*转账*/
void YH::transfer(int x)
{
	int id;
	cout << "请输入帐号:";
	cin >> id;
	int flag = 1;
	int i = 0;
	while ((i < useracnum) && (flag)) //循环查找
	{
		if (id == useraccount[i]->get_id())
			flag = 0;
		else
			i++;
	}
	if (flag)
	{
		cout << "帐号不存在!" << endl
			 << endl;
		return;
	}
	double b;

	cout << endl
		 << "请输入你要转帐的金额:";
	cin >> b;
	while (b <= 0)
	{
		cout << "请输入正确的数字!" << endl;
		cout << "——";
		cin >> b;
	}
	if (useraccount[x]->get_money() < b)
		cout << "对不起,金额不够!!" << endl;
	else
	{
		useraccount[x]->changemoney(-b);
		useraccount[i]->changemoney(b);
		cout << "转帐成功!";
	}
	return;
}

/*储户开户*/
void YH::set_account()
{
	system("cls");
	int id;
	string nam;
	string passw;
	double m;

	cout << endl
		 << "请输入开户号：";
	cin >> id;
	while (id < 100000 || id >= 1000000)
	{
		cout << endl
			 << "请输入6位数字!" << endl;
		cin >> id;
	}
	cout << endl
		 << "请输入开户人姓名：" << endl;
	cin >> nam;
	cout << endl
		 << "请输入开户密码：" << endl;
	cin >> passw;
	cout << endl
		 << "请输入存入金额:" << endl;
	cin >> m;
	while (m <= 0)
	{
		cout << "请输入正确的数字!" << endl
			 << endl;
		cin >> m;
	}
	consumer *acc = new consumer(m, id, nam, passw);
	useraccount[useracnum] = acc;
	cout << "开户成功!!" << endl
		 << endl;
	useracnum++;
	saveuser();
	cin.get();
	return;
}

/*用户文件输出*/
void YH::saveuser()
{
	ofstream ofile("bankdat.dat", ios::out);   //以输出方式打开文件
	ofstream outfile("bankdat.dat", ios::out); //以输出方式打开银行存款文件bankdat.data接收从内存输出的数据
	int n = 0;
	outfile << useracnum << "  ";
	for (; n < useracnum; n++)
	{
		outfile << useraccount[n]->ID << " "; //将信息写入bankdat.data文件
		outfile << useraccount[n]->money << " ";
		outfile << useraccount[n]->name << " ";
		outfile << useraccount[n]->passwd << " ";
	}
	outfile.close(); //关闭文件
}

/*用户账户登录*/
void YH::enter_account()
{
	system("cls");
	int id;
	cout << "请输入帐号:";
	cin >> id;
	int flag = 1;
	int i = 0;
	while ((i < useracnum) && (flag)) //循环查找账户
	{
		if (id == useraccount[i]->get_id())
			flag = 0;
		else
			i++;
	}
	if (flag)
	{
		cout << "帐号不存在!" << endl
			 << endl;
		cin.get();
		return;
	}
	cout << "请输入密码:";
	string passw;
	cin >> passw;
	if (passw != useraccount[i]->get_passwd()) //密码错误返回操作
	{
		cout << "密码错误!" << endl
			 << endl;
		cin.get();
		return;
	}
	useraccount[i]->display();
	cin.get();
	cin.get();
	int n;
	do
	{
		system("cls");
		cout << "请选择你要进行的操作:" << endl;
		cout << "————————————————————————" << endl;
		cout << "\t1)查看信息" << endl
			 << "\t2)取款" << endl
			 << "\t3)存款" << endl
			 << "\t4)转账" << endl
			 << "\t5)返回" << endl;
		cout << "————————————————————————" << endl;

		cin >> n;
		switch (n)
		{
		case 1:
			useraccount[i]->display();
			break;
		case 2:
			useraccount[i]->fetchmoney();
			saveuser();
			break; //每执行调用一次save函数 重新写一次数据
		case 3:
			useraccount[i]->savemoney();
			saveuser();
			break;
		case 4:
			transfer(i);
			saveuser();
			break;
		case 5:
			return;
		}
		cin.get();
		cin.get();
	} while (1);
}

/*读取用户信息功能实现*/
void YH::loaduser()
{
	ifstream infile("bankdat.dat", ios::in); //以输入方式打开文件
	if (!infile)
	{
		cerr << "读取错误,无资料中!" << endl;
		return;
	}
	int n = 0;
	int id;
	double m;
	string nam, passw;
	infile >> useracnum;
	for (; n < useracnum; n++) //全部读入
	{
		infile >> id; //从文件中读入信息
		infile >> m;
		infile >> nam;
		infile >> passw;
		useraccount[n]->passwd;
		consumer *acc = new consumer(m, id, nam, passw); //每读入一个n开辟一段内存
		useraccount[n] = acc;							 //赋值首地址
	}
	infile.close();
	cout << "读取资料正常!" << endl;
}

/*主菜单1*/
void YH::functionshow1()
{
	int n;
	do
	{
		system("cls"); //清屏
		loaduser();
		cout << endl
			 << "请你输入相应的操作序号进行操作:" << endl;
		cout << endl
			 << "============================================================" << endl;
		cout << "1) 用户开户" << endl
			 << "2) 账户登陆" << endl
			 << "3) 查询" << endl
			 << "4) 退出系统 " << endl;
		cout << endl
			 << "============================================================" << endl;
		cout << "请操作选择";
		cin >> n;
		cout << "************************************************************" << endl;
		while (n < 1 || n > 4)
		{
			cout << "请输入正确的操作序号!" << endl;
			cin >> n;
		}
		switch (n)
		{
		case 1:
			set_account(); //开户
			break;
		case 2:
			enter_account(); //登陆
			break;
		case 3:
			qu_account(); //查询
			break;
		case 4:
			exitYH(); //退出
			break;
		}
		cin.get();
	} while (true);
}

/*查询用户*/
void YH::qu_account()
{
	system("cls");
	int n = 0;
	cout << "账号              金额               姓名               密码" << endl;
	cout << "______________________________________________________________________" << endl;
	for (; n < useracnum; n++)
	{
		cout << useraccount[n]->ID << "\t\t"; //将信息写出bankdat.data文件
		cout << useraccount[n]->money << "\t\t";
		cout << useraccount[n]->name << "\t\t";
		cout << useraccount[n]->passwd << endl;
	}
	cout << "______________________________________________________________________" << endl;
	cout << "输出所有账户完成" << endl;
	cin.get();
	return;
}

/*退出系统*/
void YH::exitYH()
{
	cout << endl
		 << "感谢你对本银行储蓄管理系统的支持,欢迎下次光临!" << endl;
	exit(0);
}

/*初始界面*/
void YH::show()
{
	int n;
	do
	{
		system("cls"); //清屏
		loaduser();
		cout << endl
			 << "请你输入相应的操作序号进行操作:" << endl;
		cout << endl
			 << "============================================================" << endl;
		cout << "1) 用户" << endl
			 << "2) 退出系统" << endl;
		cout << endl
			 << "============================================================" << endl;
		cout << "请操作选择";
		cin >> n;
		cout << "************************************************************" << endl;
		while (n < 1 || n > 3)
		{
			cout << "请输入正确的操作序号!" << endl;
			cin >> n;
		}
		switch (n)
		{
		case 1:
			functionshow1();
			break;
		case 2:
			exitYH(); //退出
			break;
		}
		cin.get();
	} while (true);
}

int main(int argc, char const *argv[])
{
	/* code */
	return 0;
}
