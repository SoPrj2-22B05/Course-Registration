#include <iostream>
#include <string>
#include <fstream>
#include <cstdio>
#include <sstream>
#include <vector>
using namespace std;


//����ü �迭 �̹� �����Ǿ��ٰ� �����ϰ� �ڵ� ����
//�Ƹ� serach�� ����ü �迭 ���ڷ� �־��ֱ� �ؾ� ���ٵ� �ϴ��� �����
void serach() {
	cout << "find" << " ";

	int grade = 5;
	int SubjectNumber = 0;
	string majorORnot = "0";
	string subjectName = "0";

	string str;
	cin >> str;
	vector<string> names;
	stringstream ss(str);
	string token;


	//���ڿ��� '/' �������� �ڸ��ϴ�.
	while (getline(ss, token, '/'))
	{
		names.push_back(token);
	}
	if (names.size() > 4) {
		cout << "������ ���Ͽ��� ���ϴ� ������ �˻��ϴ� ��ɾ�" << endl;
		cout << "���Ǿ� : # �˻� ���� find f" << endl;
		cout << "���� : �˻����(�����ȣ, �����̸�, �г�, ����/����)" << endl;
		cout << "���� : �˻���Ҹ� �Է¹ް�, ���͸��� ������� ����մϴ�." << endl;
	}

	if ((names.size() <= 4) && names.size() > 0) {
		// �ڸ� ���ڿ� �� �����ȣ, �����̸�, �г�, ����/������ �����մϴ�.
		for (auto name : names)
		{
			int i = 0;
			stringstream ssInt(name);
			ssInt >> i;
			if (!ssInt.fail())
			{
				if (i >= 0 && i <= 4)
				{
					if (grade == 5)
					{
						grade = i;
					}
					else
					{
						cout << "���� : �˻���Ұ� �ߺ��˴ϴ�." << endl;
						cout << "'�г�' �˻���Ұ� �ߺ��ؼ� �����մϴ�." << endl;
						break;
					}

				}
				if (i > 4 && i < 10000) // �����ȣ�� ������ 4���ٴ� ���ƾ� �� �� �����ϴ�. ���ڿ����� ���ڷ� ��ȯ�ϸ� 1 ~ 4�� �г��̶� �����ȣ�� ������ �� �ǳ׿�.
				{
					if (SubjectNumber == 0)
					{
						SubjectNumber = i;
					}
					else
					{
						cout << "���� : �˻���Ұ� �ߺ��˴ϴ�." << endl;
						cout << "'�����ȣ' �˻���Ұ� �ߺ��ؼ� �����մϴ�." << endl;
						break;
					}
				}
			}
			else
			{
				if (name.substr(name.length() - 4) == "�а�" || name.substr(name.length() - 4) == "�к�" || name == "����")
				{
					if (majorORnot == "0") {
						majorORnot = name;
						if (majorORnot == "����")
						{
							if (grade != 0)
							{
								cout << "���� : �Էµ� <����/����>�� �ش� <�г�>�� ������ �� �����ϴ�." << endl;
								cout << "<����/����>�� ""����""�� ��� <�г�>�� �ݵ�� 0�̾�� �մϴ�." << endl;
								break;
							}
						}
					}
					else
					{
						cout << "���� : �˻���Ұ� �ߺ��˴ϴ�." << endl;
						cout << "'����/����' �˻���Ұ� �ߺ��ؼ� �����մϴ�." << endl;
						break;
					}
				}
				else
				{
					if (subjectName == "0")
					{
						subjectName = name;
					}
					else
					{
						cout << "���� : �˻���Ұ� �ߺ��˴ϴ�." << endl;
						cout << "'�����̸�' �˻���Ұ� �ߺ��ؼ� �����մϴ�." << endl;
						break;
					}
				}
			}
		}
	}

	//�и��� �� Ȯ��
	cout << "grade :" << grade << endl;
	cout << "SubjectNumber : " << SubjectNumber << endl;
	cout << "subjectName : " << subjectName << endl;
	cout << "majorORnot : " << majorORnot << endl;
}