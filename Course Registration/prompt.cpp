#include "SubjectData.h"
#include "Search.h"
#include "Administrator.h"
#include "Delete.h"
#include "Alter.h"
#include "Add.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
#define ORDER_NUM 5
using namespace std;

void User_info_menu();
void Student_menu();
void print_manual();
void add_check(string str);
void del_check(string str);
void alter_check(string str);
void add_help_print();
void del_help_print();
void alter_help_print();

void User_info_menu() {
    string ID;
    string num[10] = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" };
    cout << "학번 (또는 교번)을 입력해주세요" << endl;
    cin >> ID;
    size_t npos;
   
    npos = ID.find_first_not_of(' ');
    ID.erase(0, npos);
    npos = ID.find_last_not_of(' ');
    ID.erase(npos + 1); //앞뒤 공백 제거

    if (ID.compare("종료") == 0 || ID.compare("exit") == 0) {
        cout << "프로그램을 종료합니다.";
        exit(0);
    }
    bool c = false; //true면 파일 안에 학번 있음. false면 없음.
    for (int i = 0; i < 10000; i++) {
        if (Subject[i]->id.compare(ID)) {
            c = true;
            break;
        }
    }
    if (!c) {
        exit(0);
    }
    if (ID.length() != 9) { //길이는 9
        cout << "해당하는 학번(또는 교번)이 없습니다.";
        return;
    }
    else {
        bool check = false; //true면 숫자임, false면 숫자아님
        for (int i = 0; i < ID.length(); i++) {
            for (int j = 0; j < 10; j++) {
                if (num[j].compare(ID.substr(i, 1)) == 0) {
                    check = true;
                }
            }
            if (!check) {
                cout << "해당하는 학번(또는 교번)이 없습니다.";
                return;
            }
        } //숫자로 구성되야함
        
        if ((ID.substr(0, 4)).compare("0000") == 0) {
            cout << "관리자 주 프롬프트로 이동합니다" << endl;
            Administrator_menu();
        }
        else {
            cout << "학생 주 프롬프트로 이동합니다" << endl;
            Student_menu();
        }
    }
}
void print_manual() {
    cout << "-------------------------------------------------------------------" << endl;
    cout << "명령어군         | 올바른 인자들     | 설명" << endl;
    cout << "-------------------------------------------------------------------" << endl;
    cout << ". logout 로그아웃| 없음              | 로그아웃하고 사용자정보" << endl;
    cout << "                 |                   | 입력 프롬프트로 이동" << endl;
    cout << "#   find    검색 | 없거나, 검색요소  | 데이터 파일에서 인자들 검색" << endl;
    cout << "                 | 별 각 1개 이하    |" << endl;
    cout << "+    add    추가 | 과목번호, 마일리지| 데이터 파일에 새 레코드 추가" << endl;
    cout << "                 |                   |" << endl;
    cout << "-  delete   삭제 | 과목번호          | 데이터 파일에서 기존 레코드" << endl;
    cout << "                 |                   | 삭제" << endl;
    cout << "~  alt      변경 | 과목번호, 마일리지| 데이터 파일에서 기존 레코드" << endl;
    cout << "                 |                   | 변경" << endl;
    cout << "-------------------------------------------------------------------" << endl;
}
void Student_menu() {
    string logout[ORDER_NUM] = { "logout", "l", "로그아웃", "ㄹㄱㅇㅇ", "." };
    string find[ORDER_NUM] = { "find", "f", "검색", "ㄱㅅ", "#" };
    string add[ORDER_NUM] = { "add", "ad","추가", "ㅊㄱ", "+" };
    string del[ORDER_NUM] = { "delete", "d", "삭제", "ㅅㅈ", "-" };
    string alter[ORDER_NUM] = { "alter", "alt", "변경", "ㅂㄱ", "~" };
    string str;
    getline(cin, str);
    char separator = ' ';
    string stu_input[2];
    istringstream iss(str);
    string str_buf;
    int i = 0;
    while (getline(iss, str_buf, separator)) {
        if (i <= 1) {
            stu_input[i] = str_buf;
        }
        i++;
    }

    for (int i = 0; i < ORDER_NUM; i++) {
        if (logout[i].compare(stu_input[0]) == 0) {
            User_info_menu();
            return;
        }
        else if (find[i].compare(stu_input[0]) == 0) {
            Search(str);
            return;//검색은 따로 추가
        }
        else if (add[i].compare(stu_input[0]) == 0) {
            add_check(stu_input[1]);
            return;
        }
        else if (del[i].compare(stu_input[0]) == 0) {
            del_check(stu_input[1]);
            return;
        }
        else if (alter[i].compare(stu_input[0]) == 0) {
            alter_check(stu_input[1]);
            return;
        }
    }
    print_manual();
    Student_menu();
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
    if (i > 2) { //인자가 2개 초과체크
        add_help_print();
        Student_menu();
        return;
    }
    //과목번호 체크
    if (parameter[0].length() != 4) {
        add_help_print();
        Student_menu();
        return;
    } //길이는 4
    bool check = false; //true면 숫자임, false면 숫자아님
    for (int i = 0; i < parameter[0].length(); i++) {
        for (int j = 0; j < 10; j++) {
            if (num[j].compare(parameter[0].substr(i, 1)) == 0) {
                check = true;
            }
        }
        if (!check) {
            add_help_print();
            Student_menu();
            return;
        }
    } //숫자로 구성되야함
    //마일리지 체크
    if (parameter[1].length() < 1 || parameter[1].length() > 3) {
        add_help_print();
        Student_menu();
        return;
    } //길이는 1 ~ 3
    check = false; //true면 숫자임, false면 숫자아님
    for (int i = 0; i < parameter[1].length(); i++) {
        for (int j = 0; j < 10; j++) {
            if (num[j].compare(parameter[1].substr(i, 1)) == 0) {
                check = true;
            }
        }
        if (!check) {
            add_help_print();
            Student_menu();
            return;
        }
    } //숫자로 구성되야함
    if (parameter[1].length() > 1) {
        for (int i = 0; i < parameter[1].length(); i++) {
            if ((parameter[1].substr(i, 1).compare("0")) == 0) {
                parameter[1].erase(i, 1);
            }
        }
        int mile = stoi(parameter[1]);
    }//마일리지 0제거
    Add(str);
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
    string parameter[1];
    int i = 0;
    while (getline(iss, str_buf, separator)) {
        if (i <= 0) {
            parameter[i] = str_buf;
        }
        i++;
    }
    if (i > 1) { //인자 1개 초과 체크
        del_help_print();
        Student_menu();
        return;
    }
    //과목번호 체크
    if (parameter[0].length() != 4) {
        del_help_print();
        Student_menu();
        return;
    } //길이는 4
    bool check = false; //true면 숫자임, false면 숫자아님
    for (int i = 0; i < parameter[0].length(); i++) {
        for (int j = 0; j < 10; j++) {
            if (num[j].compare(parameter[0].substr(i, 1)) == 0) {
                check = true;
            }
        }
        if (!check) {
            del_help_print();
            Student_menu();
            return;
        }
    } //숫자로 구성되야함
    Delete(str);
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
    if (i > 2) { //인자가 2개 초과체크
        alter_help_print();
        Student_menu();
        return;
    }
    //과목번호 체크
    if (parameter[0].length() != 4) {
        alter_help_print();
        Student_menu();
        return;
    } //길이는 4
    bool check = false; //true면 숫자임, false면 숫자아님
    for (int i = 0; i < parameter[0].length(); i++) {
        for (int j = 0; j < 10; j++) {
            if (num[j].compare(parameter[0].substr(i, 1)) == 0) {
                check = true;
            }
        }
        if (!check) {
            alter_help_print();
            Student_menu();
            return;
        }
    } //숫자로 구성되야함
    //마일리지 체크
    if (parameter[1].length() < 1 || parameter[1].length() > 3) {
        alter_help_print();
        Student_menu();
        return;
    } //길이는 1 ~ 3
    check = false; //true면 숫자임, false면 숫자아님
    for (int i = 0; i < parameter[1].length(); i++) {
        for (int j = 0; j < 10; j++) {
            if (num[j].compare(parameter[1].substr(i, 1)) == 0) {
                check = true;
            }
        }
        if (!check) {
            alter_help_print();
            Student_menu();
            return;
        }
    } //숫자로 구성되야함
    if (parameter[1].length() > 1) {
        for (int i = 0; i < parameter[1].length(); i++) {
            if ((parameter[1].substr(i, 1).compare("0")) == 0) {
                parameter[1].erase(i, 1);
            }
        }
        int mile = stoi(parameter[1]);
    }//마일리지 0제거
    Delete(str);
}
void alter_help_print() {
    cout << "이미 신청한 과목에 대해 분배한 마일리지를 변경하는 명령어" << endl;
    cout << "동의어: ~  변경  ㅂㄱ  alter  alt" << endl;
    cout << "인자: 1개의 과목번호와 1개의 마일리지" << endl;
    cout << "동작: 과목번호와 마일리지를 입력받아, 해당 과목번호에 분배된 기존의 마일리지를 인자로 들어온 마일리지로 변경합니다." << endl;
}