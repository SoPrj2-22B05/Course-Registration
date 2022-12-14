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
map<wstring, vector<int>> SIDs; // <과목번호, 해당하는 행들>

int admin_count = 0;
bool is_duplicated_UID = false;
map<wstring, vector<int>> UIDs; // <학번(교번), 해당하는 행들>

bool is_duplicated_time_prof;	// 담당교수 - 강의시간 중복 체크 (중간 이후 새로 추가)
bool is_duplicated_time_room;	// 강의실 - 강의시간 중복 체크 (중간 이후 새로 추가)
map<wstring, vector<int>(*)[22][7]> profTimeTable;	//담당교수 map (중간 이후 새로 추가)
map<wstring, vector<int>(*)[22][7]> roomTimeTable;	//강의실 map (중간 이후 새로 추가)

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
	wfstream f1(L"과목 데이터 파일.txt");
	wfstream f2(L"사용자 데이터 파일.txt");
	if (!f1.is_open() || !f2.is_open()) {
		wcout << L"오류 : 홈 경로 " << dir << L" 에 과목 데이터 파일 또는 사용자 데이터 파일이 없습니다.프로그램을 종료합니다." << endl;
		system("pause");
		exit(0);
	}
	f1.close();
	f2.close();
}

void check_Subject_File() {
	gotoUTF;
	wfstream f(L"과목 데이터 파일.txt");

	vector<wstring> data; // id  name  credit  major  grade  time  capacity
	wstring line, str;
	wstringstream ss;

	int lineCount = 0;
	while (getline(f, line)) {
		lineCount++;
		data.clear();
		ss.clear();

		// 비어있는 행인지 체크
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

		if (data.size() != 9) { // 요소 9개인지 체크
			Subject_File_Grammar_Error_Line.push_back(lineCount);
			continue;
		}

		if (!check_SID(data[0])) { // 과목번호 문법 형식 체크
			Subject_File_Grammar_Error_Line.push_back(lineCount);
			continue;
		}
		else {
			if (SIDs.find(data[0]) != SIDs.end()) { // 과목번호 중복 체크
				is_duplicated_SID = true;
			}
			SIDs[data[0]].push_back(lineCount);
		}

		if (!check_Sname(data[1])) { // 과목이름 체크
			Subject_File_Grammar_Error_Line.push_back(lineCount);
			continue;
		}
		if (!check_Scredit(data[2])) { // 학점 체크
			Subject_File_Grammar_Error_Line.push_back(lineCount);
			continue;
		}
		if (!check_Smajor(data[3])) { // 전공/교양 체크
			Subject_File_Grammar_Error_Line.push_back(lineCount);
			continue;
		}
		if (!check_Sgrade(data[4])) { // 학년 체크
			Subject_File_Grammar_Error_Line.push_back(lineCount);
			continue;
		}
		if (!check_Stime(data[5])) { // 강의시간 체크
			Subject_File_Grammar_Error_Line.push_back(lineCount);
			continue;
		}
		if (!check_Scapacity(data[6])) { // 정원 체크
			Subject_File_Grammar_Error_Line.push_back(lineCount);
			continue;
		}
		if (!check_Smajor_Sgrade_Match(data[3], data[4],lineCount)) { // 전공/교양 - 학년 매칭 체크
			is_unmatched_major_grade = true;
		}
		if (!check_Sprof(data[7])) { // 담당교수 체크
			Subject_File_Grammar_Error_Line.push_back(lineCount);
			continue;
		}
		if (!check_Sroom(data[8])) { // 강의실 체크
			Subject_File_Grammar_Error_Line.push_back(lineCount);
			continue;
		}
		save_Sprof_Sroom_Stime(data[7], data[8], data[5], lineCount);

		//for (int i = 0; i < data.size(); i++) {
		//	wcout << data[i] + L" + ";
		//}
		//cout << endl;

		// 데이터 배열에 추가
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
	wfstream f(L"사용자 데이터 파일.txt");

	vector<wstring> data; // id  name  major  grade  acquisition_credit
	wstring line, str;
	wstringstream ss;

	int lineCount = 0;
	while (getline(f, line)) {
		lineCount++;
		data.clear();
		ss.clear();

		// 비어있는 행인지 체크
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

		if (!check_UID(data[0])) { // 학번(교번) 문법 형식 체크
			User_File_Grammar_Error_Line.push_back(lineCount);
			continue;
		}
		else {
			if (UIDs.find(data[0]) != UIDs.end()) { // 학번(교번) 중복 체크
				is_duplicated_UID = true;
			}
			UIDs[data[0]].push_back(lineCount);
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
				admin_count++; // 관리자 수 카운트
			}
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

	// 과목 데이터 파일 오류
	int num_G_error = Subject_File_Grammar_Error_Line.size();
	if (num_G_error != 0) { // 문법 오류 있는 경우
		has_Error = true;
		printf("오류 : 과목 데이터 파일의 문법 규칙이 올바르지 않습니다.\n# ");
		for (int i = 0; i < num_G_error; i++) {
			printf("%d행", Subject_File_Grammar_Error_Line[i]);
			(i == num_G_error - 1) ? printf("\n") : printf(",");
		}
	}
	else if (is_duplicated_SID || is_unmatched_major_grade || is_duplicated_time_prof || is_duplicated_time_room) { // 의미 오류 있는 경우
		has_Error = true;
		printf("오류 : 과목 데이터 파일의 의미 규칙이 올바르지 않습니다.\n");

		//겹치는 과목번호 있으면 출력
		for (auto it : SIDs) {
			if (it.second.size() != 1) {
				wcout << "\"" << it.first << "\"" << "과목번호가 중복해서 존재합니다.\n# ";
				for (int i = 0; i < it.second.size(); i++) {
					printf("%d행", it.second[i]);
					(i == it.second.size() - 1) ? printf("\n") : printf(",");
				}
			}
		}

		// 교양인데 학년이 0이 아닌 행 있으면 출력
		int error_size = nonzero_liberal_arts_lines.size();
		if (error_size != 0) {
			printf("전공/교양이 \"교양\"인데 학년이 0이 아닌 행이 존재합니다.\n# ");
			for (int i = 0; i < error_size; i++) {
				printf("%d행", nonzero_liberal_arts_lines[i]);
				(i == error_size - 1) ? printf("\n") : printf(",");
			}
		}

		// 교양이 아닌데 학년이 0인 행 있으면 출력
		error_size = zero_major_lines.size();
		if (error_size != 0) {
			printf("전공/교양이 \"교양\"이 아닌데 학년이 0인 행이 존재합니다.\n# ");
			for (int i = 0; i < error_size; i++) {
				printf("%d행", zero_major_lines[i]);
				(i == error_size - 1) ? printf("\n") : printf(",");
			}
		}

		// 담당교수 시간표 중복 있으면 출력
		if (is_duplicated_time_prof) {
			print_Sprof_Stime_redundancy();
		}

		// 강의실 시간표 중복 있으면 출력
		if (is_duplicated_time_room) {
			print_Sroom_Stime_redundancy();
		}
	}

	// 사용자 데이터 파일 오류
	num_G_error = User_File_Grammar_Error_Line.size();
	if (num_G_error != 0) { // 문법 오류 있는 경우
		has_Error = true;
		printf("오류 : 사용자 데이터 파일의 문법 규칙이 올바르지 않습니다.\n# ");
		for (int i = 0; i < num_G_error; i++) {
			printf("%d행", User_File_Grammar_Error_Line[i]);
			(i == num_G_error - 1) ? printf("\n") : printf(",");
		}
	}
	else if (is_duplicated_UID || admin_count == 0) { // 의미 오류 있는 경우
		has_Error = true;
		printf("오류 : 사용자 데이터 파일의 의미 규칙이 올바르지 않습니다.\n");

		// 겹치는 학번(교번) 있으면 출력
		for (auto it : UIDs) {
			if (it.second.size() != 1) {
				wcout << "\"" << it.first << "\"";

				if (it.first.substr(0, 4).compare(L"0000") == 0) {
					printf("교번이 중복해서 존재합니다.\n# ");
				}
				else {
					printf("학번이 중복해서 존재합니다.\n# ");
				}

				for (int i = 0; i < it.second.size(); i++) {
					printf("%d행", it.second[i]);
					(i == it.second.size() - 1) ? printf("\n") : printf(",");
				}
			}
		}

		// 관리자 없으면 출력
		if (admin_count == 0) {
			printf("관리자가 한 명도 존재하지 않습니다.\n");
		}
	}

	//map의 value로 들어가는 동적할당 해제
	/*
	for (auto it = profTimeTable.begin(); it != profTimeTable.end(); it++) {
		delete[] it->second;
	}
	for (auto it = roomTimeTable.begin(); it != roomTimeTable.end(); it++) {
		delete[] it->second;
	}
	*/

	if (has_Error) {
		cout << "프로그램을 종료합니다." << endl;
		system("pause");
		exit(0);
	}
}

bool check_SID(wstring const& str) {
	// 선행 0 포함 4자리 정수
	wregex id_reg(L"^[0-9]{4}$");
	if (!regex_match(str, id_reg)) {
		return false;
	}
	return true;
}

bool check_Sname(wstring const& str) {
	// 길이가 1이상 20이하
	// 공백류는 전혀 들어가있지 않음
	// 각 문자는 숫자, 로마자 대소문자, 자모 조합이 완성된 한글 
	wregex name_reg(L"^[0-9가-힣a-zA-Z]{1,20}$");
	if (!regex_match(str, name_reg)) {
		return false;
	}

	// 숫자로만 구성되면 안됨
	name_reg = L"^[0-9]+$";
	if (regex_match(str, name_reg)) {
		return false;
	}

	// "교양"과 일치하면 안됨
	if (str.compare(L"교양") == 0) {
		return false;
	}

	// 마지막이 "학과" 또는 "학부"로 끝나면 안됨
	name_reg = L".*(학과|학부)$";
	if (regex_match(str, name_reg)) {
		return false;
	}
	return true;
}

bool check_Scredit(wstring const& str) {
	// 1,2,3 중 하나의 숫자만 가능
	wregex credit_reg(L"[1-3]");
	if (!regex_match(str, credit_reg)) {
		return false;
	}
	return true;
}

bool check_Smajor(wstring const& str) {
	// "교양"과 정확히 일치하는 문자열
	if (str.compare(L"교양") == 0) {
		return true;
	}

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

bool check_Sgrade(wstring const& str) {
	// 0,1,2,3,4 중 하나의 숫자만 가능
	wregex grade_reg(L"[0-4]");
	if (!regex_match(str, grade_reg)) {
		return false;
	}
	return true;
}

bool check_Stime(wstring const& str) {
	map<wchar_t, int> days = { {L'월',1},{L'화',2},{L'수',3},{L'목',4},{L'금',5},{L'토',6},{L'일',7} };

	// [요일] + 숫자2개 + '-' 숫자2개
	wregex time_reg1(L"^[월화수목금토일][0-9]{2}-[0-9]{2}$");
	if (regex_match(str, time_reg1)) {
		int t1 = stoi(str.substr(1, 2));
		int t2 = stoi(str.substr(4, 2));

		// 교시가 1이상 22이하 체크
		if (t1 == 0 || t1 > 22 || t2 == 0 || t2 > 22) {
			return false;
		}

		// 앞 교시 <= 뒷 교시 체크
		if (t1 > t2) {
			return false;
		}

		return true;
	}

	// [요일] + 숫자2개 + '-' 숫자2개 + ',' + [요일] + 숫자2개 + '-' 숫자2개
	wregex time_reg2(L"^[월화수목금토일][0-9]{2}-[0-9]{2},[월화수목금토일][0-9]{2}-[0-9]{2}$");
	if (regex_match(str, time_reg2)) {
		int d1 = days[str[0]];
		int d2 = days[str[7]];

		int t1 = stoi(str.substr(1, 2));
		int t2 = stoi(str.substr(4, 2));
		int t3 = stoi(str.substr(8, 2));
		int t4 = stoi(str.substr(11, 2));

		// 앞 요일 < 뒷 요일 체크
		if (d1 >= d2) {
			return false;
		}

		// 교시가 1이상 22이하 체크
		if (t1 == 0 || t1 > 22 || t2 == 0 || t2 > 22 || t3 == 0 || t3 > 22 || t4 == 0 || t4 > 22) {
			return false;
		}

		// 앞 교시 <= 뒷 교시 체크
		if (t1 > t2 || t3 > t4) {
			return false;
		}

		return true;
	}

	return false;
}

bool check_Scapacity(wstring const& str) {
	// 공백류는 전혀 들어가지 않음
	// 선행 0이 있어도 되며, 선행 0을 포함하여 1자리 이상 3자리 이하
	wregex capacity_reg(L"[0-9]{1,3}");
	if (!regex_match(str, capacity_reg)) {
		return false;
	}
	return true;
}

bool check_Smajor_Sgrade_Match(wstring const& smajor, wstring const& sgrade, int line) {
	int grade = stoi(sgrade);
	if (smajor.compare(L"교양") == 0) { // 교양인 경우
		if (grade != 0) { // 학년이 0이 아니면
			nonzero_liberal_arts_lines.push_back(line);
			return false;
		}
	}
	else { // 전공인 경우
		if (grade == 0) { // 학년이 0이면
			zero_major_lines.push_back(line);
			return false;
		}
	}
	return true;
}

bool check_Sprof(wstring const& str) {
	// 각 문자는 숫자, 로마자 대소문자, 자모 조합이 완성된 한글
	// 숫자가 포함될 경우 제일 마지막 한 문자에만 사용 가능
	// 길이는 숫자를 제외하고 1 이상 10 이하
	// 공백류는 전혀 들어가있지 않음
	wregex prof_reg(L"^[가-힣a-zA-Z]{1,10}[0-9]?$");
	if (!regex_match(str, prof_reg)) {
		return false;
	}
	return true;
}

bool check_Sroom(wstring const& str) {
	// [건물] + 숫자 3개
	wregex room_reg(L"^[새법공인예][0-9]{3}$");
	if (!regex_match(str, room_reg)) {
		return false;
	}

	// 맨 왼쪽 숫자 1 이상 5 이하
	int floor = stoi(str.substr(1, 1));
	if (floor < 1 || floor > 5) {
		return false;
	}

	// 오른쪽 두 숫자 1 이상 19 이하
	int roomNum = stoi(str.substr(2, 2));
	if (roomNum < 1 || roomNum > 19) {
		return false;
	}
	return true;
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
		case L'월':
			col = 0;
			break;
		case L'화':
			col = 1;
			break;
		case L'수':
			col = 2;
			break;
		case L'목':
			col = 3;
			break;
		case L'금':
			col = 4;
			break;
		case L'토':
			col = 5;
			break;
		case L'일':
			col = 6;
		}

		if (!profTimeTable.count(sprof)) {	// sprof 키가 map에 없으면 배열 동적할당 후 map에 추가
			vector<int>(*profArr)[22][7] = new (vector<int>[1][22][7]);
			profTimeTable[sprof] = profArr;
		}

		for (int i = stoi(wstr2str(stime.substr(1, 2))); i <= stoi(wstr2str(stime.substr(4, 2))); i++) {
			if ((*profTimeTable[sprof])[i - 1][col].size() >= 1) {
				is_duplicated_time_prof = true;
			}
			(*profTimeTable[sprof])[i - 1][col].push_back(line);
		}

		if (!roomTimeTable.count(sroom)) {	// sroom 키가 map에 없으면 배열 동적할당 후 map에 추가
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
	map<int, wchar_t> days = { {0,L'월'},{1,L'화',},{2,L'수'},{3,L'목'},{4,L'금'},{5,L'토'},{6,L'일'} };

	for (auto it = profTimeTable.begin(); it != profTimeTable.end(); it++) {
		for (int j = 0; j < 7; j++) {
			for (int i = 0; i < 22; i++) {
				int v_size = ((*(it->second))[i][j]).size();
				if (v_size > 1) {
					wcout << "\"" << it->first << "\" ";
					wprintf(L"교수의 과목들 중 \"%c%02d교시\"가 겹치는 과목들이 존재합니다.\n#", days[j], i + 1);
					for (int k = 0; k < v_size; k++) {
						wprintf(L"%d행", ((*(it->second))[i][j])[k]);
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
	map<int, wchar_t> days = { {0,L'월'},{1,L'화',},{2,L'수'},{3,L'목'},{4,L'금'},{5,L'토'},{6,L'일'} };

	for (auto it = roomTimeTable.begin(); it != roomTimeTable.end(); it++) {
		for (int j = 0; j < 7; j++) {
			for (int i = 0; i < 22; i++) {
				int v_size = ((*(it->second))[i][j]).size();
				if (v_size > 1) {
					wcout << "\"" << it->first << "\" ";
					wprintf(L"강의실에서 열린 과목들 중 \"%c%02d교시\"가 겹치는 과목들이 존재합니다.\n#", days[j], i + 1);
					for (int k = 0; k < v_size; k++) {
						wprintf(L"%d행", ((*(it->second))[i][j])[k]);
						(k == v_size - 1) ? printf("\n") : printf(",");
					}
				}
			}
		}
	}
	gotoClassic;
}