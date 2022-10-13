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
    cout << "�й� (�Ǵ� ����)�� �Է����ּ���" << endl;
    cin >> ID;
    size_t npos;
   
    npos = ID.find_first_not_of(' ');
    ID.erase(0, npos);
    npos = ID.find_last_not_of(' ');
    ID.erase(npos + 1); //�յ� ���� ����

    if (ID.compare("����") == 0 || ID.compare("exit") == 0) {
        cout << "���α׷��� �����մϴ�.";
        exit(0);
    }
    bool c = false; //true�� ���� �ȿ� �й� ����. false�� ����.
    for (int i = 0; i < 10000; i++) {
        if (Subject[i]->id.compare(ID)) {
            c = true;
            break;
        }
    }
    if (!c) {
        exit(0);
    }
    if (ID.length() != 9) { //���̴� 9
        cout << "�ش��ϴ� �й�(�Ǵ� ����)�� �����ϴ�.";
        return;
    }
    else {
        bool check = false; //true�� ������, false�� ���ھƴ�
        for (int i = 0; i < ID.length(); i++) {
            for (int j = 0; j < 10; j++) {
                if (num[j].compare(ID.substr(i, 1)) == 0) {
                    check = true;
                }
            }
            if (!check) {
                cout << "�ش��ϴ� �й�(�Ǵ� ����)�� �����ϴ�.";
                return;
            }
        } //���ڷ� �����Ǿ���
        
        if ((ID.substr(0, 4)).compare("0000") == 0) {
            cout << "������ �� ������Ʈ�� �̵��մϴ�" << endl;
            Administrator_menu();
        }
        else {
            cout << "�л� �� ������Ʈ�� �̵��մϴ�" << endl;
            Student_menu();
        }
    }
}
void print_manual() {
    cout << "-------------------------------------------------------------------" << endl;
    cout << "��ɾ         | �ùٸ� ���ڵ�     | ����" << endl;
    cout << "-------------------------------------------------------------------" << endl;
    cout << ". logout �α׾ƿ�| ����              | �α׾ƿ��ϰ� ���������" << endl;
    cout << "                 |                   | �Է� ������Ʈ�� �̵�" << endl;
    cout << "#   find    �˻� | ���ų�, �˻����  | ������ ���Ͽ��� ���ڵ� �˻�" << endl;
    cout << "                 | �� �� 1�� ����    |" << endl;
    cout << "+    add    �߰� | �����ȣ, ���ϸ���| ������ ���Ͽ� �� ���ڵ� �߰�" << endl;
    cout << "                 |                   |" << endl;
    cout << "-  delete   ���� | �����ȣ          | ������ ���Ͽ��� ���� ���ڵ�" << endl;
    cout << "                 |                   | ����" << endl;
    cout << "~  alt      ���� | �����ȣ, ���ϸ���| ������ ���Ͽ��� ���� ���ڵ�" << endl;
    cout << "                 |                   | ����" << endl;
    cout << "-------------------------------------------------------------------" << endl;
}
void Student_menu() {
    string logout[ORDER_NUM] = { "logout", "l", "�α׾ƿ�", "��������", "." };
    string find[ORDER_NUM] = { "find", "f", "�˻�", "����", "#" };
    string add[ORDER_NUM] = { "add", "ad","�߰�", "����", "+" };
    string del[ORDER_NUM] = { "delete", "d", "����", "����", "-" };
    string alter[ORDER_NUM] = { "alter", "alt", "����", "����", "~" };
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
            return;//�˻��� ���� �߰�
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
    if (i > 2) { //���ڰ� 2�� �ʰ�üũ
        add_help_print();
        Student_menu();
        return;
    }
    //�����ȣ üũ
    if (parameter[0].length() != 4) {
        add_help_print();
        Student_menu();
        return;
    } //���̴� 4
    bool check = false; //true�� ������, false�� ���ھƴ�
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
    } //���ڷ� �����Ǿ���
    //���ϸ��� üũ
    if (parameter[1].length() < 1 || parameter[1].length() > 3) {
        add_help_print();
        Student_menu();
        return;
    } //���̴� 1 ~ 3
    check = false; //true�� ������, false�� ���ھƴ�
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
    } //���ڷ� �����Ǿ���
    if (parameter[1].length() > 1) {
        for (int i = 0; i < parameter[1].length(); i++) {
            if ((parameter[1].substr(i, 1).compare("0")) == 0) {
                parameter[1].erase(i, 1);
            }
        }
        int mile = stoi(parameter[1]);
    }//���ϸ��� 0����
    Add(str);
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
    string parameter[1];
    int i = 0;
    while (getline(iss, str_buf, separator)) {
        if (i <= 0) {
            parameter[i] = str_buf;
        }
        i++;
    }
    if (i > 1) { //���� 1�� �ʰ� üũ
        del_help_print();
        Student_menu();
        return;
    }
    //�����ȣ üũ
    if (parameter[0].length() != 4) {
        del_help_print();
        Student_menu();
        return;
    } //���̴� 4
    bool check = false; //true�� ������, false�� ���ھƴ�
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
    } //���ڷ� �����Ǿ���
    Delete(str);
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
    if (i > 2) { //���ڰ� 2�� �ʰ�üũ
        alter_help_print();
        Student_menu();
        return;
    }
    //�����ȣ üũ
    if (parameter[0].length() != 4) {
        alter_help_print();
        Student_menu();
        return;
    } //���̴� 4
    bool check = false; //true�� ������, false�� ���ھƴ�
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
    } //���ڷ� �����Ǿ���
    //���ϸ��� üũ
    if (parameter[1].length() < 1 || parameter[1].length() > 3) {
        alter_help_print();
        Student_menu();
        return;
    } //���̴� 1 ~ 3
    check = false; //true�� ������, false�� ���ھƴ�
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
    } //���ڷ� �����Ǿ���
    if (parameter[1].length() > 1) {
        for (int i = 0; i < parameter[1].length(); i++) {
            if ((parameter[1].substr(i, 1).compare("0")) == 0) {
                parameter[1].erase(i, 1);
            }
        }
        int mile = stoi(parameter[1]);
    }//���ϸ��� 0����
    Delete(str);
}
void alter_help_print() {
    cout << "�̹� ��û�� ���� ���� �й��� ���ϸ����� �����ϴ� ��ɾ�" << endl;
    cout << "���Ǿ�: ~  ����  ����  alter  alt" << endl;
    cout << "����: 1���� �����ȣ�� 1���� ���ϸ���" << endl;
    cout << "����: �����ȣ�� ���ϸ����� �Է¹޾�, �ش� �����ȣ�� �й�� ������ ���ϸ����� ���ڷ� ���� ���ϸ����� �����մϴ�." << endl;
}