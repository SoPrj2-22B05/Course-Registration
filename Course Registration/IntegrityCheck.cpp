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
	wfstream f(L"»ç¿ëÀÚ µ¥ÀÌÅÍ ÆÄÀÏ.txt");

	if (!f.is_open()) {
		wprintf(L"¿À·ù : È¨ °æ·Î¿¡ °ú¸ñ µ¥ÀÌÅÍ ÆÄÀÏ ¶Ç´Â »ç¿ëÀÚ µ¥ÀÌÅÍ ÆÄÀÏÀÌ ¾ø½À´Ï´Ù. ÇÁ·Î±×·¥À» Á¾·áÇÕ´Ï´Ù.????ÇÁ·Î±×·¥ À§Ä¡ Ãâ·Â????\n");
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

		if (!check_UID(data[0])) { // ÇĞ¹ø(±³¹ø) ¹®¹ı Çü½Ä Ã¼Å©
			User_File_Grammar_Error_Line.push_back(lineCount);
			continue;
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
			}
			/*gotoClassic;
			cout << "°ü¸®ÀÚÀÔ´Ï´Ù." << endl;
			gotoUTF;*/
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
			/*gotoClassic;
			cout << "ÇĞ»ıÀÔ´Ï´Ù." << endl;
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
		printf("¿À·ù : »ç¿ëÀÚ µ¥ÀÌÅÍ ÆÄÀÏÀÇ ¹®¹ı ±ÔÄ¢ÀÌ ¿Ã¹Ù¸£Áö ¾Ê½À´Ï´Ù.\n# ");
		for (int i = 0; i < num_Error; i++) {
			printf("%dÇà", User_File_Grammar_Error_Line[i]);
			(i == num_Error - 1) ? printf("\n") : printf(",");
		}
	}
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