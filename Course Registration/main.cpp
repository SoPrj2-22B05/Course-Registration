#pragma once
#include "IntegrityCheck.h"
#include "SubjectData.h"
#include "Search.h"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

int main() {
	/*
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
	}*/


	//학생 프롬프트에서 입력한다고 가정
	//find 컴퓨터회로/컴퓨터공학부/3/0123 이런 식으로 입력하면
	//command[0] = find
	//command[1] = 컴퓨터회로/컴퓨터공학부/3/0123
	// 이렇게 들어감

	string Input;
	getline(cin, Input);
	stringstream stream;
	stream.str(Input);
	string token;
	string arr[2] = {"0"};
	int i = 0;
	while (stream >> token) {
		arr[i] = token;
		i++;
	}

	if (arr[0] == "find") {
		Search(arr[1]);
	}
	if (arr[0] == "logout") {
		Logout(arr[1]);
	}
	return 0;
}