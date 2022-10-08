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
	if ((adminCommand.compare("로그아웃") == 0) || (adminCommand.compare("logout") == 0)) {
		return;
	}
	else if ((adminCommand.compare("시작") == 0) || (adminCommand.compare("start") == 0)) {
		StartOrEnd(START);
		return;
	}
	else if ((adminCommand.compare("종료") == 0) || (adminCommand.compare("end") == 0)) {
		bool isEnd = false;
		isEnd = StartOrEnd(END);
		if (isEnd) {
			Prioritizing();
		}

		// 전체 프로그램을 종료

	}
}

bool StartOrEnd(int command) {
	//fstream onOff("Course_Registration_On_Off.txt");	//파일 없을 때 자동 생성이 안됨 - 해결필요
	fstream onOff;
	onOff.open("Course_Registration_On_Off.txt", ios::in);
	if (!onOff.is_open()) {
		cout << "파일 열기 실패" << endl;
	}
	else {
		string state;
		onOff >> state;		// Course_Registration_On_Off.txt의 on 또는 off 상태를 읽어와 저장
		for (char& a : state) a = tolower(a);

		if (state.compare("on") == 0) {
			if (command == START) {
				cout << "이미 수강신청이 시작되어 시작할 수 없습니다." << endl;
			}
			else if (command == END) {
				onOff.close();
				onOff.open("Course_Registration_On_Off.txt", ios::out);
				onOff << "Off";
				cout << "수강신청을 종료합니다." << endl;
				onOff.close();

				return true;	// 유일하게 true를 리턴
			}

		}
		else if (state.compare("off") == 0) {
			if (command == START) {
				onOff.close();
				onOff.open("Course_Registration_On_Off.txt", ios::out);
				onOff << "On";
				cout << "수강신청을 시작합니다." << endl;
			}
			else if (command == END) {
				cout << "아직 수강신청이 시작되지 않았습니다." << endl;
			}
		}
		else {
			cout << "Course_Registration_On_Off.txt에 허용되지 않는 문자열이 입력되어있습니다." << endl;
		}
	}
	onOff.close();
	return false;
}

void Prioritizing() { //우선순위 정하는 함수

}