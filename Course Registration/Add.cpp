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

string wtos(const wstring& _src) {
	USES_CONVERSION;
	return string(W2A(_src.c_str()));
};

void Add(string command, string studentid, string studentname) {
	string id;
	string mileage;
	vector<string> adds;
	stringstream ss(command);
	string token;
	string check;
	wstring line;
	vector<pair<string, string>> find_time;
	queue < pair<string, string>> find_times;
	vector<string>found_time;
	vector<string> compare_times;
	int mileage_sum;
	bool c1, c2, c3, c4, c5,c6;
	c1 = c2 = c3 = c4 = c5 = true;

	while (getline(ss, token, '/'))
	{
		adds.push_back(token);
	}
	id = adds[0];
	mileage = adds[1];
	// �����ϴ� �������� üũ
	if (Subject[stoi(id)] == NULL) {
		cout << "���� : �������� �ʴ� �����Դϴ�." << endl;
		if (stoi(mileage) > 36) {
			cout << "���� : ���ϸ��� 36�� �ʰ��� ������ �� �����ϴ�." << endl;
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

	// �ߺ�üũ �ϱ� ���� ����� �ӽ� ������ �ִ� �� üũ
	string filename1 = studentid + '_' + studentname + "_������û���.txt";
	wfstream f1;
	f1.imbue(locale("ko_KR.UTF-8"));
	f1.open(filename1);
	if (f1.is_open()) { // ������ �о�� �� ����ð���, ���� �ܾ����
		while (getline(f1, line)) {
			wstring tmpid = line.substr(0, 4);
			wstring tmpmlg = line.substr(4);
			mileage_sum += stoi(tmpmlg);
			if (tmpid == wid) c1 = false; // �ߺ�üũ
			if (Subject[stoi(tmpid)]->name == Subject[stoi(wid)]->name) c6 = false; // �й� üũ
			find_time.push_back(make_pair(wtos(tmpid), Subject[stoi(tmpid)]->time)); // ���� �ð��� ����
			credit_sum += Subject[stoi(tmpid)]->credit;
		}
		f1.close();
	}
	if (credit_sum > 18) {
		//cout << "�ִ� �̼� ����(18����)�� �ʰ��Ͽ����ϴ�.";
		c2 = false;
	}
	// ���� �ߺ� üũ
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
			find_times.push(make_pair(find_time[i].first, token));
		}
	}
	while (!find_times.empty()) {
		for (int j = 0; j < compare_times.size(); j++) {
			string now = find_times.front().second;
			//cout << now.substr(0, 2) << " " << compare_times[j].substr(0, 2) << endl;
			if (now.substr(0, 2) == compare_times[j].substr(0, 2)) { // ���� ��
				int f_left = stoi(now.substr(2, 2));
				int f_right = stoi(now.substr(5, 2));
				int c_left = stoi(compare_times[j].substr(2, 2));
				int c_right = stoi(compare_times[j].substr(5, 2));
				/*cout << f_left << " " << f_right << " " << c_left << "  " << c_right << endl;
				cout << (f_left >= c_left && f_left < c_right) << (f_right > c_left && f_right <= c_right)<<
					(f_left <= c_left && f_right >= c_right)<< (f_left >= c_left && f_left <= c_right && f_right >= c_left && f_right <= c_right) << endl;*/
				if ((c_left>=f_left&&c_left<f_right)||(c_right>f_left&&c_right<=f_right)||(c_left<=f_left&&c_right>=f_right)) {
					//cout << "���� : �߰��Ϸ��� ����� ���ǽð��� ��ġ�� ������ �̹� �߰��Ǿ����ϴ�." << endl;
					c3 = false;
					found_time.push_back(find_times.front().first);
				}
			}
		}
		find_times.pop();
	}

	// ���ϸ��� üũ
	if (mileage_sum > 72) {
		//cout << "���� : ��û�� ���ϸ����� ���� ���ϸ����� �ʰ��մϴ�." << endl;
		c4 = false;
	}
	if (stoi(mileage) > 36) {
		//cout << "���� : ���ϸ��� 36�� �ʰ��� ������ �� �����ϴ�." << endl;
		c5 = false;
	}
	if (c1 && c2 && c3 && c4 && c5) {
		// �߰� yes / no 
		string filename2 = id + '_' + subname + "_�⼮��.txt";
		wofstream f2;
		f2.imbue(locale("ko_KR.UTF-8"));
		f2.open(filename2, ios::app);
		wfstream f3;
		f3.imbue(locale("ko_KR.UTF-8"));
		f3.open(filename1, ios::app);
		cout << "[" << id << "] " << Subject[stoi(id)]->name << " " << stoi(mileage) << "���ϸ���" << endl;
		cout << "Course Registration > �̴�� �߰��Ͻðڽ��ϱ�? (Yes/...)";
		cin >> check;
		cin.ignore();
		if (check == "Yes") {
			f2 << wstuid + L'\t';
			f2.write(wstuname.c_str(), static_cast<streamsize>(wstuname.length()));
			f2 << L'\t' + wmileage + L'\n';
			f3 << wid + L'\t' + wmileage + L'\n';
			f2.close();
			f3.close();
			cout << "���������� �߰��Ǿ����ϴ�!" << endl;
			return;
		}
		else return;
	}
	else {
		if (!c1) cout << "���� : �̹� �߰��� �����Դϴ�" << endl;
		if (!c6) cout << "���� : �̹� �߰��� ������ �й��Դϴ�" << endl;
		if (!c2)cout << "�ִ� �̼� ����(18����)�� �ʰ��Ͽ����ϴ�.";
		if (c1 && !c3) {
			sort(found_time.begin(), found_time.end());
			found_time.erase(unique(found_time.begin(), found_time.end()), found_time.end());
			cout << "���� : �߰��Ϸ��� ����� ���ǽð��� ��ġ�� ������ �̹� �߰��Ǿ����ϴ�." << endl;
			cout << "[" << id << "] " << Subject[stoi(id)]->name << " " << Subject[stoi(id)]->time << endl;
			for (int i = 0; i < found_time.size(); i++) {
				cout << "[" << found_time[i] << "] " << Subject[stoi(found_time[i])]->name << " " << Subject[stoi(found_time[i])]->time << endl;
			}
		}
		if (!c4)cout << "���� : ��û�� ���ϸ����� ���� ���ϸ����� �ʰ��մϴ�." << endl;
		if (!c5)cout << "���� : ���ϸ��� 36�� �ʰ��� ������ �� �����ϴ�." << endl;
	}
}