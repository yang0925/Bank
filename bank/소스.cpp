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

void createAcc() { //계좌 개설
	int id, money;
	char name[NAME_LEN];

	cout << "[계좌 개설]" << endl;
	cout << "계좌ID: "; cin >> id;
	cout << "이  름: "; cin >> name;
	cout << "입금액: "; cin >> money;

	if (id < 0) {
		cout << "사용할 수 없습니다." << endl;
		return;
	}
	if (money < 10) {
		cout << "10원 이상의 입금액을 넣어주세요" << endl;
		return;
	}

	for (int i = 0; i < index; i++) {
		if (customer[i].accID == id) {
			cout << "계좌가 중복되었습니다." << endl;
			return;
		}
	}

	customer[index].accID = id;
	customer[index].balance = money;

	strcpy_s(customer[index].cusName, name);
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
		if (customer[i].accID == id) {

			customer[i].balance += money;
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
		if (customer[i].accID == id) {
			if (money > customer[i].balance) {
				cout << "출금할 수 없습니다." << endl;
			}
			else {
				customer[i].balance -= money;
			}
			return;
		}
	}
	cout << "계좌가 없습니다." << endl;
}

void accInfo() { //계좌정보 전체 출력
	for (int i = 0; i < index; i++) {
		cout << "계좌ID: " << customer[i].accID << endl;
		cout << "이  름: " << customer[i].cusName << endl;
		cout << "잔  액: " << customer[i].balance << endl;
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