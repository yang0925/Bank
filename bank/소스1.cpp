#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#define ACCOUNT 100
#define NAME_NUM 20
#define NAME_LEN 20
using namespace std;

class Bank {
private:
	int accID;
	int balance;
	char *cusName;
	char nameNum[NAME_NUM];

public:
	Bank() {
		accID = -1;
		balance = -1;
		cusName = NULL;
		*nameNum = NULL;
	}
	~Bank() {
		delete[] cusName;
	}
	int getaccID() {
		return accID;
	}
	char *getnameNum() {
		return nameNum;
	}
	int getbalance() {
		return balance;
	}
	Bank(int accID, int balance, char *cusName, char *nameNum) {
		this->cusName = new char[NAME_LEN];
		this->accID = accID;
		this->balance = balance;
		strcpy(this->cusName, cusName);
		strcpy(this->nameNum, nameNum);
	}
	void plus(int money) {
		balance += money;
	}
	void minus(int money) {
		balance -= money;
	}
	void print() {
		cout << "����ID: " << accID << endl;
		cout << "��  ��: " << cusName << endl;
		cout << "��  ��: " << balance << endl;
		cout << "�ֹε�Ϲ�ȣ: " << nameNum << endl;
	}
};

Bank *customer = new Bank[ACCOUNT];

int index = 0;

void createAccount() {
	int id, money;
	char name[NAME_LEN], nameNum[NAME_NUM];


	cout << "[���� ����]" << endl;
	cout << "����ID: "; cin >> id;
	cout << "��  ��: "; cin >> name;
	cout << "�Աݾ�: "; cin >> money;
	cout << "�ֹε�Ϲ�ȣ: "; cin >> nameNum;

	if (index > ACCOUNT) {
		cout << "�� �̻� ���¸� ������ �� �����ϴ�." << endl;
		return;
	}

	if (id < 0) {
		cout << "����� �� �����ϴ�." << endl;
		return;
	}
	if (money < 10) {
		cout << "10�� �̻��� �Աݾ��� �־��ּ���" << endl;
		return;
	}

	for (int i = 0; i < index; i++) {
		if (customer[i].getaccID() == id) {
			cout << "���°� �ߺ��Ǿ����ϴ�." << endl;
			return;
		}
		if (!strcmp(customer[i].getnameNum(), nameNum)) {
			cout << "�ߺ��� ������Դϴ�." << endl;
			return;
		}
	}

	customer[index] = Bank(id, money, name, nameNum);
	index++;
}

void plusMoney() { //�Ա�
	int id, money;

	cout << "[��    ��]" << endl;
	cout << "����ID: "; cin >> id;
	cout << "�Աݾ�: "; cin >> money;

	if (money < 1) {
		cout << "1�� �̻��� �Աݾ��� �־��ּ���" << endl;
		return;
	}

	for (int i = 0; i < index; i++)
	{
		if (customer[i].getaccID() == id) {
			customer[i].plus(money);
			return;
		}
	}
	cout << "���°� �����ϴ�." << endl;
}

void minusMoney() { //���
	int id, money;

	cout << "[��    ��]" << endl;
	cout << "����ID: "; cin >> id;
	cout << "��ݾ�: "; cin >> money;

	if (money < 1) {
		cout << "1�� �̻��� ��ݾ��� �־��ּ���" << endl;
		return;
	}

	for (int i = 0; i < index; i++)
	{
		if (customer[i].getaccID() == id) {
			if (money > customer[i].getbalance()) {
				cout << "����� �� �����ϴ�." << endl;
			}
			else {
				customer[i].minus(money);
			}
			return;
		}
	}
	cout << "���°� �����ϴ�." << endl;
}

void accoutInformation() { //�������� ��ü ���
	for (int i = 0; i < index; i++) {
		customer[i].print();
	}
}

void main() {
	int choose;

	while (true) {
		cout << "-----Menu-----" << endl;
		cout << "1. ���°���" << endl;
		cout << "2. ��    ��" << endl;
		cout << "3. ��    ��" << endl;
		cout << "4. �������� ��ü ���" << endl;
		cout << "5. ���α׷� ����" << endl;
		cout << "����: "; cin >> choose;

		switch (choose) {
		case 1:
			createAccount();
			break;
		case 2:
			plusMoney();
			break;
		case 3:
			minusMoney();
			break;
		case 4:
			accoutInformation();
			break;
		case 5:
			return;
		}
	}
}