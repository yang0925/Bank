#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#define ACCOUNT 100
#define NAME_NUM 20
#define NAME_LEN 20
using namespace std;

class Bank {
private:
	const int accID;
	int balance;
	char *cusName;
	const char *nameNum;

public:
	Bank(int accID, int balance, char *cusName, char *nameNum) : accID(accID), nameNum(nameNum)
	{
		this->cusName = new char[NAME_LEN];
		this->balance = balance;
		strcpy(this->cusName, cusName);
	}
	Bank(const Bank &copy_Bank):accID(copy_Bank.accID)
	{
		cout << "Copy" << endl;
		balance = copy_Bank.balance;
		cusName = new char[NAME_LEN];
		strcpy_s(cusName, NAME_LEN, copy_Bank.cusName);
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
	
	void plus(int money) {
		balance += money;
	}
	void minus(int money) {
		balance -= money;
	}
	void print() {
		cout << "계좌ID: " << accID << endl;
		cout << "이  름: " << cusName << endl;
		cout << "잔  액: " << balance << endl;
		cout << "주민등록번호: " << nameNum << endl;
	}
};



class AccountManager
{
public:
	void createAccount() {
		int id, money;
		char *name = new char[NAME_LEN];
		char *nameNum = new char[NAME_NUM];


		cout << "[계좌 개설]" << endl;
		cout << "계좌ID: "; cin >> id;
		cout << "이  름: "; cin >> name;
		cout << "입금액: "; cin >> money;
		cout << "주민등록번호: "; cin >> nameNum;

		if (index > ACCOUNT) {
			cout << "더 이상 계좌를 개설할 수 없습니다." << endl;
			return;
		}

		if (id < 0) {
			cout << "사용할 수 없습니다." << endl;
			return;
		}
		if (money < 10) {
			cout << "10원 이상의 입금액을 넣어주세요" << endl;
			return;
		}

		for (int i = 0; i < index; i++) {
			if (customer[i]->getaccID() == id) {
				cout << "계좌가 중복되었습니다." << endl;
				return;
			}
			if (!strcmp(customer[i]->getnameNum(), nameNum)) {
				cout << "중복된 사용자입니다." << endl;
				return;
			}
		}

		customer[index] = new Bank(id, money, name, nameNum);
		index++;
	}

	void plusMoney() { //입금
		int id, money;

		cout << "[입    금]" << endl;
		cout << "계좌ID: "; cin >> id;
		cout << "입금액: "; cin >> money;

		if (money < 1) {
			cout << "1원 이상의 입금액을 넣어주세요" << endl;
			return;
		}

		for (int i = 0; i < index; i++)
		{
			if (customer[i]->getaccID() == id) {
				customer[i]->plus(money);
				return;
			}
		}
		cout << "계좌가 없습니다." << endl;
	}

	void minusMoney() { //출금
		int id, money;

		cout << "[출    금]" << endl;
		cout << "계좌ID: "; cin >> id;
		cout << "출금액: "; cin >> money;

		if (money < 1) {
			cout << "1원 이상의 출금액을 넣어주세요" << endl;
			return;
		}

		for (int i = 0; i < index; i++)
		{
			if (customer[i]->getaccID() == id) {
				if (money > customer[i]->getbalance()) {
					cout << "출금할 수 없습니다." << endl;
				}
				else {
					customer[i]->minus(money);
				}
				return;
			}
		}
		cout << "계좌가 없습니다." << endl;
	}

	void accoutInformation() { //계좌정보 전체 출력
		for (int i = 0; i < index; i++) {
			customer[i]->print();
		}
	}
private:
	Bank *customer[ACCOUNT];
	int index = 0;
};



void main() {
	AccountManager account_manager;
	int choose;

	while (true) {
		cout << "-----Menu-----" << endl;
		cout << "1. 계좌개설" << endl;
		cout << "2. 입    금" << endl;
		cout << "3. 출    금" << endl;
		cout << "4. 계좌정보 전체 출력" << endl;
		cout << "5. 프로그램 종료" << endl;
		cout << "선택: "; cin >> choose;

		switch (choose) {
		case 1:
			account_manager.createAccount();
			break;
		case 2:
			account_manager.plusMoney();
			break;
		case 3:
			account_manager.minusMoney();
			break;
		case 4:
			account_manager.accoutInformation();
			break;
		case 5:
			return;
		}
	}
}