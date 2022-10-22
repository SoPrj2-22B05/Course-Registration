#pragma once
#include "Administrator.h"
#include "SubjectData.h"
#pragma warning(disable:4996)
#define START 1
#define END 0

using namespace std;
namespace fs = std::filesystem;

//string wstringTOstring(wstring src);
bool addEnd = false;

//기본적으로 "Course_Registration_On_Off.txt" 파일이 존재해야 함
//내용은 소문자로 바꿨을 때 on 또는 off 될 수 있는 것으로 (on On oN ON off OFF oFf 등등)
/*
테스트할 때는 아래 내용을 사용자 데이터 파일.txt에 복붙
202012345	우리돼지한돈	축산식품생명공학과	2   	58
000012345	내가관리자
202098124	고인물건덕이	테스트학과			2  	200
202018239	리처드파인만	테스트학과  			2  	132
202067890	   송강		테스트학과	  		2  	132
202083249	  배윤경   		의상디자인학과		3   	 85
201911260	  유철희		컴퓨터공학과		2	60
000067890	  리자관
*/

/*
테스트할 때는 아래 내용을 0000_전기프_출석부.txt에 복붙
202012345	우리돼지한돈	30
202067890	송강			28
201911260	유철희		30
202098124	고인물건덕이	28
202018239	리처드파인만	28
202083249	배윤경		14
*/

/*
테스트할 때는 아래 내용을 "202018239_리처드파인만_수강신청목록.txt"에 복붙 (당연히 내용 수정해도 됨)
0000	28
3867	14
8751	30
아래 내용을 "202067890_송강_수강신청목록.txt"에 복붙 (당연히 내용 수정해도 됨)
0000	28
7777	17
6666	16
아래 내용을 "202098124_고인물건덕이_수강신청목록.txt"에 복붙 (당연히 내용 수정해도 됨)
0000	28
9143	18
*/
void Administrator_menu() {
	string adminCommand;
tryAgain:
	cout << "Course Registration > ";
	cin >> adminCommand;
	if ((adminCommand.compare("로그아웃") == 0) || (adminCommand.compare("logout") == 0)) {
		return;
	}
	else if ((adminCommand.compare("시작") == 0) || (adminCommand.compare("start") == 0)) {
		bool isStart= StartOrEnd(START);
		if (isStart) {
			locale::global(std::locale("Korean"));
			wstring dir = fs::current_path();
			fs::directory_iterator itr1(dir);
			while (itr1 != fs::end(itr1)) {
				const fs::directory_entry& entry = *itr1;
				wstring filename = entry.path();
				filename.replace(0, dir.size() + 1, L"");
				if (filename.size() >= 8) {
					filename = filename.substr(filename.size() - 8);
					if (filename.compare(L"_출석부.txt") == 0) {
						fs::path p(entry.path());
						fs::remove(p);
					}
				}
				itr1++;
			}
		}
		goto tryAgain;
	}
	else if ((adminCommand.compare("종료") == 0) || (adminCommand.compare("end") == 0)) {
		bool isEnd = false;
		isEnd = StartOrEnd(END);
		if (isEnd) {
			Prioritizing();
		}

		//종료할 때 파일 삭제
		locale::global(std::locale("Korean"));
		wstring dir = fs::current_path();
		fs::directory_iterator itr2(dir);
		while (itr2 != fs::end(itr2)) {
			const fs::directory_entry& entry = *itr2;
			wstring filename = entry.path();
			filename.replace(0, dir.size() + 1, L"");
			//wcout << filename << endl;
			//cout << filename.size() << endl;
			if (filename.size() >= 11) {
				filename = filename.substr(filename.size() - 11);
				if (filename.compare(L"_수강신청목록.txt") == 0) {
					fs::path p(entry.path());
					fs::remove(p);
				}
			}
			itr2++;
		}
		// 전체 프로그램을 종료
		exit(0);
	}
	else {
		cout << "------------------------------------------------------------------" << endl;
		cout << "명령어군\t" << "| 설명" << endl;
		cout << "------------------------------------------------------------------" << endl;
		cout << "logout\t로그아웃" << "| 로그아웃하고 사용자 정보 입력 프롬프트로 돌아감" << endl;
		cout << "start\t  시작\t" << "| 수강신청 기간 시작을 의미" << endl;
		cout << "end\t  종료\t" << "| 수강신청 기간 종료를 의미" << endl;
		cout << "------------------------------------------------------------------" << endl;
		goto tryAgain;
	}
}

