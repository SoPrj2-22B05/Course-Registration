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
	vector<string> find_time;
	queue <string> find_times;
	vector<string> compare_times;
	int mileage_sum;

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
	wstring wstuid, wmileage, wid, wsubname;
	wstuid.assign(studentid.begin(), studentid.end());
	wmileage.assign(mileage.begin(), mileage.end());
	wid.assign(id.begin(), id.end());
	string subname = Subject[stoi(id)]->name;
	wsubname.assign(subname.begin(), subname.end());
	USES_CONVERSION;
	wstring wstuname(A2W(studentname.c_str()));

	// �����ϴ� �������� üũ
	if (Subject[stoi(id)] == NULL) {
		cout << "���� : �������� �ʴ� �����Դϴ�." << endl;
		return;
	}

	// �ߺ�üũ �ϱ� ���� ����� �ӽ� ������ �ִ� �� üũ
	string filename1 = studentid + '_' + studentname + "_������û���.txt";
	wfstream f1;
	f1.imbue(locale("ko_KR.UTF-8"));
	f1.open(filename1);
	if (f1.is_open()) { // ������ �о�� �� ����ð��� �ܾ����
		while (getline(f1, line)) {
			wstring tmpid = line.substr(0, 4);
			wstring tmpmlg = line.substr(4);
			mileage_sum += stoi(tmpmlg);
			if (tmpid == wid) { // ����� �ߺ� üũ
				cout << "���� : �̹� �߰��� �����Դϴ�"<<endl;
				return;
			}
			find_time.push_back(Subject[stoi(tmpid)]->time); // ���� �ð��� ����
		}
		f1.close();
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
		ss.str(find_time[i]);
		while (getline(ss, token, ','))
		{
			find_times.push(token);
		}
		for (int i = 0; i < compare_times.size(); i++) {
			//cout << find_times.front().substr(0, 2) << " " << compare_times[i].substr(0, 2) << endl;
			if (find_times.front().substr(0, 2) == compare_times[i].substr(0, 2)) { // ���� ��
				int f_left = stoi(find_time[i].substr(2, 2));
				int f_right = stoi(find_time[i].substr(5, 2));
				int c_left = stoi(compare_times[i].substr(2, 2));
				int c_right = stoi(compare_times[i].substr(5, 2));
				if ((f_left >= c_left && f_left < c_right) || (f_right > c_left && f_right <= c_right)) {
					cout << "���� : �߰��Ϸ��� ����� ���ǽð��� ��ġ�� ������ �̹� �߰��Ǿ����ϴ�." << endl;
					return;
				}
			}
		}
		find_times.pop();
	}

	// ���ϸ��� üũ
	if (mileage_sum > 72) {
		cout << "���� : ��û�� ���ϸ����� ���� ���ϸ����� �ʰ��մϴ�." << endl;
		return;
	}
	if (stoi(mileage) > 36) {
		cout << "���� : ���ϸ��� 36�� �ʰ��� ������ �� �����ϴ�." << endl;
		return;
	}
	// �߰� yes / no 
	string filename2 = id + '_' + subname + "_�⼮��.txt" ;
	wofstream f2;
	f2.imbue(locale("ko_KR.UTF-8"));
	f2.open(filename2, ios::app);
	wfstream f3;
	f3.imbue(locale("ko_KR.UTF-8"));
	f3.open(filename1, ios::app);
	cout << "�̴�� �߰��Ͻðڽ��ϱ�? (Yes/...)";
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