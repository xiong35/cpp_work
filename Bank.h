#pragma once
#pragma once
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <string>

#ifndef BANK_H
#define BANK_H
using namespace std;

/*������*/
class consumer;
class Adm;

class YH
{
public: //������Ա
	YH();
	void qu_account();	  //��ѯ�û�
	void qu_server();	  //��ѯְԱ
	void set_account();	  //���п���
	void set_register();  //ְԱע��
	void del_account();	  //��������
	void transfer(int);	  //ת��
	void enter_account(); //�û���¼
	void enter_server();  //ְԱ��¼
	void exitYH();		  //�˳�ϵͳ
	void show();		  //��ʼ����
	void functionshow1(); //���˵�1
	void functionshow2(); //���˵�2
	void saveuser();	  //����
	void saveadm();		  //���
	void loaduser();
	void loadadm();

protected:					   //���ݳ�Ա
	consumer *useraccount[20]; //�˻���
	static int useracnum;
	Adm *admaccount[20]; //ְԱ��
	static int admacnum;
};

/*�û���*/
class consumer : public YH //�̳���YH
{
public:
	friend class YH; //��YH�����г�Ա����������consumer����Ԫ�������ܴ�ȡ��consumer��˽�г�Ա�ͱ�����Ա
	consumer(double m, int id, const string Name = " ", const string PassWord = " ");
	consumer();
	void setid(int);
	void setname(string);
	void setpassword(string);
	void setmoney(double);
	int get_id() const; //ȡ���˺�
	double get_money() const;
	string get_name() const;
	string get_passwd() const; //ȡ������
	void display();
	void savemoney();		  //��Ǯ
	void fetchmoney();		  //ȡǮ
	void changemoney(double); //�������
	void changepassword();	  //�޸�����

private:
	int ID;		   //�����ʺ�
	string passwd; //�û�����
	string name;   //�û�����
	double money;  //�������
};

/*ְԱ��*/
class Adm : public YH
{
public:
	friend class YH;
	Adm(int id, const string = " ", const string = " ");
	void setuserid(int);
	int getuserid() const;
	void setname(string);
	string getname();
	void setpassword(string);
	string getpassword() const;
	void display() const;
	void changepasswd(); //�޸�����
private:
	string password; //ְԱ����
	string admname;	 //ְԱ����
	int userid;		 //ְԱ����
};

#endif