bool StartOrEnd(boolean command) {
	wstring dir = fs::current_path();
	wfstream isOn;
	isOn.open(dir + L"\\Course_Registration_Is_On.txt");
	if (!isOn.is_open()) {
		if (command == START) {
			//파일을 생성하고 수강신청 시작한다고 출력
			isOn.close();
			wofstream out(dir + L"\\Course_Registration_Is_On.txt");
			out.close();
			cout << "수강신청을 시작합니다." << endl;
			return true;
		}
		else if (command == END) {
			cout << "아직 수강신청이 시작되지 않았습니다." << endl;
		}
	}
	else {
		if (command == START) {
			cout << "이미 수강신청이 시작되어 시작할 수 없습니다." << endl;
		}
		else if (command == END) {
			isOn.close();
			fs::path p(dir + L"\\Course_Registration_Is_On.txt");
			fs::remove(p);
			cout << "수강신청을 종료합니다." << endl;
			return true;
		}
		/*
		else {
			cout << "Course_Registration_On_Off.txt에 허용되지 않는 문자열이 입력되어있습니다." << endl;
		}
		*/
	}
	isOn.close();
	return false;
}

void Prioritizing() { //우선순위 정하는 함수
	for (int i = 0; i < 10000; i++) {	//과목번호 0000부터 9999까지
		addEnd = false;
		wstring subjectID, subjectName, major;
		int grade, max;
		if (Subject[i] == NULL) continue;	//해당 과목번호를 가지는 과목 없으면 건너뜀
		else {								//과목 이름, 학년, 정원을 가지고 옴
			locale::global(locale("ko_KR.UTF-8"));
			subjectID = stringTOwstring(Subject[i]->id);
			subjectName = stringTOwstring(Subject[i]->name);
			major = stringTOwstring(Subject[i]->major);
			grade = Subject[i]->grade;
			max = Subject[i]->max;
		}
		//	Subject안에 내용이 안채워진 상태로 테스트하기 위한 데이터 (바로 위 if,else블록 주석처리하고 이걸 주석해제)
		/*
		subjectID = L"0000";
		subjectName = L"전기프";
		major = L"테스트학과";
		grade = 2;
		max = 4;
		*/
		locale::global(locale("ko_KR.UTF-8"));
		wstring filename = subjectID + L"_" + subjectName + L"_출석부.txt";
		wfstream f(filename);

		vector<Student> stuVector;
		vector<wstring> data;
		wstring line, str;
		wstringstream ss;
		if (f.is_open()) {
			int lineCount = 0;		//lineNumber로서, 학생 객체의 order로 들어가 6번째 우선순위에서 활용됨
			while (getline(f, line)) {
				locale::global(locale("ko_KR.UTF-8"));
				lineCount++;
				data.clear();
				ss.clear();
				// 비어있는 행인지 체크
				line = trimFunc(line);
				if (line.compare(L"") == 0) {
					cout << "출석부 파일에 빈 행이 존재" << endl;
					continue;
				}
				//data라는 vector에 wstring형태로 학번, 이름, 마일리지 넣음
				ss.str(line);
				while (getline(ss, str, L'\t')) {
					str = trimFunc(str);
					if (str != L"") {
						data.push_back(str);
					}
				}
				int mileage = stoi(data[2]);
				stuVector.push_back(Student(data[0], data[1], mileage, lineCount));

				//stuVector[lineCount-1].PrintStudentInfo();
				locale::global(locale::classic());
			}
			f.close();
			if (lineCount <= max) {
				//cout << "정원 이하로 신청함" << endl;
				//출석부 파일에 마일리지 제거하고 "학번\t이름"만 남김 !!!!!!!!!!!
				FinalizeAttendanceBook(stuVector, filename, addEnd);
				continue;	//다음 과목으로
			}
			else {
				//cout << "정원 초과하여 신청함" << endl << endl;
				//첫 번째 우선순위 적용
				FirstPriority(stuVector, max, grade, major, filename);
			}
		}

	}
	locale::global(locale::classic());
	cout << "모든 과목에 대한 수강신청 우선순위가 정해져 출석부 파일이 확정되었습니다." << endl;
}

