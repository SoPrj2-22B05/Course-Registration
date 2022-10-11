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
	string studentname = "������";
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

	// �����ϴ� �������� üũ
	if (Subject[stoi(id)] == NULL) {
		cout << "���� : �������� �ʴ� �����Դϴ�.";
		return;
	}

	fstream f1(studentid + "_" + studentname + "_������û���.txt", ios::in | ios::out);
	if (f1.is_open()) { 
		while (f1.peek() != EOF) {
			getline(f1, line);
			string tmpid = line.substr(0, 4);
			string tmpmlg = line.substr(4);
			mileage_sum += stoi(tmpmlg);
			if (tmpid == id) { // ����� ���Ͽ� ����
				mileage_sum -= stoi(tmpmlg);
				// ���ϸ��� üũ�� �߰��� �ؾ��ҵ�!
				if (mileage_sum > 72) {
					cout << "���� : ��û�� ���ϸ����� ���� ���ϸ����� �ʰ��մϴ�.";
					return;
				}
				if (stoi(mileage) > 36) {
					cout << "���� : ���ϸ��� 36�� �ʰ��� ������ �� �����ϴ�.";
					return;
				}
				find_id = true;
				cout << "���� �����Ͻðڽ��ϱ�? (yes/no)";
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
		cout << "���� : ���� ��û���� ���� �����Դϴ�.";
		return;
	}
	fstream f2(id + "_" + Subject[stoi(id)]->name + "_�⼮��.txt", ios::in | ios::out);
	if (f2.is_open()) {
		while (f2.peek() != EOF) {
			getline(f2, line);
			string tmpstuid = line.substr(0, 9);
			if (tmpstuid == studentid) { // ���� ���� ��ġ ã��
				f2.seekg(-21, ios::cur); // �̸��� ���� ����Ʈ �� �ٸ��ٵ�...
				f2 << studentid + "\t" + studentname + "\t" + mileage;
				break;
			}
		}
		f2.close();
	}
}