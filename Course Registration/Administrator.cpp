#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include "Administrator.h"
#define START 1
#define END 0
using namespace std;



void Administrator_menu() {
	string adminCommand;
	cin >> adminCommand;
	if ((adminCommand.compare("�α׾ƿ�") == 0) || (adminCommand.compare("logout") == 0)) {
		return;
	}
	else if ((adminCommand.compare("����") == 0) || (adminCommand.compare("start") == 0)) {
		StartOrEnd(START);
		return;
	}
	else if ((adminCommand.compare("����") == 0) || (adminCommand.compare("end") == 0)) {
		bool isEnd = false;
		isEnd = StartOrEnd(END);
		if (isEnd) {
			Prioritizing();
		}

		// ��ü ���α׷��� ����

	}
}

bool StartOrEnd(int command) {
	//fstream onOff("Course_Registration_On_Off.txt");	//���� ���� �� �ڵ� ������ �ȵ� - �ذ��ʿ�
	fstream onOff;
	onOff.open("Course_Registration_On_Off.txt", ios::in);
	if (!onOff.is_open()) {
		cout << "���� ���� ����" << endl;
	}
	else {
		string state;
		onOff >> state;		// Course_Registration_On_Off.txt�� on �Ǵ� off ���¸� �о�� ����
		for (char& a : state) a = tolower(a);

		if (state.compare("on") == 0) {
			if (command == START) {
				cout << "�̹� ������û�� ���۵Ǿ� ������ �� �����ϴ�." << endl;
			}
			else if (command == END) {
				onOff.close();
				onOff.open("Course_Registration_On_Off.txt", ios::out);
				onOff << "Off";
				cout << "������û�� �����մϴ�." << endl;
				onOff.close();

				return true;	// �����ϰ� true�� ����
			}

		}
		else if (state.compare("off") == 0) {
			if (command == START) {
				onOff.close();
				onOff.open("Course_Registration_On_Off.txt", ios::out);
				onOff << "On";
				cout << "������û�� �����մϴ�." << endl;
			}
			else if (command == END) {
				cout << "���� ������û�� ���۵��� �ʾҽ��ϴ�." << endl;
			}
		}
		else {
			cout << "Course_Registration_On_Off.txt�� ������ �ʴ� ���ڿ��� �ԷµǾ��ֽ��ϴ�." << endl;
		}
	}
	onOff.close();
	return false;
}

void Prioritizing() { //�켱���� ���ϴ� �Լ�

}