//높은 마일리지 베팅한 학생 뽑기
void FirstPriority(vector<Student>& studentsWhoApplied, int& max, int& subGrade, wstring subMajor, wstring filename) {
	//cout << "1번째 우선순위 단계 도착" << endl;
	//cout << studentsWhoApplied.size() << "명 중 " << max << "명을 뽑아야 함" << endl << endl;
	vector<int> mileageVec;
	for (int i = 0; i < studentsWhoApplied.size(); i++) {
		mileageVec.push_back(studentsWhoApplied[i].GetMileage());
	}
	sort(mileageVec.begin(), mileageVec.end(), greater<int>());
	/*	mileageVec에 잘 들어가고 정렬되는지 확인
	for (int i = 0; i < mileageVec.size(); i++) {
		cout << mileageVec[i] << " ";
	}
	cout << endl;
	*/
	//locale::global(locale("ko_KR.UTF-8"));
	//PrintCandidateInfo(studentsWhoApplied);
	vector<Student> candidateVec;		//출석부에 적을 확정된 학생들 vector
	vector<Student> definiteVec;		//추가 우선순위 정해야 할 후보 학생들 vector
	if (mileageVec[(long long)(max - 1)] != mileageVec[max]) {
		//max까지만 출석부에 저장하고 끝 (mileageVec[max-1] 보다 크거나 같은 마일리지 가진 학생만 추가)
		for (int i = 0; i < studentsWhoApplied.size(); i++) {
			if (studentsWhoApplied[i].GetMileage() >= mileageVec[(long long)(max - 1)]) {
				definiteVec.push_back(studentsWhoApplied[i]);
			}
		}
		FinalizeAttendanceBook(definiteVec, filename, addEnd);
		return;
	}
	else {
		size_t remainMax;
		for (int i = 0; i < studentsWhoApplied.size(); i++) {
			if (studentsWhoApplied[i].GetMileage() > mileageVec[(long long)(max - 1)]) {
				definiteVec.push_back(studentsWhoApplied[i]);
			}
			else if (studentsWhoApplied[i].GetMileage() == mileageVec[(long long)(max - 1)]) {
				candidateVec.push_back(studentsWhoApplied[i]);
			}
		}
		if (definiteVec.size() > 0) {
			FinalizeAttendanceBook(definiteVec, filename, addEnd);
			addEnd = true;
		}
		//cout << "확정된 학생 수 : " << definiteVec.size() << endl;
		remainMax = max - definiteVec.size();
		if (subMajor.compare(L"교양") == 0) {
			FourthPriority(candidateVec, remainMax, filename);
		}
		else {
			SecondPriority(candidateVec, remainMax, subGrade, subMajor, filename);
			return;
		}
	}
}

