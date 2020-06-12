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
	cout << "* �û�������" << name << endl;
	cout << "* �ʺţ� " << ID << endl;
	cout << "* ���: " << money << endl;
	cout << "**********************************" << endl;
}

/*��Ǯ*/
void consumer::savemoney()
{
	double smoney;
	int judge = 1;
	while (judge)
	{
		cout << "����������: ";
		cin >> smoney;
		while (smoney <= 0)
		{
			cout << "�����������Ľ�����" << endl;
			cout << "���������" << endl;
			cin >> smoney;
		}
		money += smoney;
		cout << "���ɹ�������" << endl;
		cout << "�Ƿ���Ҫ������\n �ǣ�1���������֣���0" << endl;
		cin >> judge;
	}
}

/*ȡǮ*/
void consumer::fetchmoney()
{
	if (money <= 0)
	{
		cout << "����˻����С�ڵ���0�������ȳ�ֵ����" << endl;
		return;
	}
	double fmoney;
	int judge = 1;
	while (judge)
	{
		cout << "������Ҫȡ���Ľ�";
		cin >> fmoney;
		while (fmoney <= 0)
		{
			cout << "�����������Ľ�����" << endl;
			cout << "���������" << endl;
			cin >> fmoney;
		}
		if (money - fmoney < 0)
		{
			cout << "�Բ��������˻����㣡����" << endl;
		}
		else
		{
			money -= fmoney;
			cout << "ȡ��ɹ�������" << endl;
			cout << "�Ƿ���Ҫ����ȡ��ǣ�1�����������֣���0" << endl;
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

/*ת��*/
void YH::transfer(int x)
{
	int id;
	cout << "�������ʺ�:";
	cin >> id;
	int flag = 1;
	int i = 0;
	while ((i < useracnum) && (flag)) //ѭ������
	{
		if (id == useraccount[i]->get_id())
			flag = 0;
		else
			i++;
	}
	if (flag)
	{
		cout << "�ʺŲ�����!" << endl
			 << endl;
		return;
	}
	double b;

	cout << endl
		 << "��������Ҫת�ʵĽ��:";
	cin >> b;
	while (b <= 0)
	{
		cout << "��������ȷ������!" << endl;
		cout << "����";
		cin >> b;
	}
	if (useraccount[x]->get_money() < b)
		cout << "�Բ���,����!!" << endl;
	else
	{
		useraccount[x]->changemoney(-b);
		useraccount[i]->changemoney(b);
		cout << "ת�ʳɹ�!";
	}
	return;
}

/*��������*/
void YH::set_account()
{
	system("cls");
	int id;
	string nam;
	string passw;
	double m;

	cout << endl
		 << "�����뿪���ţ�";
	cin >> id;
	while (id < 100000 || id >= 1000000)
	{
		cout << endl
			 << "������6λ����!" << endl;
		cin >> id;
	}
	cout << endl
		 << "�����뿪����������" << endl;
	cin >> nam;
	cout << endl
		 << "�����뿪�����룺" << endl;
	cin >> passw;
	cout << endl
		 << "�����������:" << endl;
	cin >> m;
	while (m <= 0)
	{
		cout << "��������ȷ������!" << endl
			 << endl;
		cin >> m;
	}
	consumer *acc = new consumer(m, id, nam, passw);
	useraccount[useracnum] = acc;
	cout << "�����ɹ�!!" << endl
		 << endl;
	useracnum++;
	saveuser();
	cin.get();
	return;
}

/*�û��ļ����*/
void YH::saveuser()
{
	ofstream ofile("bankdat.dat", ios::out);   //�������ʽ���ļ�
	ofstream outfile("bankdat.dat", ios::out); //�������ʽ�����д���ļ�bankdat.data���մ��ڴ����������
	int n = 0;
	outfile << useracnum << "  ";
	for (; n < useracnum; n++)
	{
		outfile << useraccount[n]->ID << " "; //����Ϣд��bankdat.data�ļ�
		outfile << useraccount[n]->money << " ";
		outfile << useraccount[n]->name << " ";
		outfile << useraccount[n]->passwd << " ";
	}
	outfile.close(); //�ر��ļ�
}

/*�û��˻���¼*/
void YH::enter_account()
{
	system("cls");
	int id;
	cout << "�������ʺ�:";
	cin >> id;
	int flag = 1;
	int i = 0;
	while ((i < useracnum) && (flag)) //ѭ�������˻�
	{
		if (id == useraccount[i]->get_id())
			flag = 0;
		else
			i++;
	}
	if (flag)
	{
		cout << "�ʺŲ�����!" << endl
			 << endl;
		cin.get();
		return;
	}
	cout << "����������:";
	string passw;
	cin >> passw;
	if (passw != useraccount[i]->get_passwd()) //������󷵻ز���
	{
		cout << "�������!" << endl
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
		cout << "��ѡ����Ҫ���еĲ���:" << endl;
		cout << "������������������������������������������������" << endl;
		cout << "\t1)�鿴��Ϣ" << endl
			 << "\t2)ȡ��" << endl
			 << "\t3)���" << endl
			 << "\t4)ת��" << endl
			 << "\t5)����" << endl;
		cout << "������������������������������������������������" << endl;

		cin >> n;
		switch (n)
		{
		case 1:
			useraccount[i]->display();
			break;
		case 2:
			useraccount[i]->fetchmoney();
			saveuser();
			break; //ÿִ�е���һ��save���� ����дһ������
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

/*��ȡ�û���Ϣ����ʵ��*/
void YH::loaduser()
{
	ifstream infile("bankdat.dat", ios::in); //�����뷽ʽ���ļ�
	if (!infile)
	{
		cerr << "��ȡ����,��������!" << endl;
		return;
	}
	int n = 0;
	int id;
	double m;
	string nam, passw;
	infile >> useracnum;
	for (; n < useracnum; n++) //ȫ������
	{
		infile >> id; //���ļ��ж�����Ϣ
		infile >> m;
		infile >> nam;
		infile >> passw;
		useraccount[n]->passwd;
		consumer *acc = new consumer(m, id, nam, passw); //ÿ����һ��n����һ���ڴ�
		useraccount[n] = acc;							 //��ֵ�׵�ַ
	}
	infile.close();
	cout << "��ȡ��������!" << endl;
}

/*���˵�1*/
void YH::functionshow1()
{
	int n;
	do
	{
		system("cls"); //����
		loaduser();
		cout << endl
			 << "����������Ӧ�Ĳ�����Ž��в���:" << endl;
		cout << endl
			 << "============================================================" << endl;
		cout << "1) �û�����" << endl
			 << "2) �˻���½" << endl
			 << "3) ��ѯ" << endl
			 << "4) �˳�ϵͳ " << endl;
		cout << endl
			 << "============================================================" << endl;
		cout << "�����ѡ��";
		cin >> n;
		cout << "************************************************************" << endl;
		while (n < 1 || n > 4)
		{
			cout << "��������ȷ�Ĳ������!" << endl;
			cin >> n;
		}
		switch (n)
		{
		case 1:
			set_account(); //����
			break;
		case 2:
			enter_account(); //��½
			break;
		case 3:
			qu_account(); //��ѯ
			break;
		case 4:
			exitYH(); //�˳�
			break;
		}
		cin.get();
	} while (true);
}

/*��ѯ�û�*/
void YH::qu_account()
{
	system("cls");
	int n = 0;
	cout << "�˺�              ���               ����               ����" << endl;
	cout << "______________________________________________________________________" << endl;
	for (; n < useracnum; n++)
	{
		cout << useraccount[n]->ID << "\t\t"; //����Ϣд��bankdat.data�ļ�
		cout << useraccount[n]->money << "\t\t";
		cout << useraccount[n]->name << "\t\t";
		cout << useraccount[n]->passwd << endl;
	}
	cout << "______________________________________________________________________" << endl;
	cout << "��������˻����" << endl;
	cin.get();
	return;
}

/*�˳�ϵͳ*/
void YH::exitYH()
{
	cout << endl
		 << "��л��Ա����д������ϵͳ��֧��,��ӭ�´ι���!" << endl;
	exit(0);
}

/*��ʼ����*/
void YH::show()
{
	int n;
	do
	{
		system("cls"); //����
		loaduser();
		cout << endl
			 << "����������Ӧ�Ĳ�����Ž��в���:" << endl;
		cout << endl
			 << "============================================================" << endl;
		cout << "1) �û�" << endl
			 << "2) �˳�ϵͳ" << endl;
		cout << endl
			 << "============================================================" << endl;
		cout << "�����ѡ��";
		cin >> n;
		cout << "************************************************************" << endl;
		while (n < 1 || n > 3)
		{
			cout << "��������ȷ�Ĳ������!" << endl;
			cin >> n;
		}
		switch (n)
		{
		case 1:
			functionshow1();
			break;
		case 2:
			exitYH(); //�˳�
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
