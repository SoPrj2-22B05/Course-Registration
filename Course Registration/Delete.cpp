#include <filesystem>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <algorithm>
#include <locale.h>
#include <codecvt>
#include "SubjectData.h"
using namespace std;

void Delete(string command, string studentid, string studentname) {
	string id = command;
	wstring line;
	bool check = false;
	int pos=-1;
	int back = 36 + studentname.length();
	int lineCount = 0;
	vector<wstring>lines;

	wstring wstuid, wid;
	wstuid.assign(studentid.begin(), studentid.end());
	wid.assign(id.begin(), id.end());
	string subname = Subject[stoi(id)]->name;

	string filename1 = studentid + '_' + studentname + "_수강신청목록.txt";
	wfstream f1;
	f1.imbue(locale("ko_KR.UTF-8"));
	f1.open(filename1);
	if (f1.is_open()) {
		while (getline(f1, line)) {
			lines.push_back(line);
			wstring tmpid = line.substr(0, 4);
			if (tmpid == wid) {
				check = true;
				pos = lineCount;
			}
			lineCount++;
		}
		f1.close();
		check = false;
		lineCount = 0;
	}
	if (pos == -1) {
		cout << "오류 : 수강 신청 삭제 대상 과목이 없습니다." << endl;
		return;
	}
	cout << "정말 삭제하시겠습니까? (Yes/...)";
	string dcheck;
	cin >> dcheck;
	cin.ignore();
	if (dcheck == "Yes") {
		remove(filename1.c_str());
	}
	else return;

	wofstream f3;
	f3.imbue(locale("ko_KR.UTF-8"));
	f3.open(filename1,ios::app);
	if (f3.is_open()) {
		for (int i = 0; i < lines.size(); i++) {
			if (i == pos)continue;
			else f3 << lines[i] << L'\n';
		}
		f3.close();
	}

	lines.clear();
	vector<wstring>().swap(lines);

	string filename2 = id + '_' + subname + "_출석부.txt";
	wfstream f2;
	f2.imbue(locale("ko_KR.UTF-8"));
	f2.open(filename2);
	if (f2.is_open()) {
		while (getline(f2, line)) {
			lines.push_back(line);
			wstring tmpstuid = line.substr(0, 9);
			if (tmpstuid == wstuid) {
				check = true;
				pos = lineCount;
			}
			lineCount++;
		}
		f2.close();
		check = false;
		lineCount = 0;
	}
	remove(filename2.c_str());

	if (lines.size()>1) {
		wofstream f4;
		f4.imbue(locale("ko_KR.UTF-8"));
		f4.open(filename2, ios::app);
		if (f4.is_open()) {
			for (int i = 0; i < lines.size(); i++) {
				if (i == pos)continue;
				else f4 << lines[i] << L'\n';
			}
			f4.close();
		}
	}
	cout << "성공적으로 삭제되었습니다." << endl;
	return;
}