#pragma once
#include "IntegrityCheck.h"
#include "SubjectData.h"
#include "Search.h"
#include "Add.h"
#include "Delete.h"
#include "Alter.h"
#include "prompt.h"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

int main() {
	
	Integrity_Check();
	cout << "================ 과목 데이터 테스트 출력 ================" << endl;
	for (int i = 0; i < 10000; i++) {
		if (Subject[i] != NULL) {
			cout << Subject[i]->id << " ";
			cout << Subject[i]->name << " ";
			cout << Subject[i]->credit << " ";
			cout << Subject[i]->major << " ";
			cout << Subject[i]->grade << " ";
			cout << Subject[i]->time << " ";
			cout << Subject[i]->max << endl;
		}
	}
	while (true) { User_info_menu(); }
	/*
	//학생 프롬프트에서 입력한다고 가정
	//find 컴퓨터회로/컴퓨터공학부/3/0123 이런 식으로 입력하면
	//arr[0] = find
	//arr[1] = 컴퓨터회로/컴퓨터공학부/3/0123
	//이렇게 들어감
	string Input;
	getline(cin, Input);
	stringstream stream;
	stream.str(Input);
	string token;
	string arr[3] = { "0" };
	int i = 0;
	while (stream >> token) {
		arr[i] = token;
		i++;
	}
	//검색 및 로그아웃 명령어에 따라 해당 함수 호출
	if (arr[0] == "find" || arr[0] == "f" || arr[0] == "#" || arr[0] == "검색" || arr[0] == "ㄱㅅ") {
		Search(arr[1]);
	}

	else if (arr[0] == "logout" || arr[0] == "l" || arr[0] =="." || arr[0] =="로그아웃" || arr[0] =="ㄹㄱㅇㅇ") {
		Logout(arr[1]);
	}

	else if (arr[0] == "add" || arr[0] == "ad" || arr[0] == "+" || arr[0] == "추가" || arr[0] == "ㅊㄱ") {
		Add(arr[1]);
	}

	else if(arr[0] == "delete" || arr[0] == "d" || arr[0] == "-" || arr[0] == "삭제" || arr[0] == "ㅅㅈ") {
		Delete(arr[1]);
	}
	
	else if (arr[0] == "alter" || arr[0] == "alt" || arr[0] == "~" || arr[0] == "변경" || arr[0] == "ㅂㄱ") {
		Alter(arr[1]);
	}*/
	return 0;
}