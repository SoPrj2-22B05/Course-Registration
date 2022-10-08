#include <iostream>
#include <string>
#include <fstream>
#include <cstdio>
#include <sstream>
#include <vector>
using namespace std;


//구조체 배열 이미 생성되었다고 가정하고 코딩 진행
//아마 serach에 구조체 배열 인자로 넣어주긴 해야 될텐데 일단은 비워둠
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


	//문자열을 '/' 기준으로 자릅니다.
	while (getline(ss, token, '/'))
	{
		names.push_back(token);
	}
	if (names.size() > 4) {
		cout << "데이터 파일에서 원하는 과목을 검색하는 명령어" << endl;
		cout << "동의어 : # 검색 ㄱㅅ find f" << endl;
		cout << "인자 : 검색요소(과목번호, 과목이름, 학년, 전공/교양)" << endl;
		cout << "동작 : 검색요소를 입력받고, 필터링된 과목들을 출력합니다." << endl;
	}

	if ((names.size() <= 4) && names.size() > 0) {
		// 자른 문자열 중 과목번호, 과목이름, 학년, 전공/교양을 구분합니다.
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
						cout << "오류 : 검색요소가 중복됩니다." << endl;
						cout << "'학년' 검색요소가 중복해서 존재합니다." << endl;
						break;
					}

				}
				if (i > 4 && i < 10000) // 과목번호는 무조건 4보다는 높아야 될 거 같습니다. 문자열에서 숫자로 변환하면 1 ~ 4는 학년이랑 과목번호랑 구분이 안 되네요.
				{
					if (SubjectNumber == 0)
					{
						SubjectNumber = i;
					}
					else
					{
						cout << "오류 : 검색요소가 중복됩니다." << endl;
						cout << "'과목번호' 검색요소가 중복해서 존재합니다." << endl;
						break;
					}
				}
			}
			else
			{
				if (name.substr(name.length() - 4) == "학과" || name.substr(name.length() - 4) == "학부" || name == "교양")
				{
					if (majorORnot == "0") {
						majorORnot = name;
						if (majorORnot == "교양")
						{
							if (grade != 0)
							{
								cout << "오류 : 입력된 <전공/교양>에 해당 <학년>이 존재할 수 없습니다." << endl;
								cout << "<전공/교양>이 ""교양""일 경우 <학년>은 반드시 0이어야 합니다." << endl;
								break;
							}
						}
					}
					else
					{
						cout << "오류 : 검색요소가 중복됩니다." << endl;
						cout << "'전공/교양' 검색요소가 중복해서 존재합니다." << endl;
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
						cout << "오류 : 검색요소가 중복됩니다." << endl;
						cout << "'과목이름' 검색요소가 중복해서 존재합니다." << endl;
						break;
					}
				}
			}
		}
	}

	//분리된 거 확인
	cout << "grade :" << grade << endl;
	cout << "SubjectNumber : " << SubjectNumber << endl;
	cout << "subjectName : " << subjectName << endl;
	cout << "majorORnot : " << majorORnot << endl;
}