//과목의 전공과 일치하는 전공을 가진 학생 뽑기
void SecondPriority(vector<Student>& candidate, size_t& remainMax, int& subGrade, wstring subMajor, wstring filename) {
	//locale::global(locale::classic());
	//cout << "2번째 우선순위 단계 도착" << endl;
	//cout << candidate.size() << "명 중 " << remainMax << "명을 더 뽑아야 함" << endl << endl;
	//locale::global(locale("ko_KR.UTF-8"));
	//wcout << L"이 과목의 전공 : " << subMajor << endl << endl;
	locale::global(locale("ko_KR.UTF-8"));
	wfstream f(L"사용자 데이터 파일.txt");
	if (!f.is_open()) {
		cout << "파일 열기 실패" << endl;
	}
	else {
		cout << "파일 열기 성공" << endl;
		vector<wstring> data;
		wstring line, str;
		wstringstream ss;
		int dataUpdateNum = 0;
		while (getline(f, line)) {
			if (dataUpdateNum == candidate.size()) {
				break;
			}
			locale::global(locale("ko_KR.UTF-8"));
			data.clear();
			ss.clear();
			line = trimFunc(line);
			ss.str(line);
			getline(ss, str, L'\t');
			str = trimFunc(str);
			//여기까지 했을 때 str은 학번(또는 교번)
			//교번인 0000으로 시작하는 것은 for문 들어가기전에 거르면 좋음 - 추후 추가
			for (int i = 0; i < candidate.size(); i++) {
				if (str.compare(candidate[i].GetStudentNum()) == 0) {
					getline(ss, str, L'\t');			//이름은 이미 갖고 있는 데이터라 건너뛰려고 한 번 읽음
					while (getline(ss, str, L'\t')) {	//data에 전공, 학년, 취득학점 들어감
						str = trimFunc(str);
						if (str != L"") {
							data.push_back(str);
						}
					}
					//data에 있는 전공, 학년, 취득학점을 학생 객체의 데이터로 넣어줌
					candidate[i].SetStudentMajor(data[0]);
					candidate[i].SetStudentGrade(stoi(data[1]));
					candidate[i].SetAchievedCredit(stoi(data[2]));
					dataUpdateNum++;
				}
			}
		}
		//locale::global(locale("ko_KR.UTF-8"));
		//PrintCandidateInfo(candidate);
		//cout << endl;
		vector<bool> majorCoincidence;
		int coincidenceNum = 0;
		for (int i = 0; i < candidate.size(); i++) {
			if (subMajor.compare(candidate[i].GetStudentMajor()) == 0) {
				majorCoincidence.push_back(true);
				coincidenceNum++;
			}
			else {
				majorCoincidence.push_back(false);
			}
		}
		//후보 중 전공 일치하는 학생 수와 출석부에 더 추가할 수 있는 remainMax비교해서 분기를 나눔
		vector<Student> newCandidate;
		vector<Student> definiteVec;
		if (coincidenceNum < remainMax) {
			//불일치 애들 새 후보 벡터에 넣고 세 번째 우선순위 적용
			for (int i = 0; i < majorCoincidence.size(); i++) {
				if (majorCoincidence[i] == false) {
					newCandidate.push_back(candidate[i]);
				}
				else {
					definiteVec.push_back(candidate[i]);
				}
			}
			if (definiteVec.size() > 0) {
				FinalizeAttendanceBook(definiteVec, filename, addEnd);
				addEnd = true;
			}
			// candidate.size() - newCandidate.size() 는 이 우선순위 단계에서 확정된 학생 수
			remainMax = remainMax - (candidate.size() - newCandidate.size());
			ThirdPriority(newCandidate, remainMax, subGrade, filename);
		}
		else if (coincidenceNum == remainMax) {
			for (int i = 0; i < majorCoincidence.size(); i++) {
				if (majorCoincidence[i] == true) {
					definiteVec.push_back(candidate[i]);
				}
			}
			FinalizeAttendanceBook(definiteVec, filename, addEnd);
			return;
		}
		else {
			for (int i = 0; i < majorCoincidence.size(); i++) {
				if (majorCoincidence[i] == true) {
					newCandidate.push_back(candidate[i]);
				}
			}
			ThirdPriority(newCandidate, remainMax, subGrade, filename);
		}
	}
}

//과목의 학년과 일치하는 학년을 가진 학생 뽑기
void ThirdPriority(vector<Student>& candidate, size_t& remainMax, int& subGrade, wstring filename) {
	//locale::global(locale::classic());
	//cout << "3번째 우선순위 단계 도착" << endl;
	//cout << candidate.size() << "명 중 " << remainMax << "명을 더 뽑아야 함" << endl << endl;
	//cout << "이 과목의 학년 : " << subGrade << endl << endl;
	//locale::global(locale("ko_KR.UTF-8"));
	//PrintCandidateInfo(candidate);
	//cout << endl << endl;
	vector<bool> gradeCoincidence;
	int coincidenceNum = 0;
	for (int i = 0; i < candidate.size(); i++) {
		if (subGrade == candidate[i].GetStudentGrade()) {
			gradeCoincidence.push_back(true);
			coincidenceNum++;
		}
		else {
			gradeCoincidence.push_back(false);
		}
	}
	//후보 중 학년 일치하는 학생 수와 출석부에 더 추가할 수 있는 remainMax비교해서 분기를 나눔
	vector<Student> newCandidate;
	vector<Student> definiteVec;
	if (coincidenceNum < remainMax) {
		//불일치 애들 후보에 넣고 네 번째 우선순위 적용
		for (int i = 0; i < gradeCoincidence.size(); i++) {
			if (gradeCoincidence[i] == false) {
				newCandidate.push_back(candidate[i]);
			}
			else {
				definiteVec.push_back(candidate[i]);
			}
		}
		if (definiteVec.size() > 0) {
			FinalizeAttendanceBook(definiteVec, filename, addEnd);
			addEnd = true;
		}
		// candidate.size() - newCandidate.size() 는 이 우선순위 단계에서 확정된 학생 수
		remainMax = remainMax - (candidate.size() - newCandidate.size());
		FourthPriority(newCandidate, remainMax, filename);
	}
	else if (coincidenceNum == remainMax) {
		//학년 일치하는 학생만 출석부 파일에 추가
		for (int i = 0; i < gradeCoincidence.size(); i++) {
			if (gradeCoincidence[i] == true) {
				definiteVec.push_back(candidate[i]);
			}
		}
		FinalizeAttendanceBook(definiteVec, filename, addEnd);
		return;
	}
	else {
		for (int i = 0; i < gradeCoincidence.size(); i++) {
			if (gradeCoincidence[i] == true) {
				newCandidate.push_back(candidate[i]);
			}
		}
		FourthPriority(newCandidate, remainMax, filename);
	}
}

//신청한 과목수가 적은 학생 뽑기
void FourthPriority(vector<Student>& candidate, size_t& remainMax, wstring filename) {
	//locale::global(locale::classic());
	//cout << "4번째 우선순위 단계 도착" << endl;
	//cout << candidate.size() << "명 중 " << remainMax << "명을 더 뽑아야 함" << endl << endl;
	//locale::global(locale("ko_KR.UTF-8"));
	//PrintCandidateInfo(candidate);
	//cout << endl << endl;
	int* appliedSubjectNum = new int[candidate.size()];
	//학생별로 신청과목 파일 열어서 신청과목수 얻어야 함
	for (int i = 0; i < candidate.size(); i++) {
		wstring filename = candidate[i].GetStudentNum() + L"_" + candidate[i].GetStudentName() + L"_수강신청목록.txt";
		wfstream f(filename);
		wstring line;		//빈 행 있는지 체크하는 코드 안 넣었음
		if (f.is_open()) {
			//cout << "파일 열림" << endl;
			int lineCount = 0;
			while (getline(f, line)) {
				locale::global(locale("ko_KR.UTF-8"));
				lineCount++;
			}
			f.close();
			*(appliedSubjectNum + i) = lineCount;		//lineCount가 행 수니깐 신청과목수가 됨
			candidate[i].SetAppliedSubjectNum(lineCount);
		}
	}
	sort(appliedSubjectNum, appliedSubjectNum + candidate.size());
	/*	오름차순으로 신청과목수 벡터 sorting되었는지 확인
	for (int i = 0; i < candidate.size(); i++) {
		cout << appliedSubjectNum[i] << " ";
	}
	cout << endl;
	*/
	vector<Student> newCandidate;
	vector<Student> definiteVec;
	if (appliedSubjectNum[remainMax - 1] != appliedSubjectNum[remainMax]) {
		//신청과목수가 appliedSubjectNum[remainMax-1] 보다 작거나 같은 학생들 출석부에 추가
		for (int i = 0; i < candidate.size(); i++) {
			if (candidate[i].GetAppliedSubjectNum() <= appliedSubjectNum[remainMax - 1]) {
				definiteVec.push_back(candidate[i]);
			}
		}
		delete[]appliedSubjectNum;
		FinalizeAttendanceBook(definiteVec, filename, addEnd);
		return;
	}
	else {
		for (int i = 0; i < candidate.size(); i++) {
			if (candidate[i].GetAppliedSubjectNum() < appliedSubjectNum[remainMax - 1]) {
				definiteVec.push_back(candidate[i]);
			}
			else if (candidate[i].GetAppliedSubjectNum() == appliedSubjectNum[remainMax - 1]) {
				newCandidate.push_back(candidate[i]);
			}
		}
		if (definiteVec.size() > 0) {
			FinalizeAttendanceBook(definiteVec, filename, addEnd);
			addEnd = true;
		}
		delete[]appliedSubjectNum;
		//definite vector에 들어간 학생들 출석부에 추가하는 코드

		remainMax = remainMax - definiteVec.size();
		FifthPriority(newCandidate, remainMax, filename);
	}
}

//취득학점이 적은 학생 뽑기
void FifthPriority(vector<Student>& candidate, size_t& remainMax, wstring filename) {
	//locale::global(locale::classic());
	//cout << "5번째 우선순위 단계 도착" << endl;
	//cout << candidate.size() << "명 중 " << remainMax << "명을 더 뽑아야 함" << endl << endl;
	//locale::global(locale("ko_KR.UTF-8"));
	//PrintCandidateInfo(candidate);
	//cout << endl << endl;
	vector<int> achievedCreditVec;
	for (int i = 0; i < candidate.size(); i++) {
		achievedCreditVec.push_back(candidate[i].GetAchievedCredit());
	}
	sort(achievedCreditVec.begin(), achievedCreditVec.end());
	/*	취득학점 오름차순으로 잘 정렬되었는지 확인
	for (int i = 0; i < achievedCreditVec.size(); i++) {
		cout << achievedCreditVec[i] << " ";
	}
	cout << endl;
	*/
	vector<Student> newCandidate;
	vector<Student> definiteVec;
	if (achievedCreditVec[remainMax - 1] != achievedCreditVec[remainMax]) {
		for (int i = 0; i < candidate.size(); i++) {
			if (candidate[i].GetAchievedCredit() <= achievedCreditVec[remainMax - 1]) {
				definiteVec.push_back(candidate[i]);
			}
		}
		FinalizeAttendanceBook(definiteVec, filename, addEnd);
		return;
	}
	else {
		for (int i = 0; i < candidate.size(); i++) {
			if (candidate[i].GetAchievedCredit() < achievedCreditVec[remainMax - 1]) {
				definiteVec.push_back(candidate[i]);
			}
			else if (candidate[i].GetAchievedCredit() == achievedCreditVec[remainMax - 1]) {
				newCandidate.push_back(candidate[i]);
			}
		}
		if (definiteVec.size() > 0) {
			FinalizeAttendanceBook(definiteVec, filename, addEnd);
		}
		remainMax = remainMax - definiteVec.size();
		SixthPriority(newCandidate, remainMax, filename);
	}
}

//먼저 과목을 추가한 학생 뽑기
void SixthPriority(vector<Student>& candidate, size_t& remainMax, wstring filename) {
	//locale::global(locale::classic());
	//cout << "6번째 우선순위 단계 도착" << endl;
	//cout << candidate.size() << "명 중 " << remainMax << "명을 더 뽑아야 함" << endl;
	//locale::global(locale("ko_KR.UTF-8"));
	//PrintCandidateInfo(candidate);
	//cout << endl << endl;
	vector<int> orderOfApply;
	for (int i = 0; i < candidate.size(); i++) {
		orderOfApply.push_back(candidate[i].GetStudentOrder());
	}
	sort(orderOfApply.begin(), orderOfApply.end());
	/*	오름차순으로 sorting 잘 되었는지 확인
	for (int i = 0; i < orderOfApply.size(); i++) {
		cout << orderOfApply[i] << " ";
	}
	cout << endl;
	*/
	vector<Student> definiteVec;
	for (int i = 0; i < candidate.size(); i++) {
		if (candidate[i].GetStudentOrder() <= orderOfApply[remainMax - 1]) {
			definiteVec.push_back(candidate[i]);
		}
	}
	FinalizeAttendanceBook(definiteVec, filename, addEnd);
	return;
}

void PrintCandidateInfo(vector<Student>& candidateVec) {
	for (int i = 0; i < candidateVec.size(); i++) {
		wcout << candidateVec[i].GetStudentNum() << L" " << candidateVec[i].GetStudentName() << L" " << candidateVec[i].GetStudentMajor() << endl;
	}
}

void FinalizeAttendanceBook(vector<Student>& v1, wstring filename, bool addEnd) {
	locale::global(locale("ko_KR.UTF-8"));

	int i;
	if (addEnd) {
		wfstream f(filename);
		f.seekg(0, ios::end);
		f << L"\n";
		for (i = 0; i < v1.size() - 1; i++) {
			f << v1[i].GetStudentNum() << L"\t" << v1[i].GetStudentName() << endl;
		}
		f << v1[i].GetStudentNum() << L"\t" << v1[i].GetStudentName();
		f.close();
	}
	else {
		wfstream f(filename, ios::out);
		if (f.is_open()) cout << "열림" << endl;
		for (i = 0; i < v1.size() - 1; i++) {
			f << v1[i].GetStudentNum() << L"\t" << v1[i].GetStudentName() << endl;
		}
		f << v1[i].GetStudentNum() << L"\t" << v1[i].GetStudentName();
		f.close();
	}

}

wstring& trimFunc(wstring& s, const wchar_t* t) {
	s.erase(0, s.find_first_not_of(t));
	s.erase(s.find_last_not_of(t) + 1);
	return s;
}

wstring stringTOwstring(string src) {
	USES_CONVERSION;
	return A2W(src.c_str());
}

/*
string wstringTOstring(wstring src) {
	USES_CONVERSION;
	return W2A(src.c_str());
}
*/
