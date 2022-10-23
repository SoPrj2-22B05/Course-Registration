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

	// �����ϴ� �������� üũ
	if (Subject[stoi(id)] == NULL) {
		cout << "���� : �������� �ʴ� �����Դϴ�." << endl;
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

	// ���ϸ��� ����
	if (stoi(mileage) > 36) {
		cout << "���� : ���ϸ��� 36�� �ʰ��� ������ �� �����ϴ�." << endl;
		return;
	}

	// ���ϸ��� ���� ����
	string filename1 = studentid + '_' + studentname + "_������û���.txt";
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
		cout << "�ִ� �̼� ����(18����)�� �ʰ��Ͽ����ϴ�.";
		return;
	}

	f1.open(filename1);
	if (f1.is_open()) {
		while (getline(f1, line)) {
			wstring tmpid = line.substr(0, 4);
			wstring tmpmlg = line.substr(4);
			if (tmpid == wid) { // ����� ���Ͽ� ����
				mileage_sum -= stoi(tmpmlg);
				if (mileage_sum > 72) {
					cout << "���� : ��û�� ���ϸ����� ���� ���ϸ����� �ʰ��մϴ�." << endl;
					return;
				}
				find_id = true;
				cout << "[" << id << "] " << Subject[stoi(id)]->name << " " << stoi(tmpmlg) << "->" << mileage << "���ϸ����� ����" << endl;
				cout << "�̴�� �����Ͻðڽ��ϱ�? (Yes/...)";
				cin >> check;
				cin.ignore();
				if (check == "Yes") {
					cout << "���������� ����Ǿ����ϴ�!" << endl;
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
		cout << "���� : ���� ��û���� ���� �����Դϴ�." << endl;
		return;
	}
	string filename2 = id + '_' + subname + "_�⼮��.txt" ;
	wfstream f2;
	f2.imbue(locale("ko_KR.UTF-8"));
	f2.open(filename2);
	if (f2.is_open()) {
		while (getline(f2, line)) {
			wstring tmpstuid = line.substr(0, 9);
			if (tmpstuid == wstuid) { // ���� ���� ��ġ ã��
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