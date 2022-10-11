#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <algorithm>
#include "SubjectData.h"
using namespace std;

void Alter(string command) {
	string studentid = "202111312";
	string studentname = "송현우";
	string id;
	string mileage;
	vector<string> adds;
	stringstream ss(command);
	string token;
	string check;
	string line;
	int mileage_sum;
	bool find_id;

	while (getline(ss, token, '/'))
	{
		adds.push_back(token);
	}
	id = adds[0];
	mileage = adds[1];
	if (mileage.size() == 1) {
		mileage = "0" + mileage;
	}
	mileage_sum = stoi(mileage);

	// 존재하는 과목인지 체크
	if (Subject[stoi(id)] == NULL) {
		cout << "오류 : 존재하지 않는 과목입니다.";
		return;
	}

	fstream f1(studentid + "_" + studentname + "_수강신청목록.txt", ios::in | ios::out);
	if (f1.is_open()) { 
		while (f1.peek() != EOF) {
			getline(f1, line);
			string tmpid = line.substr(0, 4);
			string tmpmlg = line.substr(4);
			mileage_sum += stoi(tmpmlg);
			if (tmpid == id) { // 사용자 파일에 존재
				mileage_sum -= stoi(tmpmlg);
				// 마일리지 체크는 중간에 해야할듯!
				if (mileage_sum > 72) {
					cout << "오류 : 신청한 마일리지가 남은 마일리지를 초과합니다.";
					return;
				}
				if (stoi(mileage) > 36) {
					cout << "오류 : 마일리지 36을 초과해 배팅할 수 없습니다.";
					return;
				}
				find_id = true;
				cout << "정말 변경하시겠습니까? (yes/no)";
				cin >> check;
				if (check == "yes") {
					f1.seekg(-9, ios::cur);
					f1 << id + "\t" + mileage;
				}
				else return;
				break;
			}
		}
		f1.close();
	}
	if (!find_id) {
		cout << "오류 : 수강 신청하지 않은 과목입니다.";
		return;
	}
	fstream f2(id + "_" + Subject[stoi(id)]->name + "_출석부.txt", ios::in | ios::out);
	if (f2.is_open()) {
		while (f2.peek() != EOF) {
			getline(f2, line);
			string tmpstuid = line.substr(0, 9);
			if (tmpstuid == studentid) { // 과목 파일 위치 찾기
				f2.seekg(-21, ios::cur); // 이름에 따라 바이트 수 다를텐데...
				f2 << studentid + "\t" + studentname + "\t" + mileage;
				break;
			}
		}
		f2.close();
	}
}