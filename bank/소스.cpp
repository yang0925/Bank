#include <iostream>
#define NAME_LEN 20
using namespace std;

typedef struct {
	int accID;
	int balance;
	char cusName[NAME_LEN];
}Account;

Account *customer = new Account[100];

int index = 0;

void createAcc() { //���� ����
	int id, money;
	char name[NAME_LEN];

	cout << "[���� ����]" << endl;
	cout << "����ID: "; cin >> id;
	cout << "��  ��: "; cin >> name;
	cout << "�Աݾ�: "; cin >> money;

	if (id < 0) {
		cout << "����� �� �����ϴ�." << endl;
		return;
	}
	if (money < 10) {
		cout << "10�� �̻��� �Աݾ��� �־��ּ���" << endl;
		return;
	}

	for (int i = 0; i < index; i++) {
		if (customer[i].accID == id) {
			cout << "���°� �ߺ��Ǿ����ϴ�." << endl;
			return;
		}
	}

	customer[index].accID = id;
	customer[index].balance = money;

	strcpy_s(customer[index].cusName, name);
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
		if (customer[i].accID == id) {

			customer[i].balance += money;
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
		if (customer[i].accID == id) {
			if (money > customer[i].balance) {
				cout << "����� �� �����ϴ�." << endl;
			}
			else {
				customer[i].balance -= money;
			}
			return;
		}
	}
	cout << "���°� �����ϴ�." << endl;
}

void accInfo() { //�������� ��ü ���
	for (int i = 0; i < index; i++) {
		cout << "����ID: " << customer[i].accID << endl;
		cout << "��  ��: " << customer[i].cusName << endl;
		cout << "��  ��: " << customer[i].balance << endl;
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
			createAcc();
			break;
		case 2:
			plusMoney();
			break;
		case 3:
			minusMoney();
			break;
		case 4:
			accInfo();
			break;
		case 5:
			delete[] customer;
			return;
		}
	}
}