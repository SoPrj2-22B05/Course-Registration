#pragma once
#include "SubjectData.h"
#include "Search.h"
#include "Administrator.h"
#include "Delete.h"
#include "Alter.h"
#include "Add.h"
#include "prompt.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <vector>
#include <atlconv.h>
#define ORDER_NUM 5
namespace fs = std::filesystem;
using namespace std;

/*
void User_info_menu();
void Student_menu();
void print_manual();
void add_check(string str);
void del_check(string str);
void alter_check(string str);
void add_help_print();
void del_help_print();
void alter_help_print();
bool start_check();
*/
wstring& trim(wstring& s, const wchar_t* t = L" \t\n\r\f\v");
boolean restart = false;
string ID, name;

string w2s(const wstring& _src) {
    USES_CONVERSION;
    return string(W2A(_src.c_str()));
};

void User_info_menu() {
    string num[10] = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" };
    cout << "학번 (또는 교번)을 입력해주세요" << endl;
    cout << "Course Registration > ";
    getline(cin, ID);   //추가한 코드
    ID.erase(0, ID.find_first_not_of(" \t\n\r\f\v"));
    ID.erase(ID.find_last_not_of(" \t\n\r\f\v") + 1);

    if (ID.compare("종료") == 0 || ID.compare("exit") == 0) {
        cout << "프로그램을 종료합니다.";
        exit(0);
    }

    if (ID.length() != 9) { //길이는 9
        cout << "해당하는 학번(또는 교번)이 없습니다." << endl;
        return;
    }

    int check = 0;
    for (int i = 0; i < ID.length(); i++) {
        for (int j = 0; j < 10; j++) {
            if (num[j].compare(ID.substr(i, 1)) == 0) {
                check++;
            }
        }
    }
    if (check != ID.length()) {
        cout << "해당하는 학번(또는 교번)이 없습니다." << endl;
        return;
    }
    else check = 0;
    //숫자로 구성되야함

    wstring wID, wname;
    vector<wstring> data; // id  name  major  grade  acquisition_credit
    wstring line, str;
    wstringstream ss;
    wID.assign(ID.begin(), ID.end());
    bool c = false; //true면 파일 안에 학번 있음. false면 없음.
    string filename1 = "사용자 데이터 파일.txt";
    wfstream f1;
    f1.imbue(locale("ko_KR.UTF-8"));
    f1.open(filename1);
    if (f1.is_open()) { // 학번 이름 긁어오기
        while (getline(f1, line)) {
            wstring tmpid = line.substr(0, 9);
            if (tmpid == wID) {
                ss.str(line);
                while (getline(ss, str, L'\t')) {
                    //str = trim(str);
                    if (str != L"") {
                        data.push_back(str);
                    }
                }
                wname = data[1];
                c = true;
                break;
            }
        }
        f1.close();
    }
    name = w2s(wname);

    if (!c) {
        cout << "해당하는 학번(또는 교번)이 없습니다." << endl;
        return;
    }
    else {
        if ((ID.substr(0, 4)).compare("0000") == 0) {
            cout << "관리자 주 프롬프트로 이동합니다" << endl;
            Administrator_menu();
        }
        else {
            cout << "학생 주 프롬프트로 이동합니다" << endl;
            //print_manual();
            //cin.ignore();
            do {
                Student_menu();
            } while (restart == true);
        }
    }
}
void print_manual() {
    cout << "-------------------------------------------------------------------" << endl;
    cout << "명령어군         | 올바른 인자들     | 설명" << endl;
    cout << "-------------------------------------------------------------------" << endl;
    cout << ". logout 로그아웃| 없음              | 로그아웃하고 사용자 정보" << endl;
    cout << "                 |                   | 입력 프롬프트로 이동" << endl;
    cout << "#   find    검색 | 없거나, 검색요소  | 데이터 파일에서 인자들 검색" << endl;
    cout << "                 | 별 각 1개 이하    |" << endl;
    cout << "+    add    추가 | 과목번호, 마일리지| 데이터 파일에 새 레코드 추가" << endl;
    cout << "                 |                   |" << endl;
    cout << "-  delete   삭제 | 과목번호          | 데이터 파일에서 기존 레코드" << endl;
    cout << "                 |                   | 삭제" << endl;
    cout << "~  alter    변경 | 과목번호, 마일리지| 데이터 파일에서 기존 레코드" << endl;
    cout << "                 |                   | 변경" << endl;
    cout << "-------------------------------------------------------------------" << endl;
}
void Student_menu() {
    restart = false;
    string logout[ORDER_NUM] = { "logout", "l", "로그아웃", "ㄹㄱㅇㅇ", "." };
    string find[ORDER_NUM] = { "find", "f", "검색", "ㄱㅅ", "#" };
    string add[ORDER_NUM] = { "add", "ad","추가", "ㅊㄱ", "+" };
    string del[ORDER_NUM] = { "delete", "d", "삭제", "ㅅㅈ", "-" };
    string alter[ORDER_NUM] = { "alter", "alt", "변경", "ㅂㄱ", "~" };
    string str;
    cout << "Course Registration > ";
    getline(cin, str);
    str.erase(0, str.find_first_not_of(" \t\n\r\f\v"));
    str.erase(str.find_last_not_of(" \t\n\r\f\v") + 1);
    //char separator = ' ';
    string stu_input[2];
    //istringstream iss(str);
    //string str_buf;
    string commandExcept;
    int i = 0;
    bool sORf = true;
    int realOrderNum = -1;

    if (str.compare("") == 0) { //빈 문자열이면 즉시 리턴
        print_manual();
        restart = true;
        return;
    }

    stu_input[0] = str.substr(0, str.find_first_of(" \n\r\t\f\v"));
    for (int k = 0; k < ORDER_NUM; k++) {
        if (logout[k].compare(stu_input[0]) == 0) { realOrderNum = 0; break; }
        if (find[k].compare(stu_input[0]) == 0) { realOrderNum = 1; break; }
        if (add[k].compare(stu_input[0]) == 0) { realOrderNum = 2; break; }
        if (del[k].compare(stu_input[0]) == 0) { realOrderNum = 3; break; }
        if (alter[k].compare(stu_input[0]) == 0) { realOrderNum = 4; break; }
    }

    if (str.find_first_of(" \t\f\v") < 0 || str.find_first_of(" \t\f\v") >= str.size()) {   //입력에 횡공백류 하나도 없으면 리턴
        if (realOrderNum == -1) {
            print_manual();
            restart = true;
            return;
        }
    }

    stu_input[1] = "";
    if (str.find_first_of(" \t\f\v") >= 0 && str.find_first_of(" \t\f\v") < str.size()) {   
        
        commandExcept = str.substr(str.find_first_of(" \t\f\v"));
        stu_input[1] = commandExcept.substr(commandExcept.find_first_not_of(" \t\f\v"));
        

        if (stu_input[1].find_first_of(" \t\f\v") >= 0 && stu_input[1].find_first_of(" \t\f\v") < stu_input[1].size()) {
            switch (realOrderNum) {
            case 0:
                cout << "오류 : 문법에 맞지 않습니다." << endl;
                break;
            case 1:
                find_help_print();
                break;
            case 2:
                add_help_print();
                break;
            case 3:
                del_help_print();
                break;
            case 4:
                alter_help_print();
            }
            cout << "문법 형식에 위배됩니다. 입력 인자들 사이에 공백이 있으면 안 됩니다." << endl;
            restart = true;
            return;
        }

        
        char* chars = new char[stu_input[1].length() + 1];
        stu_input[1].copy(chars, stu_input[1].length());
        chars[stu_input[1].length()] = '\0';
        for (int j = 0; j < stu_input[1].length(); j++)
        {
            // 아스키코드 상의 특수문자가 있으면 오류 출력
            // 과목이름이 알파벳으로만 구성되어 있으면 걍 알파벳만 아스키코드 포함시킨 뒤 not 하면 되는데...
            // 한글이 껴있다보니 하트나 네모 등의 특수문자까지 제거하려면 모든 경우의 수를 일일이 다 제거해줘야 돼서 현실적으로 어려울 것 같습니다. 
            if (!((chars[j] >= 48 && chars[j] <= 57) || chars[j] == 47)) // 47은 '/'라서 46까지만
            {
                cout << "문법 형식에 위배됩니다. 입력 인자들 사이에 '/'를 제외한 특수 문자가 있으면 안 됩니다." << endl;
                restart = true;
                return;
            }
        }
        
    }
    
    bool check2 = false;
    /*
    if (str.compare("") == 0) {
        print_manual();
        restart = true;
        return;
    }
    */

    switch (realOrderNum) {
    case 0:
        return;
        break;
    case 1:
        Search(str);
        check2 = true;
        break;
    case 2:
        if (start_check()) {
            add_check(stu_input[1]);
            check2 = true;
        }
        break;
    case 3:
        if (start_check()) {
            del_check(stu_input[1]);
            check2 = true;
        }
        break;
    case 4:
        if (start_check()) {
            alter_check(stu_input[1]);
            check2 = true;
        }
    }

    if (!check2) {  //나머지 입력
        print_manual();
    }
    restart = true;
    return;
    //cout << "stu_input[0] : " << stu_input[0] << endl;
    //cout << "stu_input[1] : " << stu_input[1] << endl;
    //str_buf = str.substr(str.find_first_of(" \t\f\v"), (str.find_last_of(" \t\f\v") - str.find_first_of(" \t\f\v") + 1));
    //cout << str_buf << "." << endl;

    

    
    /*
    while (getline(iss, str_buf, separator)) {
        if (i <= 1) {
            if (str_buf.compare("") == 0) { continue; }
            cout << str_buf << endl;
            stu_input[i] = str_buf;
            i++;
        }
        else {
            cout << "문법 형식에 위배됩니다. 입력 인자들 사이에 공백이 있으면 안 됩니다." << endl;
            sORf = false;
            break;
        }
    }
    */
    

    
    /*
    for (int i = 0; i < ORDER_NUM; i++) {
        if (logout[i].compare(stu_input[0]) == 0) {
            return;
        }
        else if (find[i].compare(stu_input[0]) == 0) {
            Search(str);
            check2 = true;
        }
        else if (add[i].compare(stu_input[0]) == 0) {
            if (start_check()) {
                add_check(stu_input[1]);
                check2 = true;
            }
        }
        else if (del[i].compare(stu_input[0]) == 0) {
            if (start_check()) {
                del_check(stu_input[1]);
                check2 = true;
            }
        }
        else if (alter[i].compare(stu_input[0]) == 0) {
            if (start_check()) {
                alter_check(stu_input[1]);
                check2 = true;
            }
        }
    }
    */
    
}

void add_check(string str) {
    char separator = '/';
    string num[10] = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" };
    istringstream iss(str);
    string str_buf;
    string parameter[2];
    int i = 0;
    while (getline(iss, str_buf, separator)) {
        if (i <= 1) {
            parameter[i] = str_buf;
        }
        i++;
    }
    if (str.compare("") == 0) {
        add_help_print();
        return;
    }
    if (str[str.size() - 1] == '/') {
        add_help_print();
        return;
    }
    if (i > 2) { //인자가 2개 초과체크
        add_help_print();
        return;
    }
    //과목번호 체크
    if (parameter[0].length() != 4) {
        add_help_print();
        return;
    } //길이는 4
    int check = 0;
    for (int i = 0; i < parameter[0].length(); i++) {
        for (int j = 0; j < 10; j++) {
            if (num[j].compare(parameter[0].substr(i, 1)) == 0) {
                check++;
            }
        }
    }
    if (check != parameter[0].length()) {
        add_help_print();
        return;
    }
    else check = 0;
    //마일리지 체크
    if (parameter[1].length() < 1 || parameter[1].length() > 3) {
        add_help_print();
        return;
    } //길이는 1 ~ 3
    check = 0;
    for (int i = 0; i < parameter[1].length(); i++) {
        for (int j = 0; j < 10; j++) {
            if (num[j].compare(parameter[1].substr(i, 1)) == 0) {
                check++;
            }
        }
    }
    if (check != parameter[1].length()) {
        add_help_print();
        return;
    }
    else check = 0; // 숫자만 있는지
    Add(str, ID, name);
}
void add_help_print() {
    cout << "원하는 과목을 수강신청 추가하는 명령어" << endl;
    cout << "동의어: +  추가  ㅊㄱ  add  ad" << endl;
    cout << "인자: 1개의 과목번호와 1개의 마일리지" << endl;
    cout << "동작: 과목번호와 마일리지를 입력받고, 과목번호에 해당하는 과목에 마일리지를 배팅해 수강신청을 추가합니다." << endl;
}
void del_check(string str)
{
    char separator = '/';
    string num[10] = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" };
    istringstream iss(str);
    string str_buf;
    string parameter;
    int i = 0;
    while (getline(iss, str_buf, separator)) {
        if (i == 0) {
            parameter = str_buf;
        }
        i++;
    }
    if (str.compare("") == 0) {
        del_help_print();
        return;
    }
    if (i > 1) { //인자 1개 초과 체크
        del_help_print();
        return;
    }
    //과목번호 체크
    if (parameter.length() != 4) {
        del_help_print();
        return;
    } //길이는 4
    int check = 0;
    for (int i = 0; i < parameter.length(); i++) {
        for (int j = 0; j < 10; j++) {
            if (num[j].compare(parameter.substr(i, 1)) == 0) {
                check++;
            }
        }
    }
    if (check != parameter.length()) {
        add_help_print();
        return;
    }
    else check = 0;
    Delete(parameter, ID, name);
}
void del_help_print() {
    cout << "삭제를 원하는 과목을 수강신청 취소하는 명령어" << endl;
    cout << "동의어: -  삭제  ㅅㅈ  delete  d" << endl;
    cout << "인자: 1개의 과목번호" << endl;
    cout << "동작: 과목번호를 입력받고, 과목번호에 해당하는 과목을 삭제합니다." << endl;
}
void alter_check(string str)
{
    char separator = '/';
    string num[10] = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" };
    istringstream iss(str);
    string str_buf;
    string parameter[2];
    int i = 0;
    while (getline(iss, str_buf, separator)) {
        if (i <= 1) {
            parameter[i] = str_buf;
        }
        i++;
    }
    if (str.compare("") == 0) {
        alter_help_print();
        return;
    }
    if (str[str.size() - 1] == '/') {
        alter_help_print();
        return;
    }
    if (i > 2) { //인자가 2개 초과체크
        alter_help_print();
        return;
    }
    //과목번호 체크
    if (parameter[0].length() != 4) {
        alter_help_print();
        return;
    } //길이는 4
    int check = 0;
    for (int i = 0; i < parameter[0].length(); i++) {
        for (int j = 0; j < 10; j++) {
            if (num[j].compare(parameter[0].substr(i, 1)) == 0) {
                check++;
            }
        }
    }
    if (check != parameter[0].length()) {
        add_help_print();
        return;
    }
    else check = 0;
    //마일리지 체크
    if (parameter[1].length() < 1 || parameter[1].length() > 3) {
        alter_help_print();
        return;
    } //길이는 1 ~ 3
    check = 0;
    for (int i = 0; i < parameter[1].length(); i++) {
        for (int j = 0; j < 10; j++) {
            if (num[j].compare(parameter[1].substr(i, 1)) == 0) {
                check++;
            }
        }
    }
    if (check != parameter[1].length()) {
        add_help_print();
        return;
    }
    else check = 0;
    Alter(str, ID, name);
}
void alter_help_print() {
    cout << "이미 신청한 과목에 대해 분배한 마일리지를 변경하는 명령어" << endl;
    cout << "동의어: ~  변경  ㅂㄱ  alter  alt" << endl;
    cout << "인자: 1개의 과목번호와 1개의 마일리지" << endl;
    cout << "동작: 과목번호와 마일리지를 입력받아, 해당 과목번호에 분배된 기존의 마일리지를 인자로 들어온 마일리지로 변경합니다." << endl;
}

void find_help_print() {
    cout << "데이터 파일에서 원하는 과목을 검색하는 명령어" << endl;
    cout << "동의어 : # 검색 ㄱㅅ find f" << endl;
    cout << "인자 : 검색요소(과목번호, 과목이름, 학년, 전공/교양)" << endl;
    cout << "동작 : 검색요소를 입력받고, 필터링된 과목들을 출력합니다." << endl;
}

bool start_check() {
    wstring dir = fs::current_path();
    wfstream isOn;
    isOn.open(dir + L"\\Course_Registration_Is_On.txt");
    if (!isOn.is_open()) {
        cout << "아직 수강신청이 시작되지 않았습니다." << endl;
        return false;
    }
    else {
        return true;
    }
}