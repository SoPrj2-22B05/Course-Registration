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

bool Logout(string command) {

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
		cout << "���� : logout �ڿ��� ���ڰ� ����� �մϴ�." << endl;
		return false;
	}
	if (command.empty() == 1) {
		return true;
	}
}
/*
Search("find 1/1/1/1/1");
Search("find 5");
Search("find ������");
Search("find ����/0");
Search("find 0/��ǻ��");
*/

void Search(string command)
{
	//cout << "Search�� �޴� ���� : " << command << endl; // ���� Ȯ��
	bool sORf = true;
	stringstream stream;
	stream.str(command);
	string token1;
	string arr[100] = { "0" }; //arr[0]�� find, arr[1]�� �����ȣ/�����̸�/�г�/�а� ���ڿ��� ����
	int i = 0;
	int SpecialCharacterIndex = 0;

	//���ڵ� ���̿� �����̳� Ư�� ���ڰ� ������ ���� ����� 
	while (stream >> token1) {
		arr[i] = token1;
		i++;
		if (i > 2) // find �� ���ڿ��� ������ ������ i == 2�̱� ������ (��:find 3123/������/3) i == 3 �̻��̶�� �� ������ �����Ѵٴ� �� 
		{
			cout << "���� : �Է� ���ڵ� ���̿� ������ ������ �� �˴ϴ�." << endl;
			sORf = false;
			break;
		}
		else if (i == 2)
		{
			for (char j = 33; j <= 46; j++) //�ƽ�Ű�ڵ� ���� Ư������ ���� ������ �ݺ����� ��
			{
				if (arr[1].find(j) != string::npos) //���� �ش��ϴ� Ư�����ڰ� �����Ѵٸ�
				{
					SpecialCharacterIndex = 1; // Ư�������ε����� ���� 1�� �����Ŵ
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

	if (SpecialCharacterIndex == 1) //Ư������ �ε����� 1�̸� Ư�� ���ڰ� �ִٴ� ���̹Ƿ� ���� ���
	{
		//cout << "���� : �Է� ���ڵ� ���̿� '/'�� ������ Ư�� ���ڰ� ������ �� �˴ϴ�." << endl;
		cout << "������ ���Ͽ��� ���ϴ� ������ �˻��ϴ� ��ɾ�" << endl;
		cout << "���Ǿ� : # �˻� ���� find f" << endl;
		cout << "���� : �˻����(�����ȣ, �����̸�, �г�, ����/����)" << endl;
		cout << "���� : �˻���Ҹ� �Է¹ް�, ���͸��� ������� ����մϴ�." << endl;
		sORf = false;
	}
	//cout << "arr[1] :" << arr[1] <<"a" << endl;

	if (arr[1].empty() == 0) {
		if (arr[1].back() == '/' || arr[1].front() == '/') // ������ ù��° ���ڳ� ������ ���ڰ� /�̸� ���� ���
		{
			//cout << "���� : '/'�� ���ڿ� ���̿� �־�� �մϴ�." << endl;
			cout << "������ ���Ͽ��� ���ϴ� ������ �˻��ϴ� ��ɾ�" << endl;
			cout << "���Ǿ� : # �˻� ���� find f" << endl;
			cout << "���� : �˻����(�����ȣ, �����̸�, �г�, ����/����)" << endl;
			cout << "���� : �˻���Ҹ� �Է¹ް�, ���͸��� ������� ����մϴ�." << endl;
			sORf = false;
		}
	}

	if (sORf == true) { // �����ȣ/�����̸�/�г�/�а� ���ڿ��� �����̳� Ư�����ڰ� ������ �� �غκ��� ������ �� �ǵ��� �մϴ�.

		command = arr[1]; //find ���� ���ڿ��� ���ϴ�.

		//cout << "command : " << command << endl;
		int grade = 10000;
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

		if (searchs.size() > 4) // �������� ���� (���ڰ� 5�� �̻��� �Ǵ� ���)
		{
			cout << "������ ���Ͽ��� ���ϴ� ������ �˻��ϴ� ��ɾ�" << endl;
			cout << "���Ǿ� : # �˻� ���� find f" << endl;
			cout << "���� : �˻����(�����ȣ, �����̸�, �г�, ����/����)" << endl;
			cout << "���� : �˻���Ҹ� �Է¹ް�, ���͸��� ������� ����մϴ�." << endl;
			sORf = false;
		}

		if ((searchs.size() <= 4) && searchs.size() >= 1) {
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
						if (i >= 0 && i <= 4 && grade == 10000)
						{
							grade = i;
						}
						else if (i > 4)
						{
							sORf = false;
							cout << "������ ���Ͽ��� ���ϴ� ������ �˻��ϴ� ��ɾ�" << endl;
							cout << "���Ǿ� : # �˻� ���� find f" << endl;
							cout << "���� : �˻����(�����ȣ, �����̸�, �г�, ����/����)" << endl;
							cout << "���� : �˻���Ҹ� �Է¹ް�, ���͸��� ������� ����մϴ�." << endl;

						}
						else if (grade != 10000)
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
						/*
						cout << "���� : ������ �ʴ� �Է��Դϴ�.." << endl;
						cout << "'�����̸�' �˻���ҿ� ��� �ѱ��� �ϳ� �̻� ���� �մϴ�." << endl;
						cout << "'�����ȣ' �˻���Ҵ� 4�ڸ� ���ڷθ� �̷�����ϴ�." << endl;
						cout << "'�г�' �˻���Ҵ� 1�ڸ� ���ڷθ� �̷�����ϴ�." << endl;
						*/
						cout << "������ ���Ͽ��� ���ϴ� ������ �˻��ϴ� ��ɾ�" << endl;
						cout << "���Ǿ� : # �˻� ���� find f" << endl;
						cout << "���� : �˻����(�����ȣ, �����̸�, �г�, ����/����)" << endl;
						cout << "���� : �˻���Ҹ� �Է¹ް�, ���͸��� ������� ����մϴ�." << endl;
						break;
					}


				}
				else //���ڿ��� ���������� �ٲٴµ� ���� 
				{
					vector<string> koreanVec;
					for (int i = 0; i < search.length(); i += 2)
					{
						koreanVec.push_back(search.substr(i, 2));
					}
					for (int j = 0; j < koreanVec.size(); j++)
					{
						if (koreanVec[i] == "��" ||
							koreanVec[i] == "��" ||
							koreanVec[i] == "��" ||
							koreanVec[i] == "��" ||
							koreanVec[i] == "��" ||
							koreanVec[i] == "��" ||
							koreanVec[i] == "��" ||
							koreanVec[i] == "��" ||
							koreanVec[i] == "��" ||
							koreanVec[i] == "��" ||
							koreanVec[i] == "��" ||
							koreanVec[i] == "��" ||
							koreanVec[i] == "��" ||
							koreanVec[i] == "��" ||
							koreanVec[i] == "��" ||
							koreanVec[i] == "��" ||
							koreanVec[i] == "��" ||
							koreanVec[i] == "��" ||
							koreanVec[i] == "��" ||
							koreanVec[i] == "��" ||
							koreanVec[i] == "��" ||
							koreanVec[i] == "��" ||
							koreanVec[i] == "��" ||
							koreanVec[i] == "��" ||
							koreanVec[i] == "��" ||
							koreanVec[i] == "��" ||
							koreanVec[i] == "��" ||
							koreanVec[i] == "��" ||
							koreanVec[i] == "��" ||
							koreanVec[i] == "��" ||
							koreanVec[i] == "��" ||
							koreanVec[i] == "��" ||
							koreanVec[i] == "��" ||
							koreanVec[i] == "��" ||
							koreanVec[i] == "��" ||
							koreanVec[i] == "��" ||
							koreanVec[i] == "��" ||
							koreanVec[i] == "��" ||
							koreanVec[i] == "" ||
							koreanVec[i] == "��")
						{
							sORf = false;
							cout << "������ ���Ͽ��� ���ϴ� ������ �˻��ϴ� ��ɾ�" << endl;
							cout << "���Ǿ� : # �˻� ���� find f" << endl;
							cout << "���� : �˻����(�����ȣ, �����̸�, �г�, ����/����)" << endl;
							cout << "���� : �˻���Ҹ� �Է¹ް�, ���͸��� ������� ����մϴ�." << endl;
							break;
						}
					}
					if (search.length() >= 4)
					{
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
				if (major == "����")
				{
					if (grade != 0 && grade != 10000)
					{
						sORf = false;
						cout << "���� : �Էµ� <����/����>�� �ش� <�г�>�� ������ �� �����ϴ�." << endl;
						cout << "<����/����>�� ""����""�� ��� <�г�>�� �ݵ�� 0�̾�� �մϴ�." << endl;
						break;
					}
				}
				else if (major != "0") // major�� 0�� �ƴϰ� ���絵 �ƴ� �� ������
				{
					if (grade == 0) //�ٵ� �г��� 0�̸� ���� ���
					{
						sORf = false;
						cout << "���� : �Էµ� <����/����>�� �ش� <�г�>�� ������ �� �����ϴ�." << endl;
						cout << "<����/����>�� ""����""�� ��� <�г�>�� �ݵ�� 0�̾�� �մϴ�." << endl;
						break;
					}
				}

			}
		}


		//�� �ڷ����� �и��ż� �� �� Ȯ��
	/*
		cout << "grade :" << grade << endl;
		cout << "id : " << id << endl;
		cout << "name : " << name << endl;
		cout << "major : " << major << endl;
	*/

		if (sORf == true)
		{
			for (int i = 0; i < 10000; i++)
			{
				if (Subject[i] != NULL) {
					//���� �ϳ��� ������ ��ü ���
					if (id == "0" && name == "0" && grade == 10000 && major == "0")
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
					if (id == Subject[i]->id && name == "0" && grade == 10000 && major == "0")
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
					if (id == "0" && name == Subject[i]->name && grade == 10000 && major == "0")
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
					if (id == "0" && name == "0" && grade == 10000 && major == Subject[i]->major)
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
					if (id == Subject[i]->id && name == Subject[i]->name && grade == 10000 && major == "0")
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
					if (id == Subject[i]->id && name == "0" && grade == 10000 && major == Subject[i]->major)
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
					if (id == "0" && name == Subject[i]->name && grade == 10000 && major == Subject[i]->major)
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
					if (id == Subject[i]->id && name == Subject[i]->name && grade == 10000 && major == Subject[i]->major)
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