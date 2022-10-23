#include "SubjectData.h"
#include <iostream>
#include <filesystem>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <algorithm>
#include <locale.h>
#include <atlconv.h>
#include <locale>
#include <codecvt>
using namespace std;

void Alter(string command, string studentid, string studentname) {
	string id;
	string mileage;
	vector<string> adds;
	stringstream ss(command);
	string token;
	string check;
	wstring line;
	int mileage_sum;
	int find_mileage;
	bool find_id=false;
	int back = 18 + studentname.length();
	int credit_sum = Subject[stoi(id)]->credit;

	while (getline(ss, token, '/'))
	{
		adds.push_back(token);
	}
	id = adds[0];

	// 존재하는 과목인지 체크
	if (Subject[stoi(id)] == NULL) {
		cout << "오류 : 존재하지 않는 과목입니다." << endl;
		return;
	}

	mileage = adds[1];
	if (mileage.size() == 1) {
		mileage = "0" + mileage;
	}
	mileage_sum = stoi(mileage);

	wstring wstuid, wmileage, wid, wsubname;
	wstuid.assign(studentid.begin(), studentid.end());
	wmileage.assign(mileage.begin(), mileage.end());
	wid.assign(id.begin(), id.end());
	string subname = Subject[stoi(id)]->name;
	wsubname.assign(subname.begin(), subname.end());
	USES_CONVERSION;
	wstring wstuname(A2W(studentname.c_str()));

	// 마일리지 오류
	if (stoi(mileage) > 36) {
		cout << "오류 : 마일리지 36을 초과해 배팅할 수 없습니다." << endl;
		return;
	}

	// 마일리지 저장 과정
	string filename1 = studentid + '_' + studentname + "_수강신청목록.txt";
	wfstream f1;
	f1.imbue(locale("ko_KR.UTF-8"));
	f1.open(filename1);
	if (f1.is_open()) {
		while (getline(f1, line)) {
			wstring tmpid = line.substr(0, 4);
			wstring tmpmlg = line.substr(4);
			mileage_sum += stoi(tmpmlg);
			credit_sum += Subject[stoi(tmpid)]->credit;
		}
		f1.close();
	}

	if (credit_sum > 18) {
		cout << "최대 이수 학점(18학점)을 초과하였습니다.";
		return;
	}

	f1.open(filename1);
	if (f1.is_open()) {
		while (getline(f1, line)) {
			wstring tmpid = line.substr(0, 4);
			wstring tmpmlg = line.substr(4);
			if (tmpid == wid) { // 사용자 파일에 존재
				mileage_sum -= stoi(tmpmlg);
				if (mileage_sum > 72) {
					cout << "오류 : 신청한 마일리지가 남은 마일리지를 초과합니다." << endl;
					return;
				}
				find_id = true;
				cout << "[" << id << "] " << Subject[stoi(id)]->name << " " << stoi(tmpmlg) << "->" << mileage << "마일리지로 변경" << endl;
				cout << "이대로 변경하시겠습니까? (Yes/...)";
				cin >> check;
				cin.ignore();
				if (check == "Yes") {
					cout << "성공적으로 변경되었습니다!" << endl;
					f1.seekg(-9, ios::cur);
					f1 << wid + L'\t' + wmileage + L'\n';
					f1.seekg(9, ios::cur);
				}
				else return;
				break;
			}
		}
		f1.close();
	}
	if (!find_id) {
		cout << "오류 : 수강 신청하지 않은 과목입니다." << endl;
		return;
	}
	string filename2 = id + '_' + subname + "_출석부.txt" ;
	wfstream f2;
	f2.imbue(locale("ko_KR.UTF-8"));
	f2.open(filename2);
	if (f2.is_open()) {
		while (getline(f2, line)) {
			wstring tmpstuid = line.substr(0, 9);
			if (tmpstuid == wstuid) { // 과목 파일 위치 찾기
				f2.seekg(-back, ios::cur);
				f2 << wstuid + L'\t';
				f2.write(wstuname.c_str(), static_cast<streamsize>(wstuname.length()));
				f2 << L'\t' + wmileage + L'\n';
				f2.seekg(back, ios::cur);
				break;
			}
		}
		f2.close();
	}
	cin.ignore();
	return;
}