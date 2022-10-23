#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <algorithm>
#include <filesystem>
#include <locale.h>
#include <atlconv.h>
#include <locale>
#include <codecvt>
#include<utility>
#include "SubjectData.h"
using namespace std;

void Add(string command, string studentid, string studentname) {
	string id;
	string mileage;
	vector<string> adds;
	stringstream ss(command);
	string token;
	string check;
	wstring line;
	vector<pair<int,string>> find_time;
	queue < pair<int,string>> find_times;
	vector<int>found_time;
	vector<string> compare_times;
	int mileage_sum;
	bool c1, c2, c3, c4,c5;
	c1 = c2 = c3 = c4 =c5= true;

	while (getline(ss, token, '/'))
	{
		adds.push_back(token);
	}
	id = adds[0];
	mileage = adds[1];
	// 존재하는 과목인지 체크
	if (Subject[stoi(id)] == NULL) {
		cout << "오류 : 존재하지 않는 과목입니다." << endl;
		if (stoi(mileage) > 36) {
			cout << "오류 : 마일리지 36을 초과해 배팅할 수 없습니다." << endl;
		}
		return;
	}

	int credit_sum = Subject[stoi(id)]->credit;
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

	// 중복체크 하기 전에 사용자 임시 파일이 있는 지 체크
	string filename1 = studentid + '_' + studentname + "_수강신청목록.txt";
	wfstream f1;
	f1.imbue(locale("ko_KR.UTF-8"));
	f1.open(filename1);
	if (f1.is_open()) { // 있으면 읽어온 뒤 과목시간대, 학점 긁어오기
		while (getline(f1, line)) {
			wstring tmpid = line.substr(0, 4);
			wstring tmpmlg = line.substr(4);
			mileage_sum += stoi(tmpmlg);
			if (tmpid == wid) { // 사용자 중복 체크
				c1 = false;
				//cout << "오류 : 이미 추가한 과목입니다"<<endl;
			}
			find_time.push_back(make_pair(stoi(tmpid),Subject[stoi(tmpid)]->time)); // 과목 시간대 저장
			credit_sum += Subject[stoi(tmpid)]->credit;
		}
		f1.close();
	}
	if (credit_sum > 18) {
		//cout << "최대 이수 학점(18학점)을 초과하였습니다.";
		c2 = false;
	}
	// 과목 중복 체크
	ss.clear();
	string compare_time = Subject[stoi(id)]->time;
	ss.str(compare_time);
	while (getline(ss, token, ','))
	{
		compare_times.push_back(token);
	}

	for (int i = 0; i < find_time.size(); i++) {
		ss.clear();
		ss.str(find_time[i].second);
		while (getline(ss, token, ','))
		{
			find_times.push(make_pair(find_time[i].first,token));
		}
	}
	while(!find_times.empty()){
		for (int j = 0; j < compare_times.size(); j++) {
			string now = find_times.front().second;
			//cout << now.substr(0, 2) << " " << compare_times[j].substr(0, 2) << endl;
			if (now.substr(0, 2) == compare_times[j].substr(0, 2)) { // 요일 비교
				int f_left = stoi(now.substr(2, 2));
				int f_right = stoi(now.substr(5, 2));
				int c_left = stoi(compare_times[j].substr(2, 2));
				int c_right = stoi(compare_times[j].substr(5, 2));
				//cout << f_left << " " << f_right << " " << c_left << "  " << c_right << endl;
				if ((f_left >= c_left && f_left < c_right) || (f_right > c_left && f_right <= c_right)) {
					//cout << "오류 : 추가하려는 과목과 강의시간이 겹치는 과목이 이미 추가되었습니다." << endl;
					c3 = false;
					found_time.push_back(find_times.front().first);
				}
			}
		}
		find_times.pop();
	}

	// 마일리지 체크
	if (mileage_sum > 72) {
		//cout << "오류 : 신청한 마일리지가 남은 마일리지를 초과합니다." << endl;
		c4 = false;
	}
	if (stoi(mileage) > 36) {
		//cout << "오류 : 마일리지 36을 초과해 배팅할 수 없습니다." << endl;
		c5 = false;
	}
	if (c1 && c2 && c3 && c4 && c5) {
		// 추가 yes / no 
		string filename2 = id + '_' + subname + "_출석부.txt";
		wofstream f2;
		f2.imbue(locale("ko_KR.UTF-8"));
		f2.open(filename2, ios::app);
		wfstream f3;
		f3.imbue(locale("ko_KR.UTF-8"));
		f3.open(filename1, ios::app);
		cout << "[" << id << "] " << Subject[stoi(id)]->name << " " << stoi(mileage) << "마일리지" << endl;
		cout << "Course Registration > 이대로 추가하시겠습니까? (Yes/...)";
		cin >> check;
		cin.ignore();
		if (check == "Yes") {
			f2 << wstuid + L'\t';
			f2.write(wstuname.c_str(), static_cast<streamsize>(wstuname.length()));
			f2 << L'\t' + wmileage + L'\n';
			f3 << wid + L'\t' + wmileage + L'\n';
			f2.close();
			f3.close();
			cout << "성공적으로 추가되었습니다!" << endl;
			return;
		}
		else return;
	}
	else {
		if(!c1) cout << "오류 : 이미 추가한 과목입니다" << endl;
		if(!c2)cout << "최대 이수 학점(18학점)을 초과하였습니다.";
		if (!c3) {
			sort(found_time.begin(), found_time.end());
			found_time.erase(unique(found_time.begin(), found_time.end()), found_time.end());
			cout << "오류 : 추가하려는 과목과 강의시간이 겹치는 과목이 이미 추가되었습니다." << endl;
			cout << "[" << id << "] " << Subject[stoi(id)]->name << " " << Subject[stoi(id)]->time << endl;
			for (int i = 0; i < found_time.size(); i++) {
				cout << "[" << found_time[i] << "] " << Subject[found_time[i]]->name << " " << Subject[found_time[i]]->time << endl;
			}
		}
		if (!c4)cout << "오류 : 신청한 마일리지가 남은 마일리지를 초과합니다." << endl;
		if (!c5)cout << "오류 : 마일리지 36을 초과해 배팅할 수 없습니다." << endl;
	}
}