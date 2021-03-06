#pragma once
#pragma once
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <string>

#ifndef BANK_H
#define BANK_H
using namespace std;

/*银行类*/
class consumer;
class Adm;

class YH
{
public: //函数成员
	YH();
	void qu_account();	  //查询用户
	void set_account();	  //银行开户
	void transfer(int);	  //转账
	void enter_account(); //用户登录
	void exitYH();		  //退出系统
	void show();		  //初始界面
	void functionshow1(); //主菜单1
	void saveuser();	  //输入
	void saveadm();		  //输出
	void loaduser();
	void loadadm();

protected:					   //数据成员
	consumer *useraccount[20]; //账户数
	static int useracnum;
};

/*用户类*/
class consumer : public YH //继承类YH
{
public:
	friend class YH; //类YH的所有成员函数都是类consumer的友元函数，能存取类consumer的私有成员和保护成员
	consumer(double m, int id, const string Name = " ", const string PassWord = " ");
	consumer();
	void setid(int);
	void setname(string);
	void setpassword(string);
	void setmoney(double);
	int get_id() const; //取得账号
	double get_money() const;
	string get_name() const;
	string get_passwd() const; //取得密码
	void display();
	void savemoney();		  //存钱
	void fetchmoney();		  //取钱
	void changemoney(double); //计算余额

private:
	int ID;		   //开户帐号
	string passwd; //用户密码
	string name;   //用户姓名
	double money;  //开户金额
};

#endif
