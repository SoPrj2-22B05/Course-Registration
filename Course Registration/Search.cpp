#include <iostream>
#include <string>
#include <fstream>
#include <cstdio>
#include <sstream>
#include <vector>
#include <cctype>
#include <algorithm>
#include "SubjectData.h"
using namespace std;

void Logout(string command) {
	if (command.empty() == 0)
		cout << "���� ���Ŀ� ����˴ϴ�. (���ڰ� ����� ��)" << endl;
}
void Search(string command) {
	
	//�ʱ�ȭ
	int grade = 5;
	string id = "0";
	string major = "0";
	string name = "0";

	bool sORf = true;
	
	//string str = command;
	//getline(cin, str);
	vector<string> searchs;
	stringstream ss(command);
	string token;
	
	//���ڿ��� '/' �������� �ڸ��ϴ�.
	while (getline(ss, token, '/'))
	{
		searchs.push_back(token);
	}
	
	if (searchs.size() > 4) // �������� ���� (���ڰ� 5�� �̻��� �Ǵ� ���)
	{
		cout << "������ ���Ͽ��� ���ϴ� ������ �˻��ϴ� ��ɾ�" << endl;
		cout << "���Ǿ� : # �˻� ���� find f" << endl;
		cout << "���� : �˻����(�����ȣ, �����̸�, �г�, ����/����)" << endl;
		cout << "���� : �˻���Ҹ� �Է¹ް�, ���͸��� ������� ����մϴ�." << endl;
	}

	if ((searchs.size() <= 4) && searchs.size() > 0) {
		// �ڸ� ���ڿ� �� �����ȣ, �����̸�, �г�, ����/������ �����մϴ�.
		for (auto search : searchs)
		{
			int i = 0;
			stringstream ssInt(search);
			ssInt >> i;
			if (!ssInt.fail()) //���� ���ڿ��� ���������� �ٲٴµ� �����ϸ� (��, �����ȣ�� �г��� �Է��ϸ�)
			{
				if (search.size() == 1) // ���ڿ��� ���̰� 1�̸� �г⿡ �ش� ���ڸ� �־��ְ�
				{
					if (grade == 5)
					{
						grade = i;
					}
					else
					{
						bool sORf = false;
						cout << "���� : �˻���Ұ� �ߺ��˴ϴ�." << endl;
						cout << "'�г�' �˻���Ұ� �ߺ��ؼ� �����մϴ�." << endl;
						break;
					}

				}
				if (search.size() == 4) // ���ڿ��� ���̰� 4�� �����ȣ�� �־��ݴϴ�.
				{
					if (id == "0")
					{
						id = search;
					}
					else
					{
						bool sORf = false;
						cout << "���� : �˻���Ұ� �ߺ��˴ϴ�." << endl;
						cout << "'�����ȣ' �˻���Ұ� �ߺ��ؼ� �����մϴ�." << endl;
						break;
					}
				}
			}
			else
			{
				if (search.substr(search.length() - 4) == "�а�" || search.substr(search.length() - 4) == "�к�" || search == "����")
				{
					if (major == "0")
					{
						major = search;
					}
					else
					{
						bool sORf = false;
						cout << "���� : �˻���Ұ� �ߺ��˴ϴ�." << endl;
						cout << "'����/����' �˻���Ұ� �ߺ��ؼ� �����մϴ�." << endl;
						break;
					}
				}
				else
				{
					if (name == "0")
					{
						name = search;
					}
					else
					{
						bool sORf = false;
						cout << "���� : �˻���Ұ� �ߺ��˴ϴ�." << endl;
						cout << "'�����̸�' �˻���Ұ� �ߺ��ؼ� �����մϴ�." << endl;
						break;
					}
				}
			}
			if (major == "����" && grade != 0 && grade != 5)
			{
				sORf = false;
				cout << "���� : �Էµ� <����/����>�� �ش� <�г�>�� ������ �� �����ϴ�." << endl;
				cout << "<����/����>�� ""����""�� ��� <�г�>�� �ݵ�� 0�̾�� �մϴ�." << endl;
				break;

			}
		}
	}
	
	//�� �ڷ����� �и��ż� �� �� Ȯ��
	cout << "grade :" << grade << endl;
	cout << "id : " << id << endl;
	cout << "name : " << name << endl;
	cout << "major : " << major << endl;
	
	if (sORf == true) {
		for (int i = 0; i < 10000; i++)
		{
			//���� �ϳ��� ������ ��ü ���
			if (id == "0" && name == "0" && grade == 5 && major == "0")
			{
				cout << Subject[i]->id << " " << Subject[i]->name << " " << Subject[i]->credit << " " << Subject[i]->major << Subject[i]->grade << " " << Subject[i]->time << " " << Subject[i]->max << endl;
			}

			//�����ȣ�� ���ؼ� �˻�
			if (id == Subject[i]->id && name == "0" && grade == 5 && major == "0")
			{
				cout << Subject[i]->id << " " << Subject[i]->name << " " << Subject[i]->credit << " " << Subject[i]->major << Subject[i]->grade << " " << Subject[i]->time << " " << Subject[i]->max << endl;
			}

			//�����̸��� ���ؼ� �˻�
			if (id == "0" && name == Subject[i]->name && grade == 5 && major == "0")
			{
				cout << Subject[i]->id << " " << Subject[i]->name << " " << Subject[i]->credit << " " << Subject[i]->major << Subject[i]->grade << " " << Subject[i]->time << " " << Subject[i]->max << endl;
			}

			//�г⸸ ���ؼ� �˻�
			if (id == "0" && name == "0" && grade == Subject[i]->grade && major == "0")
			{
				cout << Subject[i]->id << " " << Subject[i]->name << " " << Subject[i]->credit << " " << Subject[i]->major << Subject[i]->grade << " " << Subject[i]->time << " " << Subject[i]->max << endl;
			}

			//����/���縸 ���ؼ� �˻�
			if (id == "0" && name == "0" && grade == 5 && major == Subject[i]->major)
			{
				cout << Subject[i]->id << " " << Subject[i]->name << " " << Subject[i]->credit << " " << Subject[i]->major << Subject[i]->grade << " " << Subject[i]->time << " " << Subject[i]->max << endl;
			}

			//�����ȣ,�����̸��� ���ؼ� �˻�
			if (id == Subject[i]->id && name == Subject[i]->name && grade == 5 && major == "0")
			{
				cout << Subject[i]->id << " " << Subject[i]->name << " " << Subject[i]->credit << " " << Subject[i]->major << Subject[i]->grade << " " << Subject[i]->time << " " << Subject[i]->max << endl;
			}

			//�����ȣ,�г⸸ ���ؼ� �˻�
			if (id == Subject[i]->id && name == "0" && grade == Subject[i]->grade && major == "0")
			{
				cout << Subject[i]->id << " " << Subject[i]->name << " " << Subject[i]->credit << " " << Subject[i]->major << Subject[i]->grade << " " << Subject[i]->time << " " << Subject[i]->max << endl;
			}

			//�����ȣ,����/���縸 ���ؼ� �˻�
			if (id == Subject[i]->id && name == "0" && grade == 5 && major == Subject[i]->major)
			{
				cout << Subject[i]->id << " " << Subject[i]->name << " " << Subject[i]->credit << " " << Subject[i]->major << Subject[i]->grade << " " << Subject[i]->time << " " << Subject[i]->max << endl;
			}

			//�����̸�, �г⸸ ���ؼ� �˻�
			if (id == "0" && name == Subject[i]->name && grade == Subject[i]->grade && major == "0")
			{
				cout << Subject[i]->id << " " << Subject[i]->name << " " << Subject[i]->credit << " " << Subject[i]->major << Subject[i]->grade << " " << Subject[i]->time << " " << Subject[i]->max << endl;
			}

			//�����̸�,����/���縸 ���ؼ� �˻�
			if (id == "0" && name == Subject[i]->name && grade == 5 && major == Subject[i]->major)
			{
				cout << Subject[i]->id << " " << Subject[i]->name << " " << Subject[i]->credit << " " << Subject[i]->major << Subject[i]->grade << " " << Subject[i]->time << " " << Subject[i]->max << endl;
			}

			//�г�, ����/���縸 ���ؼ� �˻�
			if (id == "0" && name == "0" && grade == Subject[i]->grade && major == Subject[i]->major)
			{
				cout << Subject[i]->id << " " << Subject[i]->name << " " << Subject[i]->credit << " " << Subject[i]->major << Subject[i]->grade << " " << Subject[i]->time << " " << Subject[i]->max << endl;
			}

			//�����ȣ, �����̸�, �г⸸ ���ؼ� �˻�
			if (id == Subject[i]->id && name == Subject[i]->name && grade == Subject[i]->grade && major == "0")
			{
				cout << Subject[i]->id << " " << Subject[i]->name << " " << Subject[i]->credit << " " << Subject[i]->major << Subject[i]->grade << " " << Subject[i]->time << " " << Subject[i]->max << endl;
			}

			//�����ȣ, �����̸�, ����/���縸 ���ؼ� �˻�
			if (id == Subject[i]->id && name == Subject[i]->name && grade == 5 && major == Subject[i]->major)
			{
				cout << Subject[i]->id << " " << Subject[i]->name << " " << Subject[i]->credit << " " << Subject[i]->major << Subject[i]->grade << " " << Subject[i]->time << " " << Subject[i]->max << endl;
			}

			//�����ȣ, �г�, ����/���縸 ���ؼ� �˻�
			if (id == Subject[i]->id && name == "0" && grade == Subject[i]->grade && major == Subject[i]->major)
			{
				cout << Subject[i]->id << " " << Subject[i]->name << " " << Subject[i]->credit << " " << Subject[i]->major << Subject[i]->grade << " " << Subject[i]->time << " " << Subject[i]->max << endl;
			}

			//���� �̸�, �г�, ����/���縸 ���ؼ� �˻�
			if (id == "0" && name == Subject[i]->name && grade == Subject[i]->grade && major == Subject[i]->major)
			{
				cout << Subject[i]->id << " " << Subject[i]->name << " " << Subject[i]->credit << " " << Subject[i]->major << Subject[i]->grade << " " << Subject[i]->time << " " << Subject[i]->max << endl;
			}

			//�����ȣ, �����̸�, �г�, ����/���縸 ���ؼ� �˻�
			if (id == Subject[i]->id && name == Subject[i]->name && grade == Subject[i]->grade && major == Subject[i]->major)
			{
				cout << Subject[i]->id << " " << Subject[i]->name << " " << Subject[i]->credit << " " << Subject[i]->major << Subject[i]->grade << " " << Subject[i]->time << " " << Subject[i]->max << endl;
			}
		}
	}
}