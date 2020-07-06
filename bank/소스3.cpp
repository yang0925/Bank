#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#define ACCOUNT 200
#define NAME_NUM 20
#define NAME_LEN 20
using namespace std;

class NormalAccount { //보통계좌
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
		cout << "이자금액 : " << interest << endl;
	}
	void minus(int money) {
		balance -= money;
	}
	virtual void print() {
		cout << endl << "보통계좌ID: " << accID << endl;
		cout << "이  름: " << cusName << endl;
		cout << "잔  액: " << balance << endl;
		cout << "주민등록번호: " << nameNum << endl << endl;
	}
};

class DepositAccount : public NormalAccount //예금계좌
{
public:
	DepositAccount(int accID, NormalAccount id) : NormalAccount(accID, 0, id.getcusName(), id.getnameNum()) {}

	void plus(int money) {
		int interest;

		interest = ((balance + money)* 0.02);
		balance = (balance + money) + interest;
		cout << "이자금액 : " << interest << endl;
	}

	void print() {
		cout << endl << "예금계좌ID: " << accID << endl;
		cout << "이  름: " << cusName << endl;
		cout << "잔  액: " << balance << endl;
		cout << "주민등록번호: " << nameNum << endl << endl;
	}

	virtual ~DepositAccount() {}
};

class AccountManager
{
public:
	void normalCreateAccount() { //보통계좌 개설
		int id, money, account;
		char *name = new char[NAME_LEN];
		char *nameNum = new char[NAME_NUM];

		cout << endl << "[보통계좌 개설]" << endl << endl;
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
				cout << "주민등록번호가 중복되었습니다." << endl;
				return;
			}
		}

		customer[index] = new NormalAccount(id, money, name, nameNum);
		index++;

		cout << endl << "보통계좌 " << id << "를 개설하였습니다." << endl << endl;
	}

	void depositCreateAccount() { //예금계좌 개설
		int id, money, account;
		char *nameNum = new char[NAME_NUM];
		int arr;

		cout << endl << "[예금계좌 개설]" << endl << endl;
		cout << "사용자를 확인하겠습니다." << endl;
		cout << "주민등록번호: "; cin >> nameNum;
		cout << "계좌ID: "; cin >> id;

		for (int i = 0; i < index; i++) {
			if (customer[i]->getaccID() == id) {
				cout << "계좌가 중복되었습니다." << endl;
				return;
			}
		}

		if ((arr = foundUser(nameNum)) != -1) {
			customer[index++] = new DepositAccount(id, *customer[arr]);
			cout << endl << "예금계좌 " << id << "를 개설하였습니다." << endl << endl;
		}
		else {
			cout << "사용자를 찾을 수 없습니다." << endl;
		}
	}

	int foundUser(char* nameNum) { //사용자 찾기
		for (int i = 0; i < index; i++) {
			if (!strcmp(customer[i]->getnameNum(), nameNum)) {
				return i;
			}
		}
		return -1;
	}

	void plusMoney() { //입금
		int id, money;

		cout << endl << "[입    금]" << endl << endl;
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
				cout << endl << "계좌 " << id << "에 " << money << "를 입금하였습니다." << endl << endl;
				return;
			}
		}
		cout << "계좌가 없습니다." << endl;
	}

	void minusMoney() { //출금
		int id, money;

		cout << endl << "[출    금]" << endl << endl;
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
					cout << endl << "계좌 " << id << "에서 " << money << "를 출금하였습니다." << endl << endl;
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
	NormalAccount *customer[ACCOUNT];
	int index = 0;
};

void main() {
	AccountManager account_manager;
	int choose;

	while (true) {
		cout << "-----Menu-----" << endl << endl;
		cout << "1. 보통계좌 개설" << endl;
		cout << "2. 예금계좌 개설" << endl;
		cout << "3. 입    금" << endl;
		cout << "4. 출    금" << endl;
		cout << "5. 계좌정보 전체 출력" << endl;
		cout << "6. 프로그램 종료" << endl << endl;
		cout << "선택: "; cin >> choose;

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