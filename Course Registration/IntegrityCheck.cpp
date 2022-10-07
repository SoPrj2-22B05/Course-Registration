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
	wfstream f(L"사용자 데이터 파일.txt");

	if (!f.is_open()) {
		wprintf(L"오류 : 홈 경로에 과목 데이터 파일 또는 사용자 데이터 파일이 없습니다. 프로그램을 종료합니다.????프로그램 위치 출력????\n");
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

		if (!check_UID(data[0])) { // 학번(교번) 문법 형식 체크
			User_File_Grammar_Error_Line.push_back(lineCount);
			continue;
		}

		if (data[0].substr(0, 4).compare(L"0000") == 0) { // 관리자인 경우
			if (data.size() != 2) { // 요소 2개인지 체크
				User_File_Grammar_Error_Line.push_back(lineCount);
				continue;
			}
			else {
				if (!check_Uname(data[1])) { // 이름 체크
					User_File_Grammar_Error_Line.push_back(lineCount);
					continue;
				}
			}
			/*gotoClassic;
			cout << "관리자입니다." << endl;
			gotoUTF;*/
		}
		else { // 학생인 경우
			if (data.size() != 5) { // 요소 5개인지 체크
				User_File_Grammar_Error_Line.push_back(lineCount);
				continue;
			}
			else {
				if (!check_Uname(data[1])) { // 이름 체크
					User_File_Grammar_Error_Line.push_back(lineCount);
					continue;
				}
				if (!check_Umajor(data[2])) { // 전공 체크
					User_File_Grammar_Error_Line.push_back(lineCount);
					continue;
				}
				if (!check_Ugrade(data[3])) { // 학년 체크
					User_File_Grammar_Error_Line.push_back(lineCount);
					continue;
				}
				if (!check_Acquisition_Credit(data[4])) { // 취득학점 체크
					User_File_Grammar_Error_Line.push_back(lineCount);
					continue;
				}
			}
			/*gotoClassic;
			cout << "학생입니다." << endl;
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
		printf("오류 : 사용자 데이터 파일의 문법 규칙이 올바르지 않습니다.\n# ");
		for (int i = 0; i < num_Error; i++) {
			printf("%d행", User_File_Grammar_Error_Line[i]);
			(i == num_Error - 1) ? printf("\n") : printf(",");
		}
	}
}

bool check_UID(wstring const& str) {
	// 문자열 내 모든 각 문자는 숫자로만 구성
	// 문자열 길이가 9
	wregex id_reg(L"^[0-9]{9}$");
	if (!regex_match(str, id_reg)) {
		return false;
	}

	return true;
}

bool check_Uname(wstring const& str) {
	// 길이가 1이상 10이하
	// 각 문자는 로마자 대소문자, 자모 조합이 완성된 한글 
	// 공백류는 전혀 들어가있지 않음
	wregex name_reg(L"^[가-힣a-zA-Z]{1,10}$");
	if (!regex_match(str, name_reg)) {
		return false;
	}

	return true;
}

bool check_Umajor(wstring const& str) {
	// 길이가 1이상 10이하
	// 공백류는 전혀 들어가 있지 않음
	// 각 문자는 숫자, 로마자 대소문자, 자모 조합이 완성된 한글
	// "학과" 또는 "학부"로 끝나는 문자열
	wregex major_reg(L"^[0-9가-힣a-zA-Z]{0,8}(학과|학부)$");
	if (!regex_match(str, major_reg)) {
		return false;
	}
	return true;
}

bool check_Ugrade(wstring const& str) {
	// 1,2,3,4 중 하나의 숫자만 가능
	wregex grade_reg(L"[1-4]");
	if (!regex_match(str, grade_reg)) {
		return false;
	}
	return true;
}

bool check_Acquisition_Credit(wstring const& str) {
	// 공백류는 전혀 들어가지 않음
	// 선행 0이 있어도 되며, 선행 0을 포함하여 1자리 이상 3자리 이하
	wregex grade_reg(L"[0-9]{1,3}");
	if (!regex_match(str, grade_reg)) {
		return false;
	}
	
	// 200이하여야 함
	int num = stoi(str);
	if (num > 200) {
		return false;
	}

	return true;
}