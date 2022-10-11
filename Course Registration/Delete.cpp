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
	string studentname = "송현우";
	string id = command;
	string line;
	int lineCount = 0;
	int pos;

	// 그냥 삭제만 하면 안되고 이어 붙여야함... 미완

	fstream f1(studentid + "_" + studentname + "_수강신청목록.txt", ios::in | ios::out);
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
				fstream f2(id + "_" + Subject[stoi(id)]->name + "_출석부.txt", ios::in | ios::out);
				while (f2.peek() != EOF) {
					lineCount++;
					getline(f2, line);
					string tmpstuid = line.substr(0, 9);
					if (tmpstuid == studentid) {
						pos = lineCount;
						f2.close();
						cout << "과목 번호 <" << id << "> 삭제 완료";
						return;
					}
				}
			}
		}
		cout << "오류 : 수강 신청 삭제 대상 과목이 없습니다.";
		f1.close();
		return;
	}
}