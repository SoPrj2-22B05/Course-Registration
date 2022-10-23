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
		cout << "오류 : logout 뒤에는 인자가 없어야 합니다." << endl;
		return false;
	}
	if (command.empty() == 1) {
		return true;
	}
}
/*
Search("find 1/1/1/1/1");
Search("find 5");
Search("find ㅋㅍㅌ");
Search("find 전공/0");
Search("find 0/컴퓨터");
*/

void Search(string command) {
	//cout << "Search로 받는 인자 : " << command << endl; // 인자 확인
	bool sORf = true;
	stringstream stream;
	stream.str(command);
	string token1;
	string arr[100] = { "0" }; //arr[0]에 find, arr[1]에 과목번호/과목이름/학년/학과 문자열이 들어옴
	int i = 0;
	int SpecialCharacterIndex = 0;

	//인자들 사이에 공백이나 특수 문자가 있으면 오류 띄워줌 
	while (stream >> token1) {
		arr[i] = token1;
		i++;
		if (i > 2) // find 뒤 문자열에 공백이 없으면 i == 2이기 때문에 (예:find 3123/전기프/3) i == 3 이상이라는 건 공백이 존재한다는 뜻 
		{
			cout << "오류 : 입력 인자들 사이에 공백이 있으면 안 됩니다." << endl;
			sORf = false;
			break;
		}
		else if (i == 2)
		{
			for (char j = 33; j <= 46; j++) //아스키코드 상의 특수문자 범위 내에서 반복문을 돔
			{
				if (arr[1].find(j) != string::npos) //만약 해당하는 특수문자가 존재한다면
				{
					SpecialCharacterIndex = 1; // 특수문자인덱스의 값을 1로 변경시킴
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

	if (SpecialCharacterIndex == 1) //특수문자 인덱스가 1이면 특수 문자가 있다는 뜻이므로 오류 출력
	{
		cout << "오류 : 입력 인자들 사이에 '/'를 제외한 특수 문자가 있으면 안 됩니다." << endl;
		find_help_print();
		return;
	}
	//cout << "arr[1] :" << arr[1] <<"a" << endl;

	if (arr[1].empty() == 0) {	//인자가 존재할 때
		if (arr[1].back() == '/' || arr[1].front() == '/') // 인자의 첫번째 문자나 마지막 문자가 /이면 오류 출력
		{
			cout << "오류 : '/'는 문자열 사이에 있어야 합니다." << endl;
			find_help_print();
			return;
		}
	}

	if (sORf == true) { // 과목번호/과목이름/학년/학과 문자열에 공백이나 특수문자가 있으면 이 밑부분은 실행이 안 되도록 합니다.

		command = arr[1]; //find 뒤의 문자열이 들어갑니다.
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

		//문자열을 '/' 기준으로 자릅니다.
		while (getline(ss, token2, '/'))
		{
			searchs.push_back(token2);
		}

		if (searchs.size() > 4) // 문법형식 위배 (인자가 5개 이상이 되는 경우)
		{
			find_help_print();
			return;
		}

		if ((searchs.size() <= 4) && searchs.size() > 0) {
			// 자른 문자열 중 과목번호, 과목이름, 학년, 전공/교양을 구분합니다.
			for (auto search : searchs)
			{
				//int i = 0;
				//__int64 i = 0;
				long double i = 0; // 이 경우엔 더 넓은 수의 범위까지 커버 가능함 2147483647을 초과하는 수가 들어가면 그것도 과목 이름으로 분류하기 때문에 long double을 써서 입력되는 범위의 값을 증가시킴

				stringstream ssInt(search);
				ssInt >> i;
				if (!ssInt.fail()) //만약 문자열을 정수형으로 바꾸는데 성공하면 (즉, 과목번호나 학년을 입력하면)
				{
					if (search.size() == 1) // 문자열의 길이가 1이면 학년에 해당 숫자를 넣어주고
					{
						if (i >= 0 && i <= 4 && grade == 10000)
						{
							grade = i;
						}
						else if (grade != 10000)
						{
							sORf = false;
							cout << "오류 : 검색요소가 중복됩니다." << endl;
							cout << "'학년' 검색요소가 중복해서 존재합니다." << endl;
							return;
						}
						else if (i >= 5 && i <= 9 && grade == 10000) {
							find_help_print();
							return;
						}
					}
					else if (search.size() == 4) // 문자열의 길이가 4면 과목번호에 넣어줍니다.
					{
						if (id == "0")
						{
							id = search;
						}
						else
						{
							sORf = false;
							cout << "오류 : 검색요소가 중복됩니다." << endl;
							cout << "'과목번호' 검색요소가 중복해서 존재합니다." << endl;
							return;
						}
					}
					/*
					else //숫자인 문자열의 길이가 1도 아니고 4도 아닐 경우 (2,3 또는 5  이상) 숫자를 과목 이름에 넣어줌
					{
						if (name == "0")
						{
							name = search;
						}
					}*/

					else //숫자인 문자열의 길이가 1도 아니고 4도 아닐 경우
					{
						sORf = false;
						/*
						cout << "오류 : 허용되지 않는 입력입니다.." << endl;
						cout << "'과목이름' 검색요소엔 영어나 한글이 하나 이상 들어가야 합니다." << endl;
						cout << "'과목번호' 검색요소는 4자리 숫자로만 이루어집니다." << endl;
						cout << "'학년' 검색요소는 1자리 숫자로만 이루어집니다." << endl;
						*/
						find_help_print();
						return;
					}


				}
				else //문자열을 정수형으로 바꾸는데 실패 
				{
					if (search.length() >= 4) {
						if (search.substr(search.length() - 4) == "학과" || search.substr(search.length() - 4) == "학부" || search == "교양")
						{
							if (major == "0")
							{
								major = search;
							}
							else
							{
								sORf = false;
								cout << "오류 : 검색요소가 중복됩니다." << endl;
								cout << "'전공/교양' 검색요소가 중복해서 존재합니다." << endl;
								return;
							}
						}
						else // 학과나 학부나 교양이라는 게 search에 없으면 바로 과목 이름으로 넣어줌
						{
							if (name == "0")
							{
								name = search;
							}
							else
							{
								sORf = false;
								cout << "오류 : 검색요소가 중복됩니다." << endl;
								cout << "'과목이름' 검색요소가 중복해서 존재합니다." << endl;
								return;
							}
						}
					}
					else // 숫자가 아닌 문자열의 길이가 4 미만일 경우
					{
						if (name == "0") //name이 "0"이면 과목이름에 넣어줌
						{
							name = search;
						}
						else {
							cout << "오류 : 검색요소가 중복됩니다." << endl;
							cout << "'과목이름' 검색요소가 중복해서 존재합니다." << endl;
							return;
						}
					}
				}
				if (major == "교양")
				{
					if (grade != 0 && grade != 10000)
					{
						sORf = false;
						cout << "오류 : 입력된 <전공/교양>에 해당 <학년>이 존재할 수 없습니다." << endl;
						cout << "<전공/교양>이 ""교양""일 경우 <학년>은 반드시 0이어야 합니다." << endl;
						return;
					}
				}
				else if(major != "0")
				{
					if (grade == 0)
					{
						sORf = false;
						cout << "오류 : 입력된 <전공/교양>에 해당 <학년>이 존재할 수 없습니다." << endl;
						cout << "<전공/교양>이 ""학과""나 ""학부""로 끝날 경우 <학년>은 반드시 1,2,3,4중 하나여야 합니다." << endl;
						return;
					}
				}
			}
		}


		//각 자료형에 분리돼서 들어간 거 확인
		/*
		cout << "grade :" << grade << endl;
		cout << "id : " << id << endl;
		cout << "name : " << name << endl;
		cout << "major : " << major << endl;
		*/

		if (sORf == true) {
			bool findSuccess = false;
			for (int i = 0; i < 10000; i++)
			{
				if (Subject[i] != NULL) {
					//인자 하나도 없으면 전체 출력
					if (id == "0" && name == "0" && grade == 10000 && major == "0")
					{
						findSuccess = true;
						cout << Subject[i]->id << " | ";
						cout << Subject[i]->name << " | ";
						cout << Subject[i]->credit << " | ";
						cout << Subject[i]->major << " | ";
						cout << Subject[i]->grade << " | ";
						cout << Subject[i]->time << " | ";
						cout << Subject[i]->max << endl;
					}

					//과목번호만 비교해서 검색
					if (id == Subject[i]->id && name == "0" && grade == 10000 && major == "0")
					{
						findSuccess = true;
						cout << Subject[i]->id << " | ";
						cout << Subject[i]->name << " | ";
						cout << Subject[i]->credit << " | ";
						cout << Subject[i]->major << " | ";
						cout << Subject[i]->grade << " | ";
						cout << Subject[i]->time << " | ";
						cout << Subject[i]->max << endl;
					}

					//과목이름만 비교해서 검색
					if (id == "0" && name == Subject[i]->name && grade == 10000 && major == "0")
					{
						findSuccess = true;
						cout << Subject[i]->id << " | ";
						cout << Subject[i]->name << " | ";
						cout << Subject[i]->credit << " | ";
						cout << Subject[i]->major << " | ";
						cout << Subject[i]->grade << " | ";
						cout << Subject[i]->time << " | ";
						cout << Subject[i]->max << endl;
					}

					//학년만 비교해서 검색
					if (id == "0" && name == "0" && grade == Subject[i]->grade && major == "0")
					{
						findSuccess = true;
						cout << Subject[i]->id << " | ";
						cout << Subject[i]->name << " | ";
						cout << Subject[i]->credit << " | ";
						cout << Subject[i]->major << " | ";
						cout << Subject[i]->grade << " | ";
						cout << Subject[i]->time << " | ";
						cout << Subject[i]->max << endl;
					}

					//전공/교양만 비교해서 검색
					if (id == "0" && name == "0" && grade == 10000 && major == Subject[i]->major)
					{
						findSuccess = true;
						cout << Subject[i]->id << " | ";
						cout << Subject[i]->name << " | ";
						cout << Subject[i]->credit << " | ";
						cout << Subject[i]->major << " | ";
						cout << Subject[i]->grade << " | ";
						cout << Subject[i]->time << " | ";
						cout << Subject[i]->max << endl;
					}

					//과목번호,과목이름만 비교해서 검색
					if (id == Subject[i]->id && name == Subject[i]->name && grade == 10000 && major == "0")
					{
						findSuccess = true;
						cout << Subject[i]->id << " | ";
						cout << Subject[i]->name << " | ";
						cout << Subject[i]->credit << " | ";
						cout << Subject[i]->major << " | ";
						cout << Subject[i]->grade << " | ";
						cout << Subject[i]->time << " | ";
						cout << Subject[i]->max << endl;
					}

					//과목번호,학년만 비교해서 검색
					if (id == Subject[i]->id && name == "0" && grade == Subject[i]->grade && major == "0")
					{
						findSuccess = true;
						cout << Subject[i]->id << " | ";
						cout << Subject[i]->name << " | ";
						cout << Subject[i]->credit << " | ";
						cout << Subject[i]->major << " | ";
						cout << Subject[i]->grade << " | ";
						cout << Subject[i]->time << " | ";
						cout << Subject[i]->max << endl;
					}

					//과목번호,전공/교양만 비교해서 검색
					if (id == Subject[i]->id && name == "0" && grade == 10000 && major == Subject[i]->major)
					{
						findSuccess = true;
						cout << Subject[i]->id << " | ";
						cout << Subject[i]->name << " | ";
						cout << Subject[i]->credit << " | ";
						cout << Subject[i]->major << " | ";
						cout << Subject[i]->grade << " | ";
						cout << Subject[i]->time << " | ";
						cout << Subject[i]->max << endl;
					}

					//과목이름, 학년만 비교해서 검색
					if (id == "0" && name == Subject[i]->name && grade == Subject[i]->grade && major == "0")
					{
						findSuccess = true;
						cout << Subject[i]->id << " | ";
						cout << Subject[i]->name << " | ";
						cout << Subject[i]->credit << " | ";
						cout << Subject[i]->major << " | ";
						cout << Subject[i]->grade << " | ";
						cout << Subject[i]->time << " | ";
						cout << Subject[i]->max << endl;
					}

					//과목이름,전공/교양만 비교해서 검색
					if (id == "0" && name == Subject[i]->name && grade == 10000 && major == Subject[i]->major)
					{
						findSuccess = true;
						cout << Subject[i]->id << " | ";
						cout << Subject[i]->name << " | ";
						cout << Subject[i]->credit << " | ";
						cout << Subject[i]->major << " | ";
						cout << Subject[i]->grade << " | ";
						cout << Subject[i]->time << " | ";
						cout << Subject[i]->max << endl;
					}

					//학년, 전공/교양만 비교해서 검색
					if (id == "0" && name == "0" && grade == Subject[i]->grade && major == Subject[i]->major)
					{
						findSuccess = true;
						cout << Subject[i]->id << " | ";
						cout << Subject[i]->name << " | ";
						cout << Subject[i]->credit << " | ";
						cout << Subject[i]->major << " | ";
						cout << Subject[i]->grade << " | ";
						cout << Subject[i]->time << " | ";
						cout << Subject[i]->max << endl;
					}

					//과목번호, 과목이름, 학년만 비교해서 검색
					if (id == Subject[i]->id && name == Subject[i]->name && grade == Subject[i]->grade && major == "0")
					{
						findSuccess = true;
						cout << Subject[i]->id << " | ";
						cout << Subject[i]->name << " | ";
						cout << Subject[i]->credit << " | ";
						cout << Subject[i]->major << " | ";
						cout << Subject[i]->grade << " | ";
						cout << Subject[i]->time << " | ";
						cout << Subject[i]->max << endl;
					}

					//과목번호, 과목이름, 전공/교양만 비교해서 검색
					if (id == Subject[i]->id && name == Subject[i]->name && grade == 10000 && major == Subject[i]->major)
					{
						findSuccess = true;
						cout << Subject[i]->id << " | ";
						cout << Subject[i]->name << " | ";
						cout << Subject[i]->credit << " | ";
						cout << Subject[i]->major << " | ";
						cout << Subject[i]->grade << " | ";
						cout << Subject[i]->time << " | ";
						cout << Subject[i]->max << endl;
					}

					//과목번호, 학년, 전공/교양만 비교해서 검색
					if (id == Subject[i]->id && name == "0" && grade == Subject[i]->grade && major == Subject[i]->major)
					{
						findSuccess = true;
						cout << Subject[i]->id << " | ";
						cout << Subject[i]->name << " | ";
						cout << Subject[i]->credit << " | ";
						cout << Subject[i]->major << " | ";
						cout << Subject[i]->grade << " | ";
						cout << Subject[i]->time << " | ";
						cout << Subject[i]->max << endl;
					}

					//과목 이름, 학년, 전공/교양만 비교해서 검색
					if (id == "0" && name == Subject[i]->name && grade == Subject[i]->grade && major == Subject[i]->major)
					{
						findSuccess = true;
						cout << Subject[i]->id << " | ";
						cout << Subject[i]->name << " | ";
						cout << Subject[i]->credit << " | ";
						cout << Subject[i]->major << " | ";
						cout << Subject[i]->grade << " | ";
						cout << Subject[i]->time << " | ";
						cout << Subject[i]->max << endl;
					}

					//과목번호, 과목이름, 학년, 전공/교양만 비교해서 검색
					if (id == Subject[i]->id && name == Subject[i]->name && grade == Subject[i]->grade && major == Subject[i]->major)
					{
						findSuccess = true;
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
			if (findSuccess == false) {
				find_help_print();
				return;
			}
		}
	}
}