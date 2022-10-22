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
		cout << "문법 형식에 위배됩니다. logout 뒤에는 인자가 없어야 합니다." << endl;
	}
	if (command.empty() == 1) {
		User_info_menu();
	}
}
void Search(string command) {
	stringstream stream;
	stream.str(command);
	string token1;
	string arr[100] = { "0" }; //arr[0]에 find, arr[1]에 과목번호/과목이름/학년/학과 문자열이 들어옴
	int i = 0;
	bool sORf = true;

	while (stream >> token1) {
		arr[i] = token1;
		i++;
		if (i > 2) // find 뒤 문자열에 공백이 없으면 i == 2이기 때문에 (예:find 3123/전기프/3) i == 3 이상이라는 건 공백이 존재한다는 뜻 
		{
			cout << "문법 형식에 위배됩니다. 입력 인자들 사이에 공백이 있으면 안 됩니다." << endl;
			sORf = false;
			break;
		}
		else if (i == 2)
		{
			char* chars = new char[arr[1].length() + 1];
			arr[1].copy(chars, arr[1].length());
			chars[arr[1].length()] = '\0';
			for (int j = 0; j < arr[1].length(); j++)
			{
				// 아스키코드 상의 특수문자가 있으면 오류 출력
				// 과목이름이 알파벳으로만 구성되어 있으면 걍 알파벳만 아스키코드 포함시킨 뒤 not 하면 되는데...
				// 한글이 껴있다보니 하트나 네모 등의 특수문자까지 제거하려면 모든 경우의 수를 일일이 다 제거해줘야 돼서 현실적으로 어려울 것 같습니다. 
				if ((chars[j] >= 33 && chars[j] <= 46) || (chars[j] >= 58 && chars[j] <= 64) || (chars[j] >= 91 && chars[j] <= 95) || (chars[j] >= 123 && chars[j] <= 126)) // 47은 '/'라서 46까지만
				{
					cout << "문법 형식에 위배됩니다. 입력 인자들 사이에 '/'를 제외한 특수 문자가 있으면 안 됩니다." << endl;
					sORf = false;
					break;
				}
			}
		}
	}
	if (sORf == true) { // 과목번호/과목이름/학년/학과 문자열에 공백이나 특수문자가 있으면 이 밑부분은 실행이 안 되도록 합니다.
		command = arr[1]; //arr[1]에 
		//cout << command << endl;
		//cout << "arr0 : " << arr[0] << endl;
		//cout << "arr1 : " << arr[1] << endl;
		//cout << "arr2 : " << arr[2] << endl;

		int grade = 5;
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
			//여기다가 인덱스 넣어서 숫자 체크하고
		}
		//밖으로 빼서 searchs[0 ~ 3]까지 숫자 넣고
		// 널 포인터 접근 체크하고
		// 문자열 하나하나 요소 다 검사해서 특수문자 있는지 다 빼고
		// 특수문자 있으면 오류 출력하고 false 넣어서 종료.

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
				//int i = 0;
				//__int64 i = 0;
				long double i = 0; // 이 경우엔 더 넓은 수의 범위까지 커버 가능함 2147483647을 초과하는 수가 들어가면 그것도 과목 이름으로 분류하기 때문에 long double을 써서 입력되는 범위의 값을 증가시킴

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
							sORf = false;
							cout << "오류 : 검색요소가 중복됩니다." << endl;
							cout << "'학년' 검색요소가 중복해서 존재합니다." << endl;
							break;
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
							break;
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
						cout << "오류 : 허용되지 않는 입력입니다.." << endl;
						cout << "'과목이름' 검색요소엔 영어나 한글이 하나 이상 들어가야 합니다." << endl;
						cout << "'과목번호' 검색요소는 4자리 숫자로만 이루어집니다." << endl;
						cout << "'학년' 검색요소는 1자리 숫자로만 이루어집니다." << endl;
						break;
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
								break;
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
								break;
							}
						}
					}
					else // 숫자가 아닌 문자열의 길이가 4 미만일 경우
					{
						if (name == "0") //name이 "0"이면 과목이름에 넣어줌
						{
							name = search;
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
		/*
		cout << "grade :" << grade << endl;
		cout << "id : " << id << endl;
		cout << "name : " << name << endl;
		cout << "major : " << major << endl;
		*/

		if (sORf == true) {
			for (int i = 0; i < 10000; i++)
			{
				if (Subject[i] != NULL) {
					//인자 하나도 없으면 전체 출력
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

					//과목번호만 비교해서 검색
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

					//과목이름만 비교해서 검색
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

					//학년만 비교해서 검색
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

					//전공/교양만 비교해서 검색
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

					//과목번호,과목이름만 비교해서 검색
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

					//과목번호,학년만 비교해서 검색
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

					//과목번호,전공/교양만 비교해서 검색
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

					//과목이름, 학년만 비교해서 검색
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

					//과목이름,전공/교양만 비교해서 검색
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

					//학년, 전공/교양만 비교해서 검색
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

					//과목번호, 과목이름, 학년만 비교해서 검색
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

					//과목번호, 과목이름, 전공/교양만 비교해서 검색
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

					//과목번호, 학년, 전공/교양만 비교해서 검색
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

					//과목 이름, 학년, 전공/교양만 비교해서 검색
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

					//과목번호, 과목이름, 학년, 전공/교양만 비교해서 검색
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