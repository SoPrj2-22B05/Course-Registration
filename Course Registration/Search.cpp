#include <iostream>
#include <string>
#include <fstream>
#include <cstdio>
#include <sstream>
#include <vector>
#include <cctype>
#include <algorithm>
#include "SubjectData.h"
#include "prompt.h"
using namespace std;

void Logout(string command) {

	stringstream stream;
	stream.str(command);
	string token;
	string arr[100] = { "0" };
	int i = 0;
	while (stream >> token) {
		arr[i] = token;
		i++;
	}
	command = arr[1];

	if (command.empty() == 0) {
		cout << "���� ���Ŀ� ����˴ϴ�. logout �ڿ��� ���ڰ� ����� �մϴ�." << endl;
	}
	if (command.empty() == 1) {
		User_info_menu();
	}
}
void Search(string command) {
	//cout << command << endl; // ���� Ȯ��
	bool sORf = true;
	if (command.back() == '/')
	{
		cout << "���� ���Ŀ� ����˴ϴ�. '/'�� ���ڿ� ���̿� �־�� �մϴ�." << endl;
		sORf = false;
	}

	stringstream stream;
	stream.str(command);
	string token1;
	string arr[100] = { "0" }; //arr[0]�� find, arr[1]�� �����ȣ/�����̸�/�г�/�а� ���ڿ��� ����
	int i = 0;
	int SpecialCharacterIndex = 0;
	while (stream >> token1) {
		arr[i] = token1;
		i++;
		if (i > 2) // find �� ���ڿ��� ������ ������ i == 2�̱� ������ (��:find 3123/������/3) i == 3 �̻��̶�� �� ������ �����Ѵٴ� �� 
		{
			cout << "���� ���Ŀ� ����˴ϴ�. �Է� ���ڵ� ���̿� ������ ������ �� �˴ϴ�." << endl;
			sORf = false;
			break;
		}
		else if (i == 2)
		{
			for (char j = 33; j <= 46; j++)
			{
				if (arr[1].find(j) != string::npos)
				{
					SpecialCharacterIndex = 1;
					break;
				}
			}
			for (char j = 58; j <= 64; j++)
			{
				if (arr[1].find(j) != string::npos)
				{
					SpecialCharacterIndex = 1;
					break;
				}
			}
			for (char j = 91; j <= 95; j++)
			{
				if (arr[1].find(j) != string::npos)
				{
					SpecialCharacterIndex = 1;
					break;
				}
			}
			for (char j = 123; j <= 126; j++)
			{
				if (arr[1].find(j) != string::npos)
				{
					SpecialCharacterIndex = 1;
					break;
				}
			}
		}

	}
	if (SpecialCharacterIndex == 1)
	{
		cout << "���� ���Ŀ� ����˴ϴ�. �Է� ���ڵ� ���̿� '/'�� ������ Ư�� ���ڰ� ������ �� �˴ϴ�." << endl;
		sORf = false;
	}



	if (sORf == true) { // �����ȣ/�����̸�/�г�/�а� ���ڿ��� �����̳� Ư�����ڰ� ������ �� �غκ��� ������ �� �ǵ��� �մϴ�.
		command = arr[1]; //find ���� ���ڿ��� ���ϴ�.

		int grade = 5;
		string id = "0";
		string major = "0";
		string name = "0";

		//string str = command;
		//getline(cin, str);
		vector<string> searchs;
		stringstream ss(command);
		string token2;

		//���ڿ��� '/' �������� �ڸ��ϴ�.
		while (getline(ss, token2, '/'))
		{
			searchs.push_back(token2);
		}

		if (searchs[0] == "/")

			if (searchs.size() > 4) // �������� ���� (���ڰ� 5�� �̻��� �Ǵ� ���)
			{
				cout << "������ ���Ͽ��� ���ϴ� ������ �˻��ϴ� ��ɾ�" << endl;
				cout << "���Ǿ� : # �˻� ���� find f" << endl;
				cout << "���� : �˻����(�����ȣ, �����̸�, �г�, ����/����)" << endl;
				cout << "���� : �˻���Ҹ� �Է¹ް�, ���͸��� ������� ����մϴ�." << endl;
				sORf = false;
			}

		if ((searchs.size() <= 4) && searchs.size() > 0) {
			// �ڸ� ���ڿ� �� �����ȣ, �����̸�, �г�, ����/������ �����մϴ�.
			for (auto search : searchs)
			{
				//int i = 0;
				//__int64 i = 0;
				long double i = 0; // �� ��쿣 �� ���� ���� �������� Ŀ�� ������ 2147483647�� �ʰ��ϴ� ���� ���� �װ͵� ���� �̸����� �з��ϱ� ������ long double�� �Ἥ �ԷµǴ� ������ ���� ������Ŵ

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
							sORf = false;
							cout << "���� : �˻���Ұ� �ߺ��˴ϴ�." << endl;
							cout << "'�г�' �˻���Ұ� �ߺ��ؼ� �����մϴ�." << endl;
							break;
						}

					}
					else if (search.size() == 4) // ���ڿ��� ���̰� 4�� �����ȣ�� �־��ݴϴ�.
					{
						if (id == "0")
						{
							id = search;
						}
						else
						{
							sORf = false;
							cout << "���� : �˻���Ұ� �ߺ��˴ϴ�." << endl;
							cout << "'�����ȣ' �˻���Ұ� �ߺ��ؼ� �����մϴ�." << endl;
							break;
						}
					}
					/*
					else //������ ���ڿ��� ���̰� 1�� �ƴϰ� 4�� �ƴ� ��� (2,3 �Ǵ� 5  �̻�) ���ڸ� ���� �̸��� �־���
					{
						if (name == "0")
						{
							name = search;
						}
					}*/

					else //������ ���ڿ��� ���̰� 1�� �ƴϰ� 4�� �ƴ� ���
					{
						sORf = false;
						cout << "���� : ������ �ʴ� �Է��Դϴ�.." << endl;
						cout << "'�����̸�' �˻���ҿ� ��� �ѱ��� �ϳ� �̻� ���� �մϴ�." << endl;
						cout << "'�����ȣ' �˻���Ҵ� 4�ڸ� ���ڷθ� �̷�����ϴ�." << endl;
						cout << "'�г�' �˻���Ҵ� 1�ڸ� ���ڷθ� �̷�����ϴ�." << endl;
						break;
					}


				}
				else //���ڿ��� ���������� �ٲٴµ� ���� 
				{
					if (search.length() >= 4) {
						if (search.substr(search.length() - 4) == "�а�" || search.substr(search.length() - 4) == "�к�" || search == "����")
						{
							if (major == "0")
							{
								major = search;
							}
							else
							{
								sORf = false;
								cout << "���� : �˻���Ұ� �ߺ��˴ϴ�." << endl;
								cout << "'����/����' �˻���Ұ� �ߺ��ؼ� �����մϴ�." << endl;
								break;
							}
						}
						else // �а��� �кγ� �����̶�� �� search�� ������ �ٷ� ���� �̸����� �־���
						{
							if (name == "0")
							{
								name = search;
							}
							else
							{
								sORf = false;
								cout << "���� : �˻���Ұ� �ߺ��˴ϴ�." << endl;
								cout << "'�����̸�' �˻���Ұ� �ߺ��ؼ� �����մϴ�." << endl;
								break;
							}
						}
					}
					else // ���ڰ� �ƴ� ���ڿ��� ���̰� 4 �̸��� ���
					{
						if (name == "0") //name�� "0"�̸� �����̸��� �־���
						{
							name = search;
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
				if (Subject[i] != NULL) {
					//���� �ϳ��� ������ ��ü ���
					if (id == "0" && name == "0" && grade == 5 && major == "0")
					{
						cout << Subject[i]->id << " | ";
						cout << Subject[i]->name << " | ";
						cout << Subject[i]->credit << " | ";
						cout << Subject[i]->major << " | ";
						cout << Subject[i]->grade << " | ";
						cout << Subject[i]->time << " | ";
						cout << Subject[i]->max << endl;
					}

					//�����ȣ�� ���ؼ� �˻�
					if (id == Subject[i]->id && name == "0" && grade == 5 && major == "0")
					{
						cout << Subject[i]->id << " | ";
						cout << Subject[i]->name << " | ";
						cout << Subject[i]->credit << " | ";
						cout << Subject[i]->major << " | ";
						cout << Subject[i]->grade << " | ";
						cout << Subject[i]->time << " | ";
						cout << Subject[i]->max << endl;
					}

					//�����̸��� ���ؼ� �˻�
					if (id == "0" && name == Subject[i]->name && grade == 5 && major == "0")
					{
						cout << Subject[i]->id << " | ";
						cout << Subject[i]->name << " | ";
						cout << Subject[i]->credit << " | ";
						cout << Subject[i]->major << " | ";
						cout << Subject[i]->grade << " | ";
						cout << Subject[i]->time << " | ";
						cout << Subject[i]->max << endl;
					}

					//�г⸸ ���ؼ� �˻�
					if (id == "0" && name == "0" && grade == Subject[i]->grade && major == "0")
					{
						cout << Subject[i]->id << " | ";
						cout << Subject[i]->name << " | ";
						cout << Subject[i]->credit << " | ";
						cout << Subject[i]->major << " | ";
						cout << Subject[i]->grade << " | ";
						cout << Subject[i]->time << " | ";
						cout << Subject[i]->max << endl;
					}

					//����/���縸 ���ؼ� �˻�
					if (id == "0" && name == "0" && grade == 5 && major == Subject[i]->major)
					{
						cout << Subject[i]->id << " | ";
						cout << Subject[i]->name << " | ";
						cout << Subject[i]->credit << " | ";
						cout << Subject[i]->major << " | ";
						cout << Subject[i]->grade << " | ";
						cout << Subject[i]->time << " | ";
						cout << Subject[i]->max << endl;
					}

					//�����ȣ,�����̸��� ���ؼ� �˻�
					if (id == Subject[i]->id && name == Subject[i]->name && grade == 5 && major == "0")
					{
						cout << Subject[i]->id << " | ";
						cout << Subject[i]->name << " | ";
						cout << Subject[i]->credit << " | ";
						cout << Subject[i]->major << " | ";
						cout << Subject[i]->grade << " | ";
						cout << Subject[i]->time << " | ";
						cout << Subject[i]->max << endl;
					}

					//�����ȣ,�г⸸ ���ؼ� �˻�
					if (id == Subject[i]->id && name == "0" && grade == Subject[i]->grade && major == "0")
					{
						cout << Subject[i]->id << " | ";
						cout << Subject[i]->name << " | ";
						cout << Subject[i]->credit << " | ";
						cout << Subject[i]->major << " | ";
						cout << Subject[i]->grade << " | ";
						cout << Subject[i]->time << " | ";
						cout << Subject[i]->max << endl;
					}

					//�����ȣ,����/���縸 ���ؼ� �˻�
					if (id == Subject[i]->id && name == "0" && grade == 5 && major == Subject[i]->major)
					{
						cout << Subject[i]->id << " | ";
						cout << Subject[i]->name << " | ";
						cout << Subject[i]->credit << " | ";
						cout << Subject[i]->major << " | ";
						cout << Subject[i]->grade << " | ";
						cout << Subject[i]->time << " | ";
						cout << Subject[i]->max << endl;
					}

					//�����̸�, �г⸸ ���ؼ� �˻�
					if (id == "0" && name == Subject[i]->name && grade == Subject[i]->grade && major == "0")
					{
						cout << Subject[i]->id << " | ";
						cout << Subject[i]->name << " | ";
						cout << Subject[i]->credit << " | ";
						cout << Subject[i]->major << " | ";
						cout << Subject[i]->grade << " | ";
						cout << Subject[i]->time << " | ";
						cout << Subject[i]->max << endl;
					}

					//�����̸�,����/���縸 ���ؼ� �˻�
					if (id == "0" && name == Subject[i]->name && grade == 5 && major == Subject[i]->major)
					{
						cout << Subject[i]->id << " | ";
						cout << Subject[i]->name << " | ";
						cout << Subject[i]->credit << " | ";
						cout << Subject[i]->major << " | ";
						cout << Subject[i]->grade << " | ";
						cout << Subject[i]->time << " | ";
						cout << Subject[i]->max << endl;
					}

					//�г�, ����/���縸 ���ؼ� �˻�
					if (id == "0" && name == "0" && grade == Subject[i]->grade && major == Subject[i]->major)
					{
						cout << Subject[i]->id << " | ";
						cout << Subject[i]->name << " | ";
						cout << Subject[i]->credit << " | ";
						cout << Subject[i]->major << " | ";
						cout << Subject[i]->grade << " | ";
						cout << Subject[i]->time << " | ";
						cout << Subject[i]->max << endl;
					}

					//�����ȣ, �����̸�, �г⸸ ���ؼ� �˻�
					if (id == Subject[i]->id && name == Subject[i]->name && grade == Subject[i]->grade && major == "0")
					{
						cout << Subject[i]->id << " | ";
						cout << Subject[i]->name << " | ";
						cout << Subject[i]->credit << " | ";
						cout << Subject[i]->major << " | ";
						cout << Subject[i]->grade << " | ";
						cout << Subject[i]->time << " | ";
						cout << Subject[i]->max << endl;
					}

					//�����ȣ, �����̸�, ����/���縸 ���ؼ� �˻�
					if (id == Subject[i]->id && name == Subject[i]->name && grade == 5 && major == Subject[i]->major)
					{
						cout << Subject[i]->id << " | ";
						cout << Subject[i]->name << " | ";
						cout << Subject[i]->credit << " | ";
						cout << Subject[i]->major << " | ";
						cout << Subject[i]->grade << " | ";
						cout << Subject[i]->time << " | ";
						cout << Subject[i]->max << endl;
					}

					//�����ȣ, �г�, ����/���縸 ���ؼ� �˻�
					if (id == Subject[i]->id && name == "0" && grade == Subject[i]->grade && major == Subject[i]->major)
					{
						cout << Subject[i]->id << " | ";
						cout << Subject[i]->name << " | ";
						cout << Subject[i]->credit << " | ";
						cout << Subject[i]->major << " | ";
						cout << Subject[i]->grade << " | ";
						cout << Subject[i]->time << " | ";
						cout << Subject[i]->max << endl;
					}

					//���� �̸�, �г�, ����/���縸 ���ؼ� �˻�
					if (id == "0" && name == Subject[i]->name && grade == Subject[i]->grade && major == Subject[i]->major)
					{
						cout << Subject[i]->id << " | ";
						cout << Subject[i]->name << " | ";
						cout << Subject[i]->credit << " | ";
						cout << Subject[i]->major << " | ";
						cout << Subject[i]->grade << " | ";
						cout << Subject[i]->time << " | ";
						cout << Subject[i]->max << endl;
					}

					//�����ȣ, �����̸�, �г�, ����/���縸 ���ؼ� �˻�
					if (id == Subject[i]->id && name == Subject[i]->name && grade == Subject[i]->grade && major == Subject[i]->major)
					{
						cout << Subject[i]->id << " | ";
						cout << Subject[i]->name << " | ";
						cout << Subject[i]->credit << " | ";
						cout << Subject[i]->major << " | ";
						cout << Subject[i]->grade << " | ";
						cout << Subject[i]->time << " | ";
						cout << Subject[i]->max << endl;
					}
				}
			}
		}
	}
}