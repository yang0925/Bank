#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#define ACCOUNT 200
#define NAME_NUM 20
#define NAME_LEN 20
using namespace std;

class NormalAccount { //�������
protected:
	const int accID;
	int balance;
	char *cusName;
	const char *nameNum;

public:
	NormalAccount(int accID, int balance, char *cusName, const char *nameNum) : accID(accID), nameNum(nameNum)
	{
		this->cusName = new char[NAME_LEN];
		this->balance = balance;
		strcpy(this->cusName, cusName);
	}
	NormalAccount(const NormalAccount &copy_Bank) :accID(copy_Bank.accID)
	{
		cout << "Copy" << endl;
		balance = copy_Bank.balance;
		cusName = new char[NAME_LEN];
		strcpy(cusName, copy_Bank.cusName);
		char *copy_nameNum = new char[NAME_NUM];
		strcpy_s(copy_nameNum, NAME_NUM, copy_Bank.nameNum);
		nameNum = copy_nameNum;
	}
	int getaccID() {
		return accID;
	}
	const char *getnameNum() {
		return nameNum;
	}
	int getbalance() {
		return balance;
	}

	char *getcusName() const {
		return cusName;
	}

	virtual void plus(int money) {
		int interest;

		interest = ((balance + money)* 0.01);
		balance = (balance + money) + interest;
		cout << "���ڱݾ� : " << interest << endl;
	}
	void minus(int money) {
		balance -= money;
	}
	virtual void print() {
		cout << endl << "�������ID: " << accID << endl;
		cout << "��  ��: " << cusName << endl;
		cout << "��  ��: " << balance << endl;
		cout << "�ֹε�Ϲ�ȣ: " << nameNum << endl << endl;
	}
};

class DepositAccount : public NormalAccount //���ݰ���
{
public:
	DepositAccount(int accID, NormalAccount id) : NormalAccount(accID, 0, id.getcusName(), id.getnameNum()) {}

	void plus(int money) {
		int interest;

		interest = ((balance + money)* 0.02);
		balance = (balance + money) + interest;
		cout << "���ڱݾ� : " << interest << endl;
	}

	void print() {
		cout << endl << "���ݰ���ID: " << accID << endl;
		cout << "��  ��: " << cusName << endl;
		cout << "��  ��: " << balance << endl;
		cout << "�ֹε�Ϲ�ȣ: " << nameNum << endl << endl;
	}

	virtual ~DepositAccount() {}
};

class AccountManager
{
public:
	void normalCreateAccount() { //������� ����
		int id, money, account;
		char *name = new char[NAME_LEN];
		char *nameNum = new char[NAME_NUM];

		cout << endl << "[������� ����]" << endl << endl;
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
			if (customer[i]->getaccID() == id) {
				cout << "���°� �ߺ��Ǿ����ϴ�." << endl;
				return;
			}
			if (!strcmp(customer[i]->getnameNum(), nameNum)) {
				cout << "�ֹε�Ϲ�ȣ�� �ߺ��Ǿ����ϴ�." << endl;
				return;
			}
		}

		customer[index] = new NormalAccount(id, money, name, nameNum);
		index++;

		cout << endl << "������� " << id << "�� �����Ͽ����ϴ�." << endl << endl;
	}

	void depositCreateAccount() { //���ݰ��� ����
		int id, money, account;
		char *nameNum = new char[NAME_NUM];
		int arr;

		cout << endl << "[���ݰ��� ����]" << endl << endl;
		cout << "����ڸ� Ȯ���ϰڽ��ϴ�." << endl;
		cout << "�ֹε�Ϲ�ȣ: "; cin >> nameNum;
		cout << "����ID: "; cin >> id;

		for (int i = 0; i < index; i++) {
			if (customer[i]->getaccID() == id) {
				cout << "���°� �ߺ��Ǿ����ϴ�." << endl;
				return;
			}
		}

		if ((arr = foundUser(nameNum)) != -1) {
			customer[index++] = new DepositAccount(id, *customer[arr]);
			cout << endl << "���ݰ��� " << id << "�� �����Ͽ����ϴ�." << endl << endl;
		}
		else {
			cout << "����ڸ� ã�� �� �����ϴ�." << endl;
		}
	}

	int foundUser(char* nameNum) { //����� ã��
		for (int i = 0; i < index; i++) {
			if (!strcmp(customer[i]->getnameNum(), nameNum)) {
				return i;
			}
		}
		return -1;
	}

	void plusMoney() { //�Ա�
		int id, money;

		cout << endl << "[��    ��]" << endl << endl;
		cout << "����ID: "; cin >> id;
		cout << "�Աݾ�: "; cin >> money;

		if (money < 1) {
			cout << "1�� �̻��� �Աݾ��� �־��ּ���" << endl;
			return;
		}

		for (int i = 0; i < index; i++)
		{
			if (customer[i]->getaccID() == id) {
				customer[i]->plus(money);
				cout << endl << "���� " << id << "�� " << money << "�� �Ա��Ͽ����ϴ�." << endl << endl;
				return;
			}
		}
		cout << "���°� �����ϴ�." << endl;
	}

	void minusMoney() { //���
		int id, money;

		cout << endl << "[��    ��]" << endl << endl;
		cout << "����ID: "; cin >> id;
		cout << "��ݾ�: "; cin >> money;

		if (money < 1) {
			cout << "1�� �̻��� ��ݾ��� �־��ּ���" << endl;
			return;
		}

		for (int i = 0; i < index; i++)
		{
			if (customer[i]->getaccID() == id) {
				if (money > customer[i]->getbalance()) {
					cout << "����� �� �����ϴ�." << endl;
				}
				else {
					customer[i]->minus(money);
					cout << endl << "���� " << id << "���� " << money << "�� ����Ͽ����ϴ�." << endl << endl;
				}
				return;
			}
		}
		cout << "���°� �����ϴ�." << endl;
	}


	void accoutInformation() { //�������� ��ü ���
		for (int i = 0; i < index; i++) {
			customer[i]->print();
		}
	}
private:
	NormalAccount *customer[ACCOUNT];
	int index = 0;
};

void main() {
	AccountManager account_manager;
	int choose;

	while (true) {
		cout << "-----Menu-----" << endl << endl;
		cout << "1. ������� ����" << endl;
		cout << "2. ���ݰ��� ����" << endl;
		cout << "3. ��    ��" << endl;
		cout << "4. ��    ��" << endl;
		cout << "5. �������� ��ü ���" << endl;
		cout << "6. ���α׷� ����" << endl << endl;
		cout << "����: "; cin >> choose;

		switch (choose) {
		case 1:
			account_manager.normalCreateAccount();
			break;
		case 2:
			account_manager.depositCreateAccount();
			break;
		case 3:
			account_manager.plusMoney();
			break;
		case 4:
			account_manager.minusMoney();
			break;
		case 5:
			account_manager.accoutInformation();
			break;
		case 6:
			return;
		}
	}
}