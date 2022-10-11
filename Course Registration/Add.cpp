#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <algorithm>
#include "SubjectData.h"
using namespace std;

void Add(string command) {
	string studentid = "202111312";
	string studentname = "������";
	string id;
	string mileage;
	vector<string> adds;
	stringstream ss(command);
	string token;
	string check;
	string line;
	vector<string> find_time;
	queue<string> find_times;
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

	// �����ϴ� �������� üũ
	
	if (Subject[stoi(id)]==NULL) {
		cout << "���� : �������� �ʴ� �����Դϴ�.";
		return;
	}

	// �ߺ�üũ �ϱ� ���� ����� �ӽ� ������ �ִ� �� üũ
	ifstream f1(studentid + "_" + studentname + "_������û���.txt");
	if (f1.is_open()) { // ������ �о�� �� ����ð��� �ܾ����
		while (f1.peek()!=EOF) {
			getline(f1, line);
			string tmpid = line.substr(0, 4);
			string tmpmlg = line.substr(4);
			mileage_sum += stoi(tmpmlg);
			if (tmpid == id) { // ����� �ߺ� üũ
				cout << "���� : �̹� �߰��� �����Դϴ�";
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
			if (find_times.front().substr(0,2) == compare_times[i].substr(0,2)) { // ���� ��
				int f_left = stoi(find_time[i].substr(2, 2));
				int f_right = stoi(find_time[i].substr(5, 2));
				int c_left = stoi(compare_times[i].substr(2, 2));
				int c_right = stoi(compare_times[i].substr(5, 2));
				if ((f_left >= c_left && f_left<c_right) || (f_right>c_left && f_right <= c_right)) {
					cout << "���� : �߰��Ϸ��� ����� ���ǽð��� ��ġ�� ������ �̹� �߰��Ǿ����ϴ�.";
					return;
				}
			}
		}
		find_times.pop();
	}

	// ���ϸ��� üũ
	if (mileage_sum > 72) {
		cout << "���� : ��û�� ���ϸ����� ���� ���ϸ����� �ʰ��մϴ�.";
		return;
	}
	if (stoi(mileage) > 36) {
		cout << "���� : ���ϸ��� 36�� �ʰ��� ������ �� �����ϴ�.";
		return;
	}

	// �߰� yes / no 
	ofstream f2;
	f2.open(id + "_" + Subject[stoi(id)]->name + "_�⼮��.txt", ios::app);
	ofstream f3;
	f3.open(studentid + "_" + studentname + "_������û���.txt", ios::app);
	cout << "���� �߰��Ͻðڽ��ϱ�? (yes/no)";
	cin >> check;
	if (check == "yes") {
		f2 << studentid + "\t" + studentname + "\t" + mileage + "\n";
		f3 << id + "\t" + mileage + "\n";
		f2.close();
		f3.close();
		return;
	}
	else return;
}