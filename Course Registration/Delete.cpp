#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <algorithm>
#include "SubjectData.h"
using namespace std;

void Delete(string command) {
	string studentid = "202111312";
	string studentname = "������";
	string id = command;
	string line;
	int lineCount = 0;
	int pos;

	// �׳� ������ �ϸ� �ȵǰ� �̾� �ٿ�����... �̿�

	fstream f1(studentid + "_" + studentname + "_������û���.txt", ios::in | ios::out);
	if (f1.is_open()) {
		while (f1.peek() != EOF) {
			lineCount++;
			getline(f1, line);
			string tmpid = line.substr(0, 4);
			if (tmpid == id) {
				pos = lineCount;
				/*f1.seekg(0, f1.end);
				int length = f1.tellg();
				f1.seekg(0, f1.beg);
				char* buffer = new char[length];
				f1.read(buffer, length);
				cout << buffer;*/

				lineCount = 0;
				f1.close();
				fstream f2(id + "_" + Subject[stoi(id)]->name + "_�⼮��.txt", ios::in | ios::out);
				while (f2.peek() != EOF) {
					lineCount++;
					getline(f2, line);
					string tmpstuid = line.substr(0, 9);
					if (tmpstuid == studentid) {
						pos = lineCount;
						f2.close();
						cout << "���� ��ȣ <" << id << "> ���� �Ϸ�";
						return;
					}
				}
			}
		}
		cout << "���� : ���� ��û ���� ��� ������ �����ϴ�.";
		f1.close();
		return;
	}
}