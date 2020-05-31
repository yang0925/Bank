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
		cout << "계좌ID: " << accID << endl;
		cout << "이  름: " << cusName << endl;
		cout << "잔  액: " << balance << endl;
		cout << "주민등록번호: " << nameNum << endl;
	}
};

Bank *customer = new Bank[ACCOUNT];

int index = 0;

void createAccount() {
	int id, money;
	char name[NAME_LEN], nameNum[NAME_NUM];


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
		if (customer[i].getaccID() == id) {
			cout << "계좌가 중복되었습니다." << endl;
			return;
		}
		if (!strcmp(customer[i].getnameNum(), nameNum)) {
			cout << "중복된 사용자입니다." << endl;
			return;
		}
	}

	customer[index] = Bank(id, money, name, nameNum);
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
		if (customer[i].getaccID() == id) {
			customer[i].plus(money);
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
		if (customer[i].getaccID() == id) {
			if (money > customer[i].getbalance()) {
				cout << "출금할 수 없습니다." << endl;
			}
			else {
				customer[i].minus(money);
			}
			return;
		}
	}
	cout << "계좌가 없습니다." << endl;
}

void accoutInformation() { //계좌정보 전체 출력
	for (int i = 0; i < index; i++) {
		customer[i].print();
	}
}

void main() {
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