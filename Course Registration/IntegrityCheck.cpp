#pragma once
#include "IntegrityCheck.h"
#include "SubjectData.h"
#include <filesystem>
#include <iostream>
#include <fstream>
#include <locale.h>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <regex>
#include <atlconv.h>

#define gotoUTF locale::global(locale("ko_KR.UTF-8"));
#define gotoClassic locale::global(locale::classic());

using namespace std;

SubjectData* Subject[10000];

vector<int> Subject_File_Grammar_Error_Line;
vector<int> User_File_Grammar_Error_Line;

bool is_unmatched_major_grade = false;
vector<int> zero_major_lines;
vector<int> nonzero_liberal_arts_lines;
bool is_duplicated_SID = false;
map<wstring, vector<int>> SIDs; // <�����ȣ, �ش��ϴ� ���>

int admin_count = 0;
bool is_duplicated_UID = false;
map<wstring, vector<int>> UIDs; // <�й�(����), �ش��ϴ� ���>

bool is_duplicated_time_prof;	// ��米�� - ���ǽð� �ߺ� üũ (�߰� ���� ���� �߰�)
bool is_duplicated_time_room;	// ���ǽ� - ���ǽð� �ߺ� üũ (�߰� ���� ���� �߰�)
map<wstring, vector<int>(*)[22][7]> profTimeTable;	//��米�� map (�߰� ���� ���� �߰�)
map<wstring, vector<int>(*)[22][7]> roomTimeTable;	//���ǽ� map (�߰� ���� ���� �߰�)

void check_File_Exist();
void check_Subject_File();
void check_User_File();
void print_Errors();

bool check_SID(wstring const& str);
bool check_Sname(wstring const& str);
bool check_Scredit(wstring const& str);
bool check_Smajor(wstring const& str);
bool check_Sgrade(wstring const& str);
bool check_Stime(wstring const& str);
bool check_Scapacity(wstring const& str);
bool check_Smajor_Sgrade_Match(wstring const& smajor, wstring const& sgrade, int line);
bool check_Sprof(wstring const& str);
bool check_Sroom(wstring const& str);

bool check_UID(wstring const& str);
bool check_Uname(wstring const& str);
bool check_Umajor(wstring const& str);
bool check_Ugrade(wstring const& str);
bool check_Acquisition_Credit(wstring const& str);

string wstr2str(const std::wstring& _src);
wstring& trim(wstring& s, const wchar_t* t = L" \t\n\r\f\v");

void save_Sprof_Sroom_Stime(wstring const& sprof, wstring const& sroom, wstring const& time, int line);
void print_Sprof_Stime_redundancy();
void print_Sroom_Stime_redundancy();



void Integrity_Check() {
	check_File_Exist();
	check_Subject_File();
	check_User_File();
	print_Errors();
}

void check_File_Exist() {
	gotoUTF;
	wstring dir = filesystem::current_path();
	wfstream f1(L"���� ������ ����.txt");
	wfstream f2(L"����� ������ ����.txt");
	if (!f1.is_open() || !f2.is_open()) {
		wcout << L"���� : Ȩ ��� " << dir << L" �� ���� ������ ���� �Ǵ� ����� ������ ������ �����ϴ�.���α׷��� �����մϴ�." << endl;
		system("pause");
		exit(0);
	}
	f1.close();
	f2.close();
}

void check_Subject_File() {
	gotoUTF;
	wfstream f(L"���� ������ ����.txt");

	vector<wstring> data; // id  name  credit  major  grade  time  capacity
	wstring line, str;
	wstringstream ss;

	int lineCount = 0;
	while (getline(f, line)) {
		lineCount++;
		data.clear();
		ss.clear();

		// ����ִ� ������ üũ
		line = trim(line);
		if (line.compare(L"") == 0) {
			Subject_File_Grammar_Error_Line.push_back(lineCount);
			continue;
		}

		ss.str(line);
		while (getline(ss, str, L'\t')) {
			str = trim(str);
			if (str != L"") {
				data.push_back(str);
			}
		}

		if (data.size() != 9) { // ��� 9������ üũ
			Subject_File_Grammar_Error_Line.push_back(lineCount);
			continue;
		}

		if (!check_SID(data[0])) { // �����ȣ ���� ���� üũ
			Subject_File_Grammar_Error_Line.push_back(lineCount);
			continue;
		}
		else {
			if (SIDs.find(data[0]) != SIDs.end()) { // �����ȣ �ߺ� üũ
				is_duplicated_SID = true;
			}
			SIDs[data[0]].push_back(lineCount);
		}

		if (!check_Sname(data[1])) { // �����̸� üũ
			Subject_File_Grammar_Error_Line.push_back(lineCount);
			continue;
		}
		if (!check_Scredit(data[2])) { // ���� üũ
			Subject_File_Grammar_Error_Line.push_back(lineCount);
			continue;
		}
		if (!check_Smajor(data[3])) { // ����/���� üũ
			Subject_File_Grammar_Error_Line.push_back(lineCount);
			continue;
		}
		if (!check_Sgrade(data[4])) { // �г� üũ
			Subject_File_Grammar_Error_Line.push_back(lineCount);
			continue;
		}
		if (!check_Stime(data[5])) { // ���ǽð� üũ
			Subject_File_Grammar_Error_Line.push_back(lineCount);
			continue;
		}
		if (!check_Scapacity(data[6])) { // ���� üũ
			Subject_File_Grammar_Error_Line.push_back(lineCount);
			continue;
		}
		if (!check_Smajor_Sgrade_Match(data[3], data[4],lineCount)) { // ����/���� - �г� ��Ī üũ
			is_unmatched_major_grade = true;
		}
		if (!check_Sprof(data[7])) { // ��米�� üũ
			Subject_File_Grammar_Error_Line.push_back(lineCount);
			continue;
		}
		if (!check_Sroom(data[8])) { // ���ǽ� üũ
			Subject_File_Grammar_Error_Line.push_back(lineCount);
			continue;
		}
		save_Sprof_Sroom_Stime(data[7], data[8], data[5], lineCount);

		//for (int i = 0; i < data.size(); i++) {
		//	wcout << data[i] + L" + ";
		//}
		//cout << endl;

		// ������ �迭�� �߰�
		SubjectData* tmp = new SubjectData();
		tmp->id = wstr2str(data[0]);
		tmp->name = wstr2str(data[1]);
		tmp->credit = stoi(data[2]);
		tmp->major = wstr2str(data[3]);
		tmp->grade = stoi(data[4]);
		tmp->time = wstr2str(data[5]);
		tmp->max = stoi(data[6]);

		Subject[stoi(data[0])] = tmp;
	}
	gotoClassic;
}

void check_User_File() {
	gotoUTF;
	wfstream f(L"����� ������ ����.txt");

	vector<wstring> data; // id  name  major  grade  acquisition_credit
	wstring line, str;
	wstringstream ss;

	int lineCount = 0;
	while (getline(f, line)) {
		lineCount++;
		data.clear();
		ss.clear();

		// ����ִ� ������ üũ
		line = trim(line);
		if (line.compare(L"") == 0) {
			User_File_Grammar_Error_Line.push_back(lineCount);
			continue;
		}

		ss.str(line);
		while (getline(ss, str, L'\t')) {
			str = trim(str);
			if (str != L"") {
				data.push_back(str);
			}
		}

		if (!check_UID(data[0])) { // �й�(����) ���� ���� üũ
			User_File_Grammar_Error_Line.push_back(lineCount);
			continue;
		}
		else {
			if (UIDs.find(data[0]) != UIDs.end()) { // �й�(����) �ߺ� üũ
				is_duplicated_UID = true;
			}
			UIDs[data[0]].push_back(lineCount);
		}

		if (data[0].substr(0, 4).compare(L"0000") == 0) { // �������� ���
			if (data.size() != 2) { // ��� 2������ üũ
				User_File_Grammar_Error_Line.push_back(lineCount);
				continue;
			}
			else {
				if (!check_Uname(data[1])) { // �̸� üũ
					User_File_Grammar_Error_Line.push_back(lineCount);
					continue;
				}
				admin_count++; // ������ �� ī��Ʈ
			}
		}
		else { // �л��� ���
			if (data.size() != 5) { // ��� 5������ üũ
				User_File_Grammar_Error_Line.push_back(lineCount);
				continue;
			}
			else {
				if (!check_Uname(data[1])) { // �̸� üũ
					User_File_Grammar_Error_Line.push_back(lineCount);
					continue;
				}
				if (!check_Umajor(data[2])) { // ���� üũ
					User_File_Grammar_Error_Line.push_back(lineCount);
					continue;
				}
				if (!check_Ugrade(data[3])) { // �г� üũ
					User_File_Grammar_Error_Line.push_back(lineCount);
					continue;
				}
				if (!check_Acquisition_Credit(data[4])) { // ������� üũ
					User_File_Grammar_Error_Line.push_back(lineCount);
					continue;
				}
			}
		}

		//for (int i = 0; i < data.size(); i++) {
		//	wcout << data[i] + L" + ";
		//}
		//cout << endl;
	}
	gotoClassic;
}

void print_Errors() {
	bool has_Error = false;

	// ���� ������ ���� ����
	int num_G_error = Subject_File_Grammar_Error_Line.size();
	if (num_G_error != 0) { // ���� ���� �ִ� ���
		has_Error = true;
		printf("���� : ���� ������ ������ ���� ��Ģ�� �ùٸ��� �ʽ��ϴ�.\n# ");
		for (int i = 0; i < num_G_error; i++) {
			printf("%d��", Subject_File_Grammar_Error_Line[i]);
			(i == num_G_error - 1) ? printf("\n") : printf(",");
		}
	}
	else if (is_duplicated_SID || is_unmatched_major_grade || is_duplicated_time_prof || is_duplicated_time_room) { // �ǹ� ���� �ִ� ���
		has_Error = true;
		printf("���� : ���� ������ ������ �ǹ� ��Ģ�� �ùٸ��� �ʽ��ϴ�.\n");

		//��ġ�� �����ȣ ������ ���
		for (auto it : SIDs) {
			if (it.second.size() != 1) {
				wcout << "\"" << it.first << "\"" << "�����ȣ�� �ߺ��ؼ� �����մϴ�.\n# ";
				for (int i = 0; i < it.second.size(); i++) {
					printf("%d��", it.second[i]);
					(i == it.second.size() - 1) ? printf("\n") : printf(",");
				}
			}
		}

		// �����ε� �г��� 0�� �ƴ� �� ������ ���
		int error_size = nonzero_liberal_arts_lines.size();
		if (error_size != 0) {
			printf("����/������ \"����\"�ε� �г��� 0�� �ƴ� ���� �����մϴ�.\n# ");
			for (int i = 0; i < error_size; i++) {
				printf("%d��", nonzero_liberal_arts_lines[i]);
				(i == error_size - 1) ? printf("\n") : printf(",");
			}
		}

		// ������ �ƴѵ� �г��� 0�� �� ������ ���
		error_size = zero_major_lines.size();
		if (error_size != 0) {
			printf("����/������ \"����\"�� �ƴѵ� �г��� 0�� ���� �����մϴ�.\n# ");
			for (int i = 0; i < error_size; i++) {
				printf("%d��", zero_major_lines[i]);
				(i == error_size - 1) ? printf("\n") : printf(",");
			}
		}

		// ��米�� �ð�ǥ �ߺ� ������ ���
		if (is_duplicated_time_prof) {
			print_Sprof_Stime_redundancy();
		}

		// ���ǽ� �ð�ǥ �ߺ� ������ ���
		if (is_duplicated_time_room) {
			print_Sroom_Stime_redundancy();
		}
	}

	// ����� ������ ���� ����
	num_G_error = User_File_Grammar_Error_Line.size();
	if (num_G_error != 0) { // ���� ���� �ִ� ���
		has_Error = true;
		printf("���� : ����� ������ ������ ���� ��Ģ�� �ùٸ��� �ʽ��ϴ�.\n# ");
		for (int i = 0; i < num_G_error; i++) {
			printf("%d��", User_File_Grammar_Error_Line[i]);
			(i == num_G_error - 1) ? printf("\n") : printf(",");
		}
	}
	else if (is_duplicated_UID || admin_count == 0) { // �ǹ� ���� �ִ� ���
		has_Error = true;
		printf("���� : ����� ������ ������ �ǹ� ��Ģ�� �ùٸ��� �ʽ��ϴ�.\n");

		// ��ġ�� �й�(����) ������ ���
		for (auto it : UIDs) {
			if (it.second.size() != 1) {
				wcout << "\"" << it.first << "\"";

				if (it.first.substr(0, 4).compare(L"0000") == 0) {
					printf("������ �ߺ��ؼ� �����մϴ�.\n# ");
				}
				else {
					printf("�й��� �ߺ��ؼ� �����մϴ�.\n# ");
				}

				for (int i = 0; i < it.second.size(); i++) {
					printf("%d��", it.second[i]);
					(i == it.second.size() - 1) ? printf("\n") : printf(",");
				}
			}
		}

		// ������ ������ ���
		if (admin_count == 0) {
			printf("�����ڰ� �� �� �������� �ʽ��ϴ�.\n");
		}
	}

	//map�� value�� ���� �����Ҵ� ����
	/*
	for (auto it = profTimeTable.begin(); it != profTimeTable.end(); it++) {
		delete[] it->second;
	}
	for (auto it = roomTimeTable.begin(); it != roomTimeTable.end(); it++) {
		delete[] it->second;
	}
	*/

	if (has_Error) {
		cout << "���α׷��� �����մϴ�." << endl;
		system("pause");
		exit(0);
	}
}

bool check_SID(wstring const& str) {
	// ���� 0 ���� 4�ڸ� ����
	wregex id_reg(L"^[0-9]{4}$");
	if (!regex_match(str, id_reg)) {
		return false;
	}
	return true;
}

bool check_Sname(wstring const& str) {
	// ���̰� 1�̻� 20����
	// ������� ���� ������ ����
	// �� ���ڴ� ����, �θ��� ��ҹ���, �ڸ� ������ �ϼ��� �ѱ� 
	wregex name_reg(L"^[0-9��-�Ra-zA-Z]{1,20}$");
	if (!regex_match(str, name_reg)) {
		return false;
	}

	// ���ڷθ� �����Ǹ� �ȵ�
	name_reg = L"^[0-9]+$";
	if (regex_match(str, name_reg)) {
		return false;
	}

	// "����"�� ��ġ�ϸ� �ȵ�
	if (str.compare(L"����") == 0) {
		return false;
	}

	// �������� "�а�" �Ǵ� "�к�"�� ������ �ȵ�
	name_reg = L".*(�а�|�к�)$";
	if (regex_match(str, name_reg)) {
		return false;
	}
	return true;
}

bool check_Scredit(wstring const& str) {
	// 1,2,3 �� �ϳ��� ���ڸ� ����
	wregex credit_reg(L"[1-3]");
	if (!regex_match(str, credit_reg)) {
		return false;
	}
	return true;
}

bool check_Smajor(wstring const& str) {
	// "����"�� ��Ȯ�� ��ġ�ϴ� ���ڿ�
	if (str.compare(L"����") == 0) {
		return true;
	}

	// ���̰� 1�̻� 10����
	// ������� ���� �� ���� ����
	// �� ���ڴ� ����, �θ��� ��ҹ���, �ڸ� ������ �ϼ��� �ѱ�
	// "�а�" �Ǵ� "�к�"�� ������ ���ڿ�
	wregex major_reg(L"^[0-9��-�Ra-zA-Z]{0,8}(�а�|�к�)$");
	if (!regex_match(str, major_reg)) {
		return false;
	}
	return true;
}

bool check_Sgrade(wstring const& str) {
	// 0,1,2,3,4 �� �ϳ��� ���ڸ� ����
	wregex grade_reg(L"[0-4]");
	if (!regex_match(str, grade_reg)) {
		return false;
	}
	return true;
}

bool check_Stime(wstring const& str) {
	map<wchar_t, int> days = { {L'��',1},{L'ȭ',2},{L'��',3},{L'��',4},{L'��',5},{L'��',6},{L'��',7} };

	// [����] + ����2�� + '-' ����2��
	wregex time_reg1(L"^[��ȭ���������][0-9]{2}-[0-9]{2}$");
	if (regex_match(str, time_reg1)) {
		int t1 = stoi(str.substr(1, 2));
		int t2 = stoi(str.substr(4, 2));

		// ���ð� 1�̻� 22���� üũ
		if (t1 == 0 || t1 > 22 || t2 == 0 || t2 > 22) {
			return false;
		}

		// �� ���� <= �� ���� üũ
		if (t1 > t2) {
			return false;
		}

		return true;
	}

	// [����] + ����2�� + '-' ����2�� + ',' + [����] + ����2�� + '-' ����2��
	wregex time_reg2(L"^[��ȭ���������][0-9]{2}-[0-9]{2},[��ȭ���������][0-9]{2}-[0-9]{2}$");
	if (regex_match(str, time_reg2)) {
		int d1 = days[str[0]];
		int d2 = days[str[7]];

		int t1 = stoi(str.substr(1, 2));
		int t2 = stoi(str.substr(4, 2));
		int t3 = stoi(str.substr(8, 2));
		int t4 = stoi(str.substr(11, 2));

		// �� ���� < �� ���� üũ
		if (d1 >= d2) {
			return false;
		}

		// ���ð� 1�̻� 22���� üũ
		if (t1 == 0 || t1 > 22 || t2 == 0 || t2 > 22 || t3 == 0 || t3 > 22 || t4 == 0 || t4 > 22) {
			return false;
		}

		// �� ���� <= �� ���� üũ
		if (t1 > t2 || t3 > t4) {
			return false;
		}

		return true;
	}

	return false;
}

bool check_Scapacity(wstring const& str) {
	// ������� ���� ���� ����
	// ���� 0�� �־ �Ǹ�, ���� 0�� �����Ͽ� 1�ڸ� �̻� 3�ڸ� ����
	wregex capacity_reg(L"[0-9]{1,3}");
	if (!regex_match(str, capacity_reg)) {
		return false;
	}
	return true;
}

bool check_Smajor_Sgrade_Match(wstring const& smajor, wstring const& sgrade, int line) {
	int grade = stoi(sgrade);
	if (smajor.compare(L"����") == 0) { // ������ ���
		if (grade != 0) { // �г��� 0�� �ƴϸ�
			nonzero_liberal_arts_lines.push_back(line);
			return false;
		}
	}
	else { // ������ ���
		if (grade == 0) { // �г��� 0�̸�
			zero_major_lines.push_back(line);
			return false;
		}
	}
	return true;
}

bool check_Sprof(wstring const& str) {
	// �� ���ڴ� ����, �θ��� ��ҹ���, �ڸ� ������ �ϼ��� �ѱ�
	// ���ڰ� ���Ե� ��� ���� ������ �� ���ڿ��� ��� ����
	// ���̴� ���ڸ� �����ϰ� 1 �̻� 10 ����
	// ������� ���� ������ ����
	wregex prof_reg(L"^[��-�Ra-zA-Z]{1,10}[0-9]?$");
	if (!regex_match(str, prof_reg)) {
		return false;
	}
	return true;
}

bool check_Sroom(wstring const& str) {
	// [�ǹ�] + ���� 3��
	wregex room_reg(L"^[�������ο�][0-9]{3}$");
	if (!regex_match(str, room_reg)) {
		return false;
	}

	// �� ���� ���� 1 �̻� 5 ����
	int floor = stoi(str.substr(1, 1));
	if (floor < 1 || floor > 5) {
		return false;
	}

	// ������ �� ���� 1 �̻� 19 ����
	int roomNum = stoi(str.substr(2, 2));
	if (roomNum < 1 || roomNum > 19) {
		return false;
	}
	return true;
}

bool check_UID(wstring const& str) {
	// ���ڿ� �� ��� �� ���ڴ� ���ڷθ� ����
	// ���ڿ� ���̰� 9
	wregex id_reg(L"^[0-9]{9}$");
	if (!regex_match(str, id_reg)) {
		return false;
	}
	return true;
}

bool check_Uname(wstring const& str) {
	// ���̰� 1�̻� 10����
	// �� ���ڴ� �θ��� ��ҹ���, �ڸ� ������ �ϼ��� �ѱ� 
	// ������� ���� ������ ����
	wregex name_reg(L"^[��-�Ra-zA-Z]{1,10}$");
	if (!regex_match(str, name_reg)) {
		return false;
	}
	return true;
}

bool check_Umajor(wstring const& str) {
	// ���̰� 1�̻� 10����
	// ������� ���� �� ���� ����
	// �� ���ڴ� ����, �θ��� ��ҹ���, �ڸ� ������ �ϼ��� �ѱ�
	// "�а�" �Ǵ� "�к�"�� ������ ���ڿ�
	wregex major_reg(L"^[0-9��-�Ra-zA-Z]{0,8}(�а�|�к�)$");
	if (!regex_match(str, major_reg)) {
		return false;
	}
	return true;
}

bool check_Ugrade(wstring const& str) {
	// 1,2,3,4 �� �ϳ��� ���ڸ� ����
	wregex grade_reg(L"[1-4]");
	if (!regex_match(str, grade_reg)) {
		return false;
	}
	return true;
}

bool check_Acquisition_Credit(wstring const& str) {
	// ������� ���� ���� ����
	// ���� 0�� �־ �Ǹ�, ���� 0�� �����Ͽ� 1�ڸ� �̻� 3�ڸ� ����
	wregex grade_reg(L"[0-9]{1,3}");
	if (!regex_match(str, grade_reg)) {
		return false;
	}

	// 200���Ͽ��� ��
	int num = stoi(str);
	if (num > 200) {
		return false;
	}
	return true;
}

string wstr2str(const wstring& _src) {
	USES_CONVERSION;
	return string(W2A(_src.c_str()));
};

wstring& trim(wstring& s, const wchar_t* t) {
	s.erase(0, s.find_first_not_of(t));
	s.erase(s.find_last_not_of(t) + 1);
	return s;
}

void save_Sprof_Sroom_Stime(wstring const& sprof, wstring const& sroom, wstring const& time, int line) {
	int col;
	wstring stime = time;
	while (true) {
		switch (stime.at(0)) {
		case L'��':
			col = 0;
			break;
		case L'ȭ':
			col = 1;
			break;
		case L'��':
			col = 2;
			break;
		case L'��':
			col = 3;
			break;
		case L'��':
			col = 4;
			break;
		case L'��':
			col = 5;
			break;
		case L'��':
			col = 6;
		}

		if (!profTimeTable.count(sprof)) {	// sprof Ű�� map�� ������ �迭 �����Ҵ� �� map�� �߰�
			vector<int>(*profArr)[22][7] = new (vector<int>[1][22][7]);
			profTimeTable[sprof] = profArr;
		}

		for (int i = stoi(wstr2str(stime.substr(1, 2))); i <= stoi(wstr2str(stime.substr(4, 2))); i++) {
			if ((*profTimeTable[sprof])[i - 1][col].size() >= 1) {
				is_duplicated_time_prof = true;
			}
			(*profTimeTable[sprof])[i - 1][col].push_back(line);
		}

		if (!roomTimeTable.count(sroom)) {	// sroom Ű�� map�� ������ �迭 �����Ҵ� �� map�� �߰�
			vector<int>(*roomArr)[22][7] = new (vector<int>[1][22][7]);
			roomTimeTable[sroom] = roomArr;
		}

		for (int i = stoi(wstr2str(stime.substr(1, 2))); i <= stoi(wstr2str(stime.substr(4, 2))); i++) {
			if ((*roomTimeTable[sroom])[i - 1][col].size() >= 1) {
				is_duplicated_time_room = true;
			}
			(*roomTimeTable[sroom])[i - 1][col].push_back(line);
		}

		if (stime.size() > 6) {
			stime = stime.substr(7, 6);
		}
		else { return; }
	}
}

void print_Sprof_Stime_redundancy() {
	gotoUTF;
	map<int, wchar_t> days = { {0,L'��'},{1,L'ȭ',},{2,L'��'},{3,L'��'},{4,L'��'},{5,L'��'},{6,L'��'} };

	for (auto it = profTimeTable.begin(); it != profTimeTable.end(); it++) {
		for (int j = 0; j < 7; j++) {
			for (int i = 0; i < 22; i++) {
				int v_size = ((*(it->second))[i][j]).size();
				if (v_size > 1) {
					wcout << "\"" << it->first << "\" ";
					wprintf(L"������ ����� �� \"%c%02d����\"�� ��ġ�� ������� �����մϴ�.\n#", days[j], i + 1);
					for (int k = 0; k < v_size; k++) {
						wprintf(L"%d��", ((*(it->second))[i][j])[k]);
						(k == v_size - 1) ? printf("\n") : printf(",");
					}
				}
			}
		}
	}
	gotoClassic;
}

void print_Sroom_Stime_redundancy() {
	gotoUTF;
	map<int, wchar_t> days = { {0,L'��'},{1,L'ȭ',},{2,L'��'},{3,L'��'},{4,L'��'},{5,L'��'},{6,L'��'} };

	for (auto it = roomTimeTable.begin(); it != roomTimeTable.end(); it++) {
		for (int j = 0; j < 7; j++) {
			for (int i = 0; i < 22; i++) {
				int v_size = ((*(it->second))[i][j]).size();
				if (v_size > 1) {
					wcout << "\"" << it->first << "\" ";
					wprintf(L"���ǽǿ��� ���� ����� �� \"%c%02d����\"�� ��ġ�� ������� �����մϴ�.\n#", days[j], i + 1);
					for (int k = 0; k < v_size; k++) {
						wprintf(L"%d��", ((*(it->second))[i][j])[k]);
						(k == v_size - 1) ? printf("\n") : printf(",");
					}
				}
			}
		}
	}
	gotoClassic;
}