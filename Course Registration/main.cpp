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
	cout << "================ ���� ������ �׽�Ʈ ��� ================" << endl;
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
	//�л� ������Ʈ���� �Է��Ѵٰ� ����
	//find ��ǻ��ȸ��/��ǻ�Ͱ��к�/3/0123 �̷� ������ �Է��ϸ�
	//arr[0] = find
	//arr[1] = ��ǻ��ȸ��/��ǻ�Ͱ��к�/3/0123
	//�̷��� ��
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
	//�˻� �� �α׾ƿ� ��ɾ ���� �ش� �Լ� ȣ��
	if (arr[0] == "find" || arr[0] == "f" || arr[0] == "#" || arr[0] == "�˻�" || arr[0] == "����") {
		Search(arr[1]);
	}

	else if (arr[0] == "logout" || arr[0] == "l" || arr[0] =="." || arr[0] =="�α׾ƿ�" || arr[0] =="��������") {
		Logout(arr[1]);
	}

	else if (arr[0] == "add" || arr[0] == "ad" || arr[0] == "+" || arr[0] == "�߰�" || arr[0] == "����") {
		Add(arr[1]);
	}

	else if(arr[0] == "delete" || arr[0] == "d" || arr[0] == "-" || arr[0] == "����" || arr[0] == "����") {
		Delete(arr[1]);
	}
	
	else if (arr[0] == "alter" || arr[0] == "alt" || arr[0] == "~" || arr[0] == "����" || arr[0] == "����") {
		Alter(arr[1]);
	}*/
	return 0;
}