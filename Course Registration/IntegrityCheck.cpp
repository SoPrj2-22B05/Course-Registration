#pragma once
#include "IntegrityCheck.h"

#include <iostream>
#include <fstream>
#include <locale.h>
#include <string>
#include <sstream>
#include <vector>
#include <regex>

#define gotoUTF locale::global(locale("ko_KR.UTF-8"));
#define gotoClassic locale::global(locale::classic());

using namespace std;


//wstring& ltrim(wstring& s, const wchar_t* t = L" \t\n\r\f\v") {
//	s.erase(0, s.find_first_not_of(t));
//	return s;
//}
//
//wstring& rtrim(wstring& s, const wchar_t* t = L" \t\n\r\f\v") {
//	s.erase(s.find_last_not_of(t) + 1);
//	return s;
//}

wstring& trim(wstring& s, const wchar_t* t = L" \t\n\r\f\v") {
	s.erase(0, s.find_first_not_of(t));
	s.erase(s.find_last_not_of(t) + 1);
	//return ltrim(rtrim(s, t), t);
	return s;
}


vector<int> Subject_File_Grammar_Error_Line;
vector<int> User_File_Grammar_Error_Line;

void check_User_File();
//void check_Subject_File();

bool check_UID(wstring const& str);
bool check_Uname(wstring const& str);
bool check_Umajor(wstring const& str);
bool check_Ugrade(wstring const& str);
bool check_Acquisition_Credit(wstring const& str);


void Integrity_Check() {
	check_User_File();
	//check_Subject_File();
}

void check_User_File() {
	gotoUTF;
	wfstream f(L"����� ������ ����.txt");

	if (!f.is_open()) {
		wprintf(L"���� : Ȩ ��ο� ���� ������ ���� �Ǵ� ����� ������ ������ �����ϴ�. ���α׷��� �����մϴ�.????���α׷� ��ġ ���????\n");
		exit(0);
	}

	vector<wstring> data; // id  name  major  grade  acquisition_credit
	wstring line, str;
	wstringstream ss;

	int lineCount = 0;
	while (getline(f, line)) {
		lineCount++;
		data.clear();
		ss.clear();

		ss.str(line);
		while (getline(ss, str, L'\t')) {

			str = trim(str);
			//str.erase(remove_if(str.begin(), str.end(), ::isspace), str.end());
			if (str != L"") {
				data.push_back(str);
			}
		}

		if (!check_UID(data[0])) { // �й�(����) ���� ���� üũ
			User_File_Grammar_Error_Line.push_back(lineCount);
			continue;
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
			}
			/*gotoClassic;
			cout << "�������Դϴ�." << endl;
			gotoUTF;*/
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
			/*gotoClassic;
			cout << "�л��Դϴ�." << endl;
			gotoUTF;*/
		}

		//for (int i = 0; i < data.size(); i++) {
		//	wcout << data[i] + L" + ";
		//}
		//cout << endl;
	}

	gotoClassic;
	int num_Error = User_File_Grammar_Error_Line.size();
	if (num_Error != 0) {
		printf("���� : ����� ������ ������ ���� ��Ģ�� �ùٸ��� �ʽ��ϴ�.\n# ");
		for (int i = 0; i < num_Error; i++) {
			printf("%d��", User_File_Grammar_Error_Line[i]);
			(i == num_Error - 1) ? printf("\n") : printf(",");
		}
	}
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