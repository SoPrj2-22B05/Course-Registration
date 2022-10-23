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
    cout << "�й� (�Ǵ� ����)�� �Է����ּ���" << endl;
    cout << "Course Registration > ";
    getline(cin, ID);   //�߰��� �ڵ�
    ID.erase(0, ID.find_first_not_of(" \t\n\r\f\v"));
    ID.erase(ID.find_last_not_of(" \t\n\r\f\v") + 1);

    if (ID.compare("����") == 0 || ID.compare("exit") == 0) {
        cout << "���α׷��� �����մϴ�.";
        exit(0);
    }

    if (ID.length() != 9) { //���̴� 9
        cout << "�ش��ϴ� �й�(�Ǵ� ����)�� �����ϴ�." << endl;
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
        cout << "�ش��ϴ� �й�(�Ǵ� ����)�� �����ϴ�." << endl;
        return;
    }
    else check = 0;
    //���ڷ� �����Ǿ���

    wstring wID, wname;
    vector<wstring> data; // id  name  major  grade  acquisition_credit
    wstring line, str;
    wstringstream ss;
    wID.assign(ID.begin(), ID.end());
    bool c = false; //true�� ���� �ȿ� �й� ����. false�� ����.
    string filename1 = "����� ������ ����.txt";
    wfstream f1;
    f1.imbue(locale("ko_KR.UTF-8"));
    f1.open(filename1);
    if (f1.is_open()) { // �й� �̸� �ܾ����
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
        cout << "�ش��ϴ� �й�(�Ǵ� ����)�� �����ϴ�." << endl;
        return;
    }
    else {
        if ((ID.substr(0, 4)).compare("0000") == 0) {
            cout << "������ �� ������Ʈ�� �̵��մϴ�" << endl;
            Administrator_menu();
        }
        else {
            cout << "�л� �� ������Ʈ�� �̵��մϴ�" << endl;
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
    cout << "��ɾ         | �ùٸ� ���ڵ�     | ����" << endl;
    cout << "-------------------------------------------------------------------" << endl;
    cout << ". logout �α׾ƿ�| ����              | �α׾ƿ��ϰ� ����� ����" << endl;
    cout << "                 |                   | �Է� ������Ʈ�� �̵�" << endl;
    cout << "#   find    �˻� | ���ų�, �˻����  | ������ ���Ͽ��� ���ڵ� �˻�" << endl;
    cout << "                 | �� �� 1�� ����    |" << endl;
    cout << "+    add    �߰� | �����ȣ, ���ϸ���| ������ ���Ͽ� �� ���ڵ� �߰�" << endl;
    cout << "                 |                   |" << endl;
    cout << "-  delete   ���� | �����ȣ          | ������ ���Ͽ��� ���� ���ڵ�" << endl;
    cout << "                 |                   | ����" << endl;
    cout << "~  alter    ���� | �����ȣ, ���ϸ���| ������ ���Ͽ��� ���� ���ڵ�" << endl;
    cout << "                 |                   | ����" << endl;
    cout << "-------------------------------------------------------------------" << endl;
}
void Student_menu() {
    restart = false;
    string logout[ORDER_NUM] = { "logout", "l", "�α׾ƿ�", "��������", "." };
    string find[ORDER_NUM] = { "find", "f", "�˻�", "����", "#" };
    string add[ORDER_NUM] = { "add", "ad","�߰�", "����", "+" };
    string del[ORDER_NUM] = { "delete", "d", "����", "����", "-" };
    string alter[ORDER_NUM] = { "alter", "alt", "����", "����", "~" };
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

    if (str.compare("") == 0) { //�� ���ڿ��̸� ��� ����
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

    if (str.find_first_of(" \t\f\v") < 0 || str.find_first_of(" \t\f\v") >= str.size()) {   //�Է¿� Ⱦ����� �ϳ��� ������ ����
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
                cout << "���� : ������ ���� �ʽ��ϴ�." << endl;
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
            cout << "���� ���Ŀ� ����˴ϴ�. �Է� ���ڵ� ���̿� ������ ������ �� �˴ϴ�." << endl;
            restart = true;
            return;
        }

        
        char* chars = new char[stu_input[1].length() + 1];
        stu_input[1].copy(chars, stu_input[1].length());
        chars[stu_input[1].length()] = '\0';
        for (int j = 0; j < stu_input[1].length(); j++)
        {
            // �ƽ�Ű�ڵ� ���� Ư�����ڰ� ������ ���� ���
            // �����̸��� ���ĺ����θ� �����Ǿ� ������ �� ���ĺ��� �ƽ�Ű�ڵ� ���Խ�Ų �� not �ϸ� �Ǵµ�...
            // �ѱ��� ���ִٺ��� ��Ʈ�� �׸� ���� Ư�����ڱ��� �����Ϸ��� ��� ����� ���� ������ �� ��������� �ż� ���������� ����� �� �����ϴ�. 
            if (!((chars[j] >= 48 && chars[j] <= 57) || chars[j] == 47)) // 47�� '/'�� 46������
            {
                cout << "���� ���Ŀ� ����˴ϴ�. �Է� ���ڵ� ���̿� '/'�� ������ Ư�� ���ڰ� ������ �� �˴ϴ�." << endl;
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

    if (!check2) {  //������ �Է�
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
            cout << "���� ���Ŀ� ����˴ϴ�. �Է� ���ڵ� ���̿� ������ ������ �� �˴ϴ�." << endl;
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
    if (i > 2) { //���ڰ� 2�� �ʰ�üũ
        add_help_print();
        return;
    }
    //�����ȣ üũ
    if (parameter[0].length() != 4) {
        add_help_print();
        return;
    } //���̴� 4
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
    //���ϸ��� üũ
    if (parameter[1].length() < 1 || parameter[1].length() > 3) {
        add_help_print();
        return;
    } //���̴� 1 ~ 3
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
    else check = 0; // ���ڸ� �ִ���
    Add(str, ID, name);
}
void add_help_print() {
    cout << "���ϴ� ������ ������û �߰��ϴ� ��ɾ�" << endl;
    cout << "���Ǿ�: +  �߰�  ����  add  ad" << endl;
    cout << "����: 1���� �����ȣ�� 1���� ���ϸ���" << endl;
    cout << "����: �����ȣ�� ���ϸ����� �Է¹ް�, �����ȣ�� �ش��ϴ� ���� ���ϸ����� ������ ������û�� �߰��մϴ�." << endl;
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
    if (i > 1) { //���� 1�� �ʰ� üũ
        del_help_print();
        return;
    }
    //�����ȣ üũ
    if (parameter.length() != 4) {
        del_help_print();
        return;
    } //���̴� 4
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
    cout << "������ ���ϴ� ������ ������û ����ϴ� ��ɾ�" << endl;
    cout << "���Ǿ�: -  ����  ����  delete  d" << endl;
    cout << "����: 1���� �����ȣ" << endl;
    cout << "����: �����ȣ�� �Է¹ް�, �����ȣ�� �ش��ϴ� ������ �����մϴ�." << endl;
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
    if (i > 2) { //���ڰ� 2�� �ʰ�üũ
        alter_help_print();
        return;
    }
    //�����ȣ üũ
    if (parameter[0].length() != 4) {
        alter_help_print();
        return;
    } //���̴� 4
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
    //���ϸ��� üũ
    if (parameter[1].length() < 1 || parameter[1].length() > 3) {
        alter_help_print();
        return;
    } //���̴� 1 ~ 3
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
    cout << "�̹� ��û�� ���� ���� �й��� ���ϸ����� �����ϴ� ��ɾ�" << endl;
    cout << "���Ǿ�: ~  ����  ����  alter  alt" << endl;
    cout << "����: 1���� �����ȣ�� 1���� ���ϸ���" << endl;
    cout << "����: �����ȣ�� ���ϸ����� �Է¹޾�, �ش� �����ȣ�� �й�� ������ ���ϸ����� ���ڷ� ���� ���ϸ����� �����մϴ�." << endl;
}

void find_help_print() {
    cout << "������ ���Ͽ��� ���ϴ� ������ �˻��ϴ� ��ɾ�" << endl;
    cout << "���Ǿ� : # �˻� ���� find f" << endl;
    cout << "���� : �˻����(�����ȣ, �����̸�, �г�, ����/����)" << endl;
    cout << "���� : �˻���Ҹ� �Է¹ް�, ���͸��� ������� ����մϴ�." << endl;
}

bool start_check() {
    wstring dir = fs::current_path();
    wfstream isOn;
    isOn.open(dir + L"\\Course_Registration_Is_On.txt");
    if (!isOn.is_open()) {
        cout << "���� ������û�� ���۵��� �ʾҽ��ϴ�." << endl;
        return false;
    }
    else {
        return true;
    }
}