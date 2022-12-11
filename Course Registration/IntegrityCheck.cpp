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
map<wstring, vector<int>> SIDs; // <°ú¸ñ¹øÈ£, ÇØ´çÇÏ´Â Çàµé>

int admin_count = 0;
bool is_duplicated_UID = false;
map<wstring, vector<int>> UIDs; // <ÇĞ¹ø(±³¹ø), ÇØ´çÇÏ´Â Çàµé>

bool is_duplicated_time_prof;	// ´ã´ç±³¼ö - °­ÀÇ½Ã°£ Áßº¹ Ã¼Å© (Áß°£ ÀÌÈÄ »õ·Î Ãß°¡)
bool is_duplicated_time_room;	// °­ÀÇ½Ç - °­ÀÇ½Ã°£ Áßº¹ Ã¼Å© (Áß°£ ÀÌÈÄ »õ·Î Ãß°¡)
map<wstring, vector<int>(*)[22][7]> profTimeTable;	//´ã´ç±³¼ö map (Áß°£ ÀÌÈÄ »õ·Î Ãß°¡)
map<wstring, vector<int>(*)[22][7]> roomTimeTable;	//°­ÀÇ½Ç map (Áß°£ ÀÌÈÄ »õ·Î Ãß°¡)

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
	wfstream f1(L"°ú¸ñ µ¥ÀÌÅÍ ÆÄÀÏ.txt");
	wfstream f2(L"»ç¿ëÀÚ µ¥ÀÌÅÍ ÆÄÀÏ.txt");
	if (!f1.is_open() || !f2.is_open()) {
		wcout << L"¿À·ù : È¨ °æ·Î " << dir << L" ¿¡ °ú¸ñ µ¥ÀÌÅÍ ÆÄÀÏ ¶Ç´Â »ç¿ëÀÚ µ¥ÀÌÅÍ ÆÄÀÏÀÌ ¾ø½À´Ï´Ù.ÇÁ·Î±×·¥À» Á¾·áÇÕ´Ï´Ù." << endl;
		system("pause");
		exit(0);
	}
	f1.close();
	f2.close();
}

void check_Subject_File() {
	gotoUTF;
	wfstream f(L"°ú¸ñ µ¥ÀÌÅÍ ÆÄÀÏ.txt");

	vector<wstring> data; // id  name  credit  major  grade  time  capacity
	wstring line, str;
	wstringstream ss;

	int lineCount = 0;
	while (getline(f, line)) {
		lineCount++;
		data.clear();
		ss.clear();

		// ºñ¾îÀÖ´Â ÇàÀÎÁö Ã¼Å©
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

		if (data.size() != 9) { // ¿ä¼Ò 9°³ÀÎÁö Ã¼Å©
			Subject_File_Grammar_Error_Line.push_back(lineCount);
			continue;
		}

		if (!check_SID(data[0])) { // °ú¸ñ¹øÈ£ ¹®¹ı Çü½Ä Ã¼Å©
			Subject_File_Grammar_Error_Line.push_back(lineCount);
			continue;
		}
		else {
			if (SIDs.find(data[0]) != SIDs.end()) { // °ú¸ñ¹øÈ£ Áßº¹ Ã¼Å©
				is_duplicated_SID = true;
			}
			SIDs[data[0]].push_back(lineCount);
		}

		if (!check_Sname(data[1])) { // °ú¸ñÀÌ¸§ Ã¼Å©
			Subject_File_Grammar_Error_Line.push_back(lineCount);
			continue;
		}
		if (!check_Scredit(data[2])) { // ÇĞÁ¡ Ã¼Å©
			Subject_File_Grammar_Error_Line.push_back(lineCount);
			continue;
		}
		if (!check_Smajor(data[3])) { // Àü°ø/±³¾ç Ã¼Å©
			Subject_File_Grammar_Error_Line.push_back(lineCount);
			continue;
		}
		if (!check_Sgrade(data[4])) { // ÇĞ³â Ã¼Å©
			Subject_File_Grammar_Error_Line.push_back(lineCount);
			continue;
		}
		if (!check_Stime(data[5])) { // °­ÀÇ½Ã°£ Ã¼Å©
			Subject_File_Grammar_Error_Line.push_back(lineCount);
			continue;
		}
		if (!check_Scapacity(data[6])) { // Á¤¿ø Ã¼Å©
			Subject_File_Grammar_Error_Line.push_back(lineCount);
			continue;
		}
		if (!check_Smajor_Sgrade_Match(data[3], data[4],lineCount)) { // Àü°ø/±³¾ç - ÇĞ³â ¸ÅÄª Ã¼Å©
			is_unmatched_major_grade = true;
		}
		if (!check_Sprof(data[7])) { // ´ã´ç±³¼ö Ã¼Å©
			Subject_File_Grammar_Error_Line.push_back(lineCount);
			continue;
		}
		if (!check_Sroom(data[8])) { // °­ÀÇ½Ç Ã¼Å©
			Subject_File_Grammar_Error_Line.push_back(lineCount);
			continue;
		}
		save_Sprof_Sroom_Stime(data[7], data[8], data[5], lineCount);

		//for (int i = 0; i < data.size(); i++) {
		//	wcout << data[i] + L" + ";
		//}
		//cout << endl;

		// µ¥ÀÌÅÍ ¹è¿­¿¡ Ãß°¡
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
	wfstream f(L"»ç¿ëÀÚ µ¥ÀÌÅÍ ÆÄÀÏ.txt");

	vector<wstring> data; // id  name  major  grade  acquisition_credit
	wstring line, str;
	wstringstream ss;

	int lineCount = 0;
	while (getline(f, line)) {
		lineCount++;
		data.clear();
		ss.clear();

		// ºñ¾îÀÖ´Â ÇàÀÎÁö Ã¼Å©
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

		if (!check_UID(data[0])) { // ÇĞ¹ø(±³¹ø) ¹®¹ı Çü½Ä Ã¼Å©
			User_File_Grammar_Error_Line.push_back(lineCount);
			continue;
		}
		else {
			if (UIDs.find(data[0]) != UIDs.end()) { // ÇĞ¹ø(±³¹ø) Áßº¹ Ã¼Å©
				is_duplicated_UID = true;
			}
			UIDs[data[0]].push_back(lineCount);
		}

		if (data[0].substr(0, 4).compare(L"0000") == 0) { // °ü¸®ÀÚÀÎ °æ¿ì
			if (data.size() != 2) { // ¿ä¼Ò 2°³ÀÎÁö Ã¼Å©
				User_File_Grammar_Error_Line.push_back(lineCount);
				continue;
			}
			else {
				if (!check_Uname(data[1])) { // ÀÌ¸§ Ã¼Å©
					User_File_Grammar_Error_Line.push_back(lineCount);
					continue;
				}
				admin_count++; // °ü¸®ÀÚ ¼ö Ä«¿îÆ®
			}
		}
		else { // ÇĞ»ıÀÎ °æ¿ì
			if (data.size() != 5) { // ¿ä¼Ò 5°³ÀÎÁö Ã¼Å©
				User_File_Grammar_Error_Line.push_back(lineCount);
				continue;
			}
			else {
				if (!check_Uname(data[1])) { // ÀÌ¸§ Ã¼Å©
					User_File_Grammar_Error_Line.push_back(lineCount);
					continue;
				}
				if (!check_Umajor(data[2])) { // Àü°ø Ã¼Å©
					User_File_Grammar_Error_Line.push_back(lineCount);
					continue;
				}
				if (!check_Ugrade(data[3])) { // ÇĞ³â Ã¼Å©
					User_File_Grammar_Error_Line.push_back(lineCount);
					continue;
				}
				if (!check_Acquisition_Credit(data[4])) { // ÃëµæÇĞÁ¡ Ã¼Å©
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

	// °ú¸ñ µ¥ÀÌÅÍ ÆÄÀÏ ¿À·ù
	int num_G_error = Subject_File_Grammar_Error_Line.size();
	if (num_G_error != 0) { // ¹®¹ı ¿À·ù ÀÖ´Â °æ¿ì
		has_Error = true;
		printf("¿À·ù : °ú¸ñ µ¥ÀÌÅÍ ÆÄÀÏÀÇ ¹®¹ı ±ÔÄ¢ÀÌ ¿Ã¹Ù¸£Áö ¾Ê½À´Ï´Ù.\n# ");
		for (int i = 0; i < num_G_error; i++) {
			printf("%dÇà", Subject_File_Grammar_Error_Line[i]);
			(i == num_G_error - 1) ? printf("\n") : printf(",");
		}
	}
	else if (is_duplicated_SID || is_unmatched_major_grade || is_duplicated_time_prof || is_duplicated_time_room) { // ÀÇ¹Ì ¿À·ù ÀÖ´Â °æ¿ì
		has_Error = true;
		printf("¿À·ù : °ú¸ñ µ¥ÀÌÅÍ ÆÄÀÏÀÇ ÀÇ¹Ì ±ÔÄ¢ÀÌ ¿Ã¹Ù¸£Áö ¾Ê½À´Ï´Ù.\n");

		//°ãÄ¡´Â °ú¸ñ¹øÈ£ ÀÖÀ¸¸é Ãâ·Â
		for (auto it : SIDs) {
			if (it.second.size() != 1) {
				wcout << "\"" << it.first << "\"" << "°ú¸ñ¹øÈ£°¡ Áßº¹ÇØ¼­ Á¸ÀçÇÕ´Ï´Ù.\n# ";
				for (int i = 0; i < it.second.size(); i++) {
					printf("%dÇà", it.second[i]);
					(i == it.second.size() - 1) ? printf("\n") : printf(",");
				}
			}
		}

		// ±³¾çÀÎµ¥ ÇĞ³âÀÌ 0ÀÌ ¾Æ´Ñ Çà ÀÖÀ¸¸é Ãâ·Â
		int error_size = nonzero_liberal_arts_lines.size();
		if (error_size != 0) {
			printf("Àü°ø/±³¾çÀÌ \"±³¾ç\"ÀÎµ¥ ÇĞ³âÀÌ 0ÀÌ ¾Æ´Ñ ÇàÀÌ Á¸ÀçÇÕ´Ï´Ù.\n# ");
			for (int i = 0; i < error_size; i++) {
				printf("%dÇà", nonzero_liberal_arts_lines[i]);
				(i == error_size - 1) ? printf("\n") : printf(",");
			}
		}

		// ±³¾çÀÌ ¾Æ´Ñµ¥ ÇĞ³âÀÌ 0ÀÎ Çà ÀÖÀ¸¸é Ãâ·Â
		error_size = zero_major_lines.size();
		if (error_size != 0) {
			printf("Àü°ø/±³¾çÀÌ \"±³¾ç\"ÀÌ ¾Æ´Ñµ¥ ÇĞ³âÀÌ 0ÀÎ ÇàÀÌ Á¸ÀçÇÕ´Ï´Ù.\n# ");
			for (int i = 0; i < error_size; i++) {
				printf("%dÇà", zero_major_lines[i]);
				(i == error_size - 1) ? printf("\n") : printf(",");
			}
		}

		// ´ã´ç±³¼ö ½Ã°£Ç¥ Áßº¹ ÀÖÀ¸¸é Ãâ·Â
		if (is_duplicated_time_prof) {
			print_Sprof_Stime_redundancy();
		}

		// °­ÀÇ½Ç ½Ã°£Ç¥ Áßº¹ ÀÖÀ¸¸é Ãâ·Â
		if (is_duplicated_time_room) {
			print_Sroom_Stime_redundancy();
		}
	}

	// »ç¿ëÀÚ µ¥ÀÌÅÍ ÆÄÀÏ ¿À·ù
	num_G_error = User_File_Grammar_Error_Line.size();
	if (num_G_error != 0) { // ¹®¹ı ¿À·ù ÀÖ´Â °æ¿ì
		has_Error = true;
		printf("¿À·ù : »ç¿ëÀÚ µ¥ÀÌÅÍ ÆÄÀÏÀÇ ¹®¹ı ±ÔÄ¢ÀÌ ¿Ã¹Ù¸£Áö ¾Ê½À´Ï´Ù.\n# ");
		for (int i = 0; i < num_G_error; i++) {
			printf("%dÇà", User_File_Grammar_Error_Line[i]);
			(i == num_G_error - 1) ? printf("\n") : printf(",");
		}
	}
	else if (is_duplicated_UID || admin_count == 0) { // ÀÇ¹Ì ¿À·ù ÀÖ´Â °æ¿ì
		has_Error = true;
		printf("¿À·ù : »ç¿ëÀÚ µ¥ÀÌÅÍ ÆÄÀÏÀÇ ÀÇ¹Ì ±ÔÄ¢ÀÌ ¿Ã¹Ù¸£Áö ¾Ê½À´Ï´Ù.\n");

		// °ãÄ¡´Â ÇĞ¹ø(±³¹ø) ÀÖÀ¸¸é Ãâ·Â
		for (auto it : UIDs) {
			if (it.second.size() != 1) {
				wcout << "\"" << it.first << "\"";

				if (it.first.substr(0, 4).compare(L"0000") == 0) {
					printf("±³¹øÀÌ Áßº¹ÇØ¼­ Á¸ÀçÇÕ´Ï´Ù.\n# ");
				}
				else {
					printf("ÇĞ¹øÀÌ Áßº¹ÇØ¼­ Á¸ÀçÇÕ´Ï´Ù.\n# ");
				}

				for (int i = 0; i < it.second.size(); i++) {
					printf("%dÇà", it.second[i]);
					(i == it.second.size() - 1) ? printf("\n") : printf(",");
				}
			}
		}

		// °ü¸®ÀÚ ¾øÀ¸¸é Ãâ·Â
		if (admin_count == 0) {
			printf("°ü¸®ÀÚ°¡ ÇÑ ¸íµµ Á¸ÀçÇÏÁö ¾Ê½À´Ï´Ù.\n");
		}
	}

	//mapÀÇ value·Î µé¾î°¡´Â µ¿ÀûÇÒ´ç ÇØÁ¦
	/*
	for (auto it = profTimeTable.begin(); it != profTimeTable.end(); it++) {
		delete[] it->second;
	}
	for (auto it = roomTimeTable.begin(); it != roomTimeTable.end(); it++) {
		delete[] it->second;
	}
	*/

	if (has_Error) {
		cout << "ÇÁ·Î±×·¥À» Á¾·áÇÕ´Ï´Ù." << endl;
		system("pause");
		exit(0);
	}
}

bool check_SID(wstring const& str) {
	// ¼±Çà 0 Æ÷ÇÔ 4ÀÚ¸® Á¤¼ö
	wregex id_reg(L"^[0-9]{4}$");
	if (!regex_match(str, id_reg)) {
		return false;
	}
	return true;
}

bool check_Sname(wstring const& str) {
	// ±æÀÌ°¡ 1ÀÌ»ó 20ÀÌÇÏ
	// °ø¹é·ù´Â ÀüÇô µé¾î°¡ÀÖÁö ¾ÊÀ½
	// °¢ ¹®ÀÚ´Â ¼ıÀÚ, ·Î¸¶ÀÚ ´ë¼Ò¹®ÀÚ, ÀÚ¸ğ Á¶ÇÕÀÌ ¿Ï¼ºµÈ ÇÑ±Û 
	wregex name_reg(L"^[0-9°¡-ÆRa-zA-Z]{1,20}$");
	if (!regex_match(str, name_reg)) {
		return false;
	}

	// ¼ıÀÚ·Î¸¸ ±¸¼ºµÇ¸é ¾ÈµÊ
	name_reg = L"^[0-9]+$";
	if (regex_match(str, name_reg)) {
		return false;
	}

	// "±³¾ç"°ú ÀÏÄ¡ÇÏ¸é ¾ÈµÊ
	if (str.compare(L"±³¾ç") == 0) {
		return false;
	}

	// ¸¶Áö¸·ÀÌ "ÇĞ°ú" ¶Ç´Â "ÇĞºÎ"·Î ³¡³ª¸é ¾ÈµÊ
	name_reg = L".*(ÇĞ°ú|ÇĞºÎ)$";
	if (regex_match(str, name_reg)) {
		return false;
	}
	return true;
}

bool check_Scredit(wstring const& str) {
	// 1,2,3 Áß ÇÏ³ªÀÇ ¼ıÀÚ¸¸ °¡´É
	wregex credit_reg(L"[1-3]");
	if (!regex_match(str, credit_reg)) {
		return false;
	}
	return true;
}

bool check_Smajor(wstring const& str) {
	// "±³¾ç"°ú Á¤È®È÷ ÀÏÄ¡ÇÏ´Â ¹®ÀÚ¿­
	if (str.compare(L"±³¾ç") == 0) {
		return true;
	}

	// ±æÀÌ°¡ 1ÀÌ»ó 10ÀÌÇÏ
	// °ø¹é·ù´Â ÀüÇô µé¾î°¡ ÀÖÁö ¾ÊÀ½
	// °¢ ¹®ÀÚ´Â ¼ıÀÚ, ·Î¸¶ÀÚ ´ë¼Ò¹®ÀÚ, ÀÚ¸ğ Á¶ÇÕÀÌ ¿Ï¼ºµÈ ÇÑ±Û
	// "ÇĞ°ú" ¶Ç´Â "ÇĞºÎ"·Î ³¡³ª´Â ¹®ÀÚ¿­
	wregex major_reg(L"^[0-9°¡-ÆRa-zA-Z]{0,8}(ÇĞ°ú|ÇĞºÎ)$");
	if (!regex_match(str, major_reg)) {
		return false;
	}
	return true;
}

bool check_Sgrade(wstring const& str) {
	// 0,1,2,3,4 Áß ÇÏ³ªÀÇ ¼ıÀÚ¸¸ °¡´É
	wregex grade_reg(L"[0-4]");
	if (!regex_match(str, grade_reg)) {
		return false;
	}
	return true;
}

bool check_Stime(wstring const& str) {
	map<wchar_t, int> days = { {L'¿ù',1},{L'È­',2},{L'¼ö',3},{L'¸ñ',4},{L'±İ',5},{L'Åä',6},{L'ÀÏ',7} };

	// [¿äÀÏ] + ¼ıÀÚ2°³ + '-' ¼ıÀÚ2°³
	wregex time_reg1(L"^[¿ùÈ­¼ö¸ñ±İÅäÀÏ][0-9]{2}-[0-9]{2}$");
	if (regex_match(str, time_reg1)) {
		int t1 = stoi(str.substr(1, 2));
		int t2 = stoi(str.substr(4, 2));

		// ±³½Ã°¡ 1ÀÌ»ó 22ÀÌÇÏ Ã¼Å©
		if (t1 == 0 || t1 > 22 || t2 == 0 || t2 > 22) {
			return false;
		}

		// ¾Õ ±³½Ã <= µŞ ±³½Ã Ã¼Å©
		if (t1 > t2) {
			return false;
		}

		return true;
	}

	// [¿äÀÏ] + ¼ıÀÚ2°³ + '-' ¼ıÀÚ2°³ + ',' + [¿äÀÏ] + ¼ıÀÚ2°³ + '-' ¼ıÀÚ2°³
	wregex time_reg2(L"^[¿ùÈ­¼ö¸ñ±İÅäÀÏ][0-9]{2}-[0-9]{2},[¿ùÈ­¼ö¸ñ±İÅäÀÏ][0-9]{2}-[0-9]{2}$");
	if (regex_match(str, time_reg2)) {
		int d1 = days[str[0]];
		int d2 = days[str[7]];

		int t1 = stoi(str.substr(1, 2));
		int t2 = stoi(str.substr(4, 2));
		int t3 = stoi(str.substr(8, 2));
		int t4 = stoi(str.substr(11, 2));

		// ¾Õ ¿äÀÏ < µŞ ¿äÀÏ Ã¼Å©
		if (d1 >= d2) {
			return false;
		}

		// ±³½Ã°¡ 1ÀÌ»ó 22ÀÌÇÏ Ã¼Å©
		if (t1 == 0 || t1 > 22 || t2 == 0 || t2 > 22 || t3 == 0 || t3 > 22 || t4 == 0 || t4 > 22) {
			return false;
		}

		// ¾Õ ±³½Ã <= µŞ ±³½Ã Ã¼Å©
		if (t1 > t2 || t3 > t4) {
			return false;
		}

		return true;
	}

	return false;
}

bool check_Scapacity(wstring const& str) {
	// °ø¹é·ù´Â ÀüÇô µé¾î°¡Áö ¾ÊÀ½
	// ¼±Çà 0ÀÌ ÀÖ¾îµµ µÇ¸ç, ¼±Çà 0À» Æ÷ÇÔÇÏ¿© 1ÀÚ¸® ÀÌ»ó 3ÀÚ¸® ÀÌÇÏ
	wregex capacity_reg(L"[0-9]{1,3}");
	if (!regex_match(str, capacity_reg)) {
		return false;
	}
	return true;
}

bool check_Smajor_Sgrade_Match(wstring const& smajor, wstring const& sgrade, int line) {
	int grade = stoi(sgrade);
	if (smajor.compare(L"±³¾ç") == 0) { // ±³¾çÀÎ °æ¿ì
		if (grade != 0) { // ÇĞ³âÀÌ 0ÀÌ ¾Æ´Ï¸é
			nonzero_liberal_arts_lines.push_back(line);
			return false;
		}
	}
	else { // Àü°øÀÎ °æ¿ì
		if (grade == 0) { // ÇĞ³âÀÌ 0ÀÌ¸é
			zero_major_lines.push_back(line);
			return false;
		}
	}
	return true;
}

bool check_Sprof(wstring const& str) {
	// °¢ ¹®ÀÚ´Â ¼ıÀÚ, ·Î¸¶ÀÚ ´ë¼Ò¹®ÀÚ, ÀÚ¸ğ Á¶ÇÕÀÌ ¿Ï¼ºµÈ ÇÑ±Û
	// ¼ıÀÚ°¡ Æ÷ÇÔµÉ °æ¿ì Á¦ÀÏ ¸¶Áö¸· ÇÑ ¹®ÀÚ¿¡¸¸ »ç¿ë °¡´É
	// ±æÀÌ´Â ¼ıÀÚ¸¦ Á¦¿ÜÇÏ°í 1 ÀÌ»ó 10 ÀÌÇÏ
	// °ø¹é·ù´Â ÀüÇô µé¾î°¡ÀÖÁö ¾ÊÀ½
	wregex prof_reg(L"^[°¡-ÆRa-zA-Z]{1,10}[0-9]?$");
	if (!regex_match(str, prof_reg)) {
		return false;
	}
	return true;
}

bool check_Sroom(wstring const& str) {
	// [°Ç¹°] + ¼ıÀÚ 3°³
	wregex room_reg(L"^[»õ¹ı°øÀÎ¿¹][0-9]{3}$");
	if (!regex_match(str, room_reg)) {
		return false;
	}

	// ¸Ç ¿ŞÂÊ ¼ıÀÚ 1 ÀÌ»ó 5 ÀÌÇÏ
	int floor = stoi(str.substr(1, 1));
	if (floor < 1 || floor > 5) {
		return false;
	}

	// ¿À¸¥ÂÊ µÎ ¼ıÀÚ 1 ÀÌ»ó 19 ÀÌÇÏ
	int roomNum = stoi(str.substr(2, 2));
	if (roomNum < 1 || roomNum > 19) {
		return false;
	}
	return true;
}

bool check_UID(wstring const& str) {
	// ¹®ÀÚ¿­ ³» ¸ğµç °¢ ¹®ÀÚ´Â ¼ıÀÚ·Î¸¸ ±¸¼º
	// ¹®ÀÚ¿­ ±æÀÌ°¡ 9
	wregex id_reg(L"^[0-9]{9}$");
	if (!regex_match(str, id_reg)) {
		return false;
	}
	return true;
}

bool check_Uname(wstring const& str) {
	// ±æÀÌ°¡ 1ÀÌ»ó 10ÀÌÇÏ
	// °¢ ¹®ÀÚ´Â ·Î¸¶ÀÚ ´ë¼Ò¹®ÀÚ, ÀÚ¸ğ Á¶ÇÕÀÌ ¿Ï¼ºµÈ ÇÑ±Û 
	// °ø¹é·ù´Â ÀüÇô µé¾î°¡ÀÖÁö ¾ÊÀ½
	wregex name_reg(L"^[°¡-ÆRa-zA-Z]{1,10}$");
	if (!regex_match(str, name_reg)) {
		return false;
	}
	return true;
}

bool check_Umajor(wstring const& str) {
	// ±æÀÌ°¡ 1ÀÌ»ó 10ÀÌÇÏ
	// °ø¹é·ù´Â ÀüÇô µé¾î°¡ ÀÖÁö ¾ÊÀ½
	// °¢ ¹®ÀÚ´Â ¼ıÀÚ, ·Î¸¶ÀÚ ´ë¼Ò¹®ÀÚ, ÀÚ¸ğ Á¶ÇÕÀÌ ¿Ï¼ºµÈ ÇÑ±Û
	// "ÇĞ°ú" ¶Ç´Â "ÇĞºÎ"·Î ³¡³ª´Â ¹®ÀÚ¿­
	wregex major_reg(L"^[0-9°¡-ÆRa-zA-Z]{0,8}(ÇĞ°ú|ÇĞºÎ)$");
	if (!regex_match(str, major_reg)) {
		return false;
	}
	return true;
}

bool check_Ugrade(wstring const& str) {
	// 1,2,3,4 Áß ÇÏ³ªÀÇ ¼ıÀÚ¸¸ °¡´É
	wregex grade_reg(L"[1-4]");
	if (!regex_match(str, grade_reg)) {
		return false;
	}
	return true;
}

bool check_Acquisition_Credit(wstring const& str) {
	// °ø¹é·ù´Â ÀüÇô µé¾î°¡Áö ¾ÊÀ½
	// ¼±Çà 0ÀÌ ÀÖ¾îµµ µÇ¸ç, ¼±Çà 0À» Æ÷ÇÔÇÏ¿© 1ÀÚ¸® ÀÌ»ó 3ÀÚ¸® ÀÌÇÏ
	wregex grade_reg(L"[0-9]{1,3}");
	if (!regex_match(str, grade_reg)) {
		return false;
	}

	// 200ÀÌÇÏ¿©¾ß ÇÔ
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
		case L'¿ù':
			col = 0;
			break;
		case L'È­':
			col = 1;
			break;
		case L'¼ö':
			col = 2;
			break;
		case L'¸ñ':
			col = 3;
			break;
		case L'±İ':
			col = 4;
			break;
		case L'Åä':
			col = 5;
			break;
		case L'ÀÏ':
			col = 6;
		}

		if (!profTimeTable.count(sprof)) {	// sprof Å°°¡ map¿¡ ¾øÀ¸¸é ¹è¿­ µ¿ÀûÇÒ´ç ÈÄ map¿¡ Ãß°¡
			vector<int>(*profArr)[22][7] = new (vector<int>[1][22][7]);
			profTimeTable[sprof] = profArr;
		}

		for (int i = stoi(wstr2str(stime.substr(1, 2))); i <= stoi(wstr2str(stime.substr(4, 2))); i++) {
			if ((*profTimeTable[sprof])[i - 1][col].size() >= 1) {
				is_duplicated_time_prof = true;
			}
			(*profTimeTable[sprof])[i - 1][col].push_back(line);
		}

		if (!roomTimeTable.count(sroom)) {	// sroom Å°°¡ map¿¡ ¾øÀ¸¸é ¹è¿­ µ¿ÀûÇÒ´ç ÈÄ map¿¡ Ãß°¡
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
	map<int, wchar_t> days = { {0,L'¿ù'},{1,L'È­',},{2,L'¼ö'},{3,L'¸ñ'},{4,L'±İ'},{5,L'Åä'},{6,L'ÀÏ'} };

	for (auto it = profTimeTable.begin(); it != profTimeTable.end(); it++) {
		for (int j = 0; j < 7; j++) {
			for (int i = 0; i < 22; i++) {
				int v_size = ((*(it->second))[i][j]).size();
				if (v_size > 1) {
					wcout << "\"" << it->first << "\" ";
					wprintf(L"±³¼öÀÇ °ú¸ñµé Áß \"%c%02d±³½Ã\"°¡ °ãÄ¡´Â °ú¸ñµéÀÌ Á¸ÀçÇÕ´Ï´Ù.\n#", days[j], i + 1);
					for (int k = 0; k < v_size; k++) {
						wprintf(L"%dÇà", ((*(it->second))[i][j])[k]);
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
	map<int, wchar_t> days = { {0,L'¿ù'},{1,L'È­',},{2,L'¼ö'},{3,L'¸ñ'},{4,L'±İ'},{5,L'Åä'},{6,L'ÀÏ'} };

	for (auto it = roomTimeTable.begin(); it != roomTimeTable.end(); it++) {
		for (int j = 0; j < 7; j++) {
			for (int i = 0; i < 22; i++) {
				int v_size = ((*(it->second))[i][j]).size();
				if (v_size > 1) {
					wcout << "\"" << it->first << "\" ";
					wprintf(L"°­ÀÇ½Ç¿¡¼­ ¿­¸° °ú¸ñµé Áß \"%c%02d±³½Ã\"°¡ °ãÄ¡´Â °ú¸ñµéÀÌ Á¸ÀçÇÕ´Ï´Ù.\n#", days[j], i + 1);
					for (int k = 0; k < v_size; k++) {
						wprintf(L"%dÇà", ((*(it->second))[i][j])[k]);
						(k == v_size - 1) ? printf("\n") : printf(",");
					}
				}
			}
		}
	}
	gotoClassic;
}