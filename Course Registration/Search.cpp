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
		cout << "문법 형식에 위배됩니다. (인자가 없어야 함)" << endl;
}
void Search(string command) {
	
	//초기화
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
	
	//문자열을 '/' 기준으로 자릅니다.
	while (getline(ss, token, '/'))
	{
		searchs.push_back(token);
	}
	
	if (searchs.size() > 4) // 문법형식 위배 (인자가 5개 이상이 되는 경우)
	{
		cout << "데이터 파일에서 원하는 과목을 검색하는 명령어" << endl;
		cout << "동의어 : # 검색 ㄱㅅ find f" << endl;
		cout << "인자 : 검색요소(과목번호, 과목이름, 학년, 전공/교양)" << endl;
		cout << "동작 : 검색요소를 입력받고, 필터링된 과목들을 출력합니다." << endl;
	}

	if ((searchs.size() <= 4) && searchs.size() > 0) {
		// 자른 문자열 중 과목번호, 과목이름, 학년, 전공/교양을 구분합니다.
		for (auto search : searchs)
		{
			int i = 0;
			stringstream ssInt(search);
			ssInt >> i;
			if (!ssInt.fail()) //만약 문자열을 정수형으로 바꾸는데 성공하면 (즉, 과목번호나 학년을 입력하면)
			{
				if (search.size() == 1) // 문자열의 길이가 1이면 학년에 해당 숫자를 넣어주고
				{
					if (grade == 5)
					{
						grade = i;
					}
					else
					{
						bool sORf = false;
						cout << "오류 : 검색요소가 중복됩니다." << endl;
						cout << "'학년' 검색요소가 중복해서 존재합니다." << endl;
						break;
					}

				}
				if (search.size() == 4) // 문자열의 길이가 4면 과목번호에 넣어줍니다.
				{
					if (id == "0")
					{
						id = search;
					}
					else
					{
						bool sORf = false;
						cout << "오류 : 검색요소가 중복됩니다." << endl;
						cout << "'과목번호' 검색요소가 중복해서 존재합니다." << endl;
						break;
					}
				}
			}
			else
			{
				if (search.substr(search.length() - 4) == "학과" || search.substr(search.length() - 4) == "학부" || search == "교양")
				{
					if (major == "0")
					{
						major = search;
					}
					else
					{
						bool sORf = false;
						cout << "오류 : 검색요소가 중복됩니다." << endl;
						cout << "'전공/교양' 검색요소가 중복해서 존재합니다." << endl;
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
						cout << "오류 : 검색요소가 중복됩니다." << endl;
						cout << "'과목이름' 검색요소가 중복해서 존재합니다." << endl;
						break;
					}
				}
			}
			if (major == "교양" && grade != 0 && grade != 5)
			{
				sORf = false;
				cout << "오류 : 입력된 <전공/교양>에 해당 <학년>이 존재할 수 없습니다." << endl;
				cout << "<전공/교양>이 ""교양""일 경우 <학년>은 반드시 0이어야 합니다." << endl;
				break;

			}
		}
	}
	
	//각 자료형에 분리돼서 들어간 거 확인
	cout << "grade :" << grade << endl;
	cout << "id : " << id << endl;
	cout << "name : " << name << endl;
	cout << "major : " << major << endl;
	
	if (sORf == true) {
		for (int i = 0; i < 10000; i++)
		{
			//인자 하나도 없으면 전체 출력
			if (id == "0" && name == "0" && grade == 5 && major == "0")
			{
				cout << Subject[i]->id << " " << Subject[i]->name << " " << Subject[i]->credit << " " << Subject[i]->major << Subject[i]->grade << " " << Subject[i]->time << " " << Subject[i]->max << endl;
			}

			//과목번호만 비교해서 검색
			if (id == Subject[i]->id && name == "0" && grade == 5 && major == "0")
			{
				cout << Subject[i]->id << " " << Subject[i]->name << " " << Subject[i]->credit << " " << Subject[i]->major << Subject[i]->grade << " " << Subject[i]->time << " " << Subject[i]->max << endl;
			}

			//과목이름만 비교해서 검색
			if (id == "0" && name == Subject[i]->name && grade == 5 && major == "0")
			{
				cout << Subject[i]->id << " " << Subject[i]->name << " " << Subject[i]->credit << " " << Subject[i]->major << Subject[i]->grade << " " << Subject[i]->time << " " << Subject[i]->max << endl;
			}

			//학년만 비교해서 검색
			if (id == "0" && name == "0" && grade == Subject[i]->grade && major == "0")
			{
				cout << Subject[i]->id << " " << Subject[i]->name << " " << Subject[i]->credit << " " << Subject[i]->major << Subject[i]->grade << " " << Subject[i]->time << " " << Subject[i]->max << endl;
			}

			//전공/교양만 비교해서 검색
			if (id == "0" && name == "0" && grade == 5 && major == Subject[i]->major)
			{
				cout << Subject[i]->id << " " << Subject[i]->name << " " << Subject[i]->credit << " " << Subject[i]->major << Subject[i]->grade << " " << Subject[i]->time << " " << Subject[i]->max << endl;
			}

			//과목번호,과목이름만 비교해서 검색
			if (id == Subject[i]->id && name == Subject[i]->name && grade == 5 && major == "0")
			{
				cout << Subject[i]->id << " " << Subject[i]->name << " " << Subject[i]->credit << " " << Subject[i]->major << Subject[i]->grade << " " << Subject[i]->time << " " << Subject[i]->max << endl;
			}

			//과목번호,학년만 비교해서 검색
			if (id == Subject[i]->id && name == "0" && grade == Subject[i]->grade && major == "0")
			{
				cout << Subject[i]->id << " " << Subject[i]->name << " " << Subject[i]->credit << " " << Subject[i]->major << Subject[i]->grade << " " << Subject[i]->time << " " << Subject[i]->max << endl;
			}

			//과목번호,전공/교양만 비교해서 검색
			if (id == Subject[i]->id && name == "0" && grade == 5 && major == Subject[i]->major)
			{
				cout << Subject[i]->id << " " << Subject[i]->name << " " << Subject[i]->credit << " " << Subject[i]->major << Subject[i]->grade << " " << Subject[i]->time << " " << Subject[i]->max << endl;
			}

			//과목이름, 학년만 비교해서 검색
			if (id == "0" && name == Subject[i]->name && grade == Subject[i]->grade && major == "0")
			{
				cout << Subject[i]->id << " " << Subject[i]->name << " " << Subject[i]->credit << " " << Subject[i]->major << Subject[i]->grade << " " << Subject[i]->time << " " << Subject[i]->max << endl;
			}

			//과목이름,전공/교양만 비교해서 검색
			if (id == "0" && name == Subject[i]->name && grade == 5 && major == Subject[i]->major)
			{
				cout << Subject[i]->id << " " << Subject[i]->name << " " << Subject[i]->credit << " " << Subject[i]->major << Subject[i]->grade << " " << Subject[i]->time << " " << Subject[i]->max << endl;
			}

			//학년, 전공/교양만 비교해서 검색
			if (id == "0" && name == "0" && grade == Subject[i]->grade && major == Subject[i]->major)
			{
				cout << Subject[i]->id << " " << Subject[i]->name << " " << Subject[i]->credit << " " << Subject[i]->major << Subject[i]->grade << " " << Subject[i]->time << " " << Subject[i]->max << endl;
			}

			//과목번호, 과목이름, 학년만 비교해서 검색
			if (id == Subject[i]->id && name == Subject[i]->name && grade == Subject[i]->grade && major == "0")
			{
				cout << Subject[i]->id << " " << Subject[i]->name << " " << Subject[i]->credit << " " << Subject[i]->major << Subject[i]->grade << " " << Subject[i]->time << " " << Subject[i]->max << endl;
			}

			//과목번호, 과목이름, 전공/교양만 비교해서 검색
			if (id == Subject[i]->id && name == Subject[i]->name && grade == 5 && major == Subject[i]->major)
			{
				cout << Subject[i]->id << " " << Subject[i]->name << " " << Subject[i]->credit << " " << Subject[i]->major << Subject[i]->grade << " " << Subject[i]->time << " " << Subject[i]->max << endl;
			}

			//과목번호, 학년, 전공/교양만 비교해서 검색
			if (id == Subject[i]->id && name == "0" && grade == Subject[i]->grade && major == Subject[i]->major)
			{
				cout << Subject[i]->id << " " << Subject[i]->name << " " << Subject[i]->credit << " " << Subject[i]->major << Subject[i]->grade << " " << Subject[i]->time << " " << Subject[i]->max << endl;
			}

			//과목 이름, 학년, 전공/교양만 비교해서 검색
			if (id == "0" && name == Subject[i]->name && grade == Subject[i]->grade && major == Subject[i]->major)
			{
				cout << Subject[i]->id << " " << Subject[i]->name << " " << Subject[i]->credit << " " << Subject[i]->major << Subject[i]->grade << " " << Subject[i]->time << " " << Subject[i]->max << endl;
			}

			//과목번호, 과목이름, 학년, 전공/교양만 비교해서 검색
			if (id == Subject[i]->id && name == Subject[i]->name && grade == Subject[i]->grade && major == Subject[i]->major)
			{
				cout << Subject[i]->id << " " << Subject[i]->name << " " << Subject[i]->credit << " " << Subject[i]->major << Subject[i]->grade << " " << Subject[i]->time << " " << Subject[i]->max << endl;
			}
		}
	}
}