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

//�⺻������ "Course_Registration_On_Off.txt" ������ �����ؾ� ��
//������ �ҹ��ڷ� �ٲ��� �� on �Ǵ� off �� �� �ִ� ������ (on On oN ON off OFF oFf ���)
/*
�׽�Ʈ�� ���� �Ʒ� ������ ����� ������ ����.txt�� ����
202012345	�츮�����ѵ�	����ǰ������а�	2   	58
000012345	����������
202098124	���ι��Ǵ���	�׽�Ʈ�а�			2  	200
202018239	��ó�����θ�	�׽�Ʈ�а�  			2  	132
202067890	   �۰�		�׽�Ʈ�а�	  		2  	132
202083249	  ������   		�ǻ�������а�		3   	 85
201911260	  ��ö��		��ǻ�Ͱ��а�		2	60
000067890	  ���ڰ�
*/

/*
�׽�Ʈ�� ���� �Ʒ� ������ 0000_������_�⼮��.txt�� ����
202012345	�츮�����ѵ�	30
202067890	�۰�			28
201911260	��ö��		30
202098124	���ι��Ǵ���	28
202018239	��ó�����θ�	28
202083249	������		14
*/

/*
�׽�Ʈ�� ���� �Ʒ� ������ "202018239_��ó�����θ�_������û���.txt"�� ���� (�翬�� ���� �����ص� ��)
0000	28
3867	14
8751	30
�Ʒ� ������ "202067890_�۰�_������û���.txt"�� ���� (�翬�� ���� �����ص� ��)
0000	28
7777	17
6666	16
�Ʒ� ������ "202098124_���ι��Ǵ���_������û���.txt"�� ���� (�翬�� ���� �����ص� ��)
0000	28
9143	18
*/
void Administrator_menu() {
	string adminCommand;
tryAgain:
	cout << "Course Registration > ";
	cin >> adminCommand;
	if ((adminCommand.compare("�α׾ƿ�") == 0) || (adminCommand.compare("logout") == 0)) {
		return;
	}
	else if ((adminCommand.compare("����") == 0) || (adminCommand.compare("start") == 0)) {
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
					if (filename.compare(L"_�⼮��.txt") == 0) {
						fs::path p(entry.path());
						fs::remove(p);
					}
				}
				itr1++;
			}
		}
		goto tryAgain;
	}
	else if ((adminCommand.compare("����") == 0) || (adminCommand.compare("end") == 0)) {
		bool isEnd = false;
		isEnd = StartOrEnd(END);
		if (isEnd) {
			Prioritizing();
		}

		//������ �� ���� ����
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
				if (filename.compare(L"_������û���.txt") == 0) {
					fs::path p(entry.path());
					fs::remove(p);
				}
			}
			itr2++;
		}
		// ��ü ���α׷��� ����
		exit(0);
	}
	else {
		cout << "------------------------------------------------------------------" << endl;
		cout << "��ɾ\t" << "| ����" << endl;
		cout << "------------------------------------------------------------------" << endl;
		cout << "logout\t�α׾ƿ�" << "| �α׾ƿ��ϰ� ����� ���� �Է� ������Ʈ�� ���ư�" << endl;
		cout << "start\t  ����\t" << "| ������û �Ⱓ ������ �ǹ�" << endl;
		cout << "end\t  ����\t" << "| ������û �Ⱓ ���Ḧ �ǹ�" << endl;
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
			//������ �����ϰ� ������û �����Ѵٰ� ���
			isOn.close();
			wofstream out(dir + L"\\Course_Registration_Is_On.txt");
			out.close();
			cout << "������û�� �����մϴ�." << endl;
			return true;
		}
		else if (command == END) {
			cout << "���� ������û�� ���۵��� �ʾҽ��ϴ�." << endl;
		}
	}
	else {
		if (command == START) {
			cout << "�̹� ������û�� ���۵Ǿ� ������ �� �����ϴ�." << endl;
		}
		else if (command == END) {
			isOn.close();
			fs::path p(dir + L"\\Course_Registration_Is_On.txt");
			fs::remove(p);
			cout << "������û�� �����մϴ�." << endl;
			return true;
		}
		/*
		else {
			cout << "Course_Registration_On_Off.txt�� ������ �ʴ� ���ڿ��� �ԷµǾ��ֽ��ϴ�." << endl;
		}
		*/
	}
	isOn.close();
	return false;
}

void Prioritizing() { //�켱���� ���ϴ� �Լ�
	for (int i = 0; i < 10000; i++) {	//�����ȣ 0000���� 9999����
		addEnd = false;
		wstring subjectID, subjectName, major;
		int grade, max;
		if (Subject[i] == NULL) continue;	//�ش� �����ȣ�� ������ ���� ������ �ǳʶ�
		else {								//���� �̸�, �г�, ������ ������ ��
			locale::global(locale("ko_KR.UTF-8"));
			subjectID = stringTOwstring(Subject[i]->id);
			subjectName = stringTOwstring(Subject[i]->name);
			major = stringTOwstring(Subject[i]->major);
			grade = Subject[i]->grade;
			max = Subject[i]->max;
		}
		//	Subject�ȿ� ������ ��ä���� ���·� �׽�Ʈ�ϱ� ���� ������ (�ٷ� �� if,else��� �ּ�ó���ϰ� �̰� �ּ�����)
		/*
		subjectID = L"0000";
		subjectName = L"������";
		major = L"�׽�Ʈ�а�";
		grade = 2;
		max = 4;
		*/
		locale::global(locale("ko_KR.UTF-8"));
		wstring filename = subjectID + L"_" + subjectName + L"_�⼮��.txt";
		wfstream f(filename);

		vector<Student> stuVector;
		vector<wstring> data;
		wstring line, str;
		wstringstream ss;
		if (f.is_open()) {
			int lineCount = 0;		//lineNumber�μ�, �л� ��ü�� order�� �� 6��° �켱�������� Ȱ���
			while (getline(f, line)) {
				locale::global(locale("ko_KR.UTF-8"));
				lineCount++;
				data.clear();
				ss.clear();
				// ����ִ� ������ üũ
				line = trimFunc(line);
				if (line.compare(L"") == 0) {
					cout << "�⼮�� ���Ͽ� �� ���� ����" << endl;
					continue;
				}
				//data��� vector�� wstring���·� �й�, �̸�, ���ϸ��� ����
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
				//cout << "���� ���Ϸ� ��û��" << endl;
				//�⼮�� ���Ͽ� ���ϸ��� �����ϰ� "�й�\t�̸�"�� ���� !!!!!!!!!!!
				FinalizeAttendanceBook(stuVector, filename, addEnd);
				continue;	//���� ��������
			}
			else {
				//cout << "���� �ʰ��Ͽ� ��û��" << endl << endl;
				//ù ��° �켱���� ����
				FirstPriority(stuVector, max, grade, major, filename);
			}
		}

	}
	locale::global(locale::classic());
	cout << "��� ���� ���� ������û �켱������ ������ �⼮�� ������ Ȯ���Ǿ����ϴ�." << endl;
}

//���� ���ϸ��� ������ �л� �̱�
void FirstPriority(vector<Student>& studentsWhoApplied, int& max, int& subGrade, wstring subMajor, wstring filename) {
	//cout << "1��° �켱���� �ܰ� ����" << endl;
	//cout << studentsWhoApplied.size() << "�� �� " << max << "���� �̾ƾ� ��" << endl << endl;
	vector<int> mileageVec;
	for (int i = 0; i < studentsWhoApplied.size(); i++) {
		mileageVec.push_back(studentsWhoApplied[i].GetMileage());
	}
	sort(mileageVec.begin(), mileageVec.end(), greater<int>());
	/*	mileageVec�� �� ���� ���ĵǴ��� Ȯ��
	for (int i = 0; i < mileageVec.size(); i++) {
		cout << mileageVec[i] << " ";
	}
	cout << endl;
	*/
	//locale::global(locale("ko_KR.UTF-8"));
	//PrintCandidateInfo(studentsWhoApplied);
	vector<Student> candidateVec;		//�⼮�ο� ���� Ȯ���� �л��� vector
	vector<Student> definiteVec;		//�߰� �켱���� ���ؾ� �� �ĺ� �л��� vector
	if (mileageVec[(long long)(max - 1)] != mileageVec[max]) {
		//max������ �⼮�ο� �����ϰ� �� (mileageVec[max-1] ���� ũ�ų� ���� ���ϸ��� ���� �л��� �߰�)
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
		//cout << "Ȯ���� �л� �� : " << definiteVec.size() << endl;
		remainMax = max - definiteVec.size();
		if (subMajor.compare(L"����") == 0) {
			FourthPriority(candidateVec, remainMax, filename);
		}
		else {
			SecondPriority(candidateVec, remainMax, subGrade, subMajor, filename);
			return;
		}
	}
}

//������ ������ ��ġ�ϴ� ������ ���� �л� �̱�
void SecondPriority(vector<Student>& candidate, size_t& remainMax, int& subGrade, wstring subMajor, wstring filename) {
	//locale::global(locale::classic());
	//cout << "2��° �켱���� �ܰ� ����" << endl;
	//cout << candidate.size() << "�� �� " << remainMax << "���� �� �̾ƾ� ��" << endl << endl;
	//locale::global(locale("ko_KR.UTF-8"));
	//wcout << L"�� ������ ���� : " << subMajor << endl << endl;
	locale::global(locale("ko_KR.UTF-8"));
	wfstream f(L"����� ������ ����.txt");
	if (!f.is_open()) {
		cout << "���� ���� ����" << endl;
	}
	else {
		cout << "���� ���� ����" << endl;
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
			//������� ���� �� str�� �й�(�Ǵ� ����)
			//������ 0000���� �����ϴ� ���� for�� �������� �Ÿ��� ���� - ���� �߰�
			for (int i = 0; i < candidate.size(); i++) {
				if (str.compare(candidate[i].GetStudentNum()) == 0) {
					getline(ss, str, L'\t');			//�̸��� �̹� ���� �ִ� �����Ͷ� �ǳʶٷ��� �� �� ����
					while (getline(ss, str, L'\t')) {	//data�� ����, �г�, ������� ��
						str = trimFunc(str);
						if (str != L"") {
							data.push_back(str);
						}
					}
					//data�� �ִ� ����, �г�, ��������� �л� ��ü�� �����ͷ� �־���
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
		//�ĺ� �� ���� ��ġ�ϴ� �л� ���� �⼮�ο� �� �߰��� �� �ִ� remainMax���ؼ� �б⸦ ����
		vector<Student> newCandidate;
		vector<Student> definiteVec;
		if (coincidenceNum < remainMax) {
			//����ġ �ֵ� �� �ĺ� ���Ϳ� �ְ� �� ��° �켱���� ����
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
			// candidate.size() - newCandidate.size() �� �� �켱���� �ܰ迡�� Ȯ���� �л� ��
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

//������ �г�� ��ġ�ϴ� �г��� ���� �л� �̱�
void ThirdPriority(vector<Student>& candidate, size_t& remainMax, int& subGrade, wstring filename) {
	//locale::global(locale::classic());
	//cout << "3��° �켱���� �ܰ� ����" << endl;
	//cout << candidate.size() << "�� �� " << remainMax << "���� �� �̾ƾ� ��" << endl << endl;
	//cout << "�� ������ �г� : " << subGrade << endl << endl;
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
	//�ĺ� �� �г� ��ġ�ϴ� �л� ���� �⼮�ο� �� �߰��� �� �ִ� remainMax���ؼ� �б⸦ ����
	vector<Student> newCandidate;
	vector<Student> definiteVec;
	if (coincidenceNum < remainMax) {
		//����ġ �ֵ� �ĺ��� �ְ� �� ��° �켱���� ����
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
		// candidate.size() - newCandidate.size() �� �� �켱���� �ܰ迡�� Ȯ���� �л� ��
		remainMax = remainMax - (candidate.size() - newCandidate.size());
		FourthPriority(newCandidate, remainMax, filename);
	}
	else if (coincidenceNum == remainMax) {
		//�г� ��ġ�ϴ� �л��� �⼮�� ���Ͽ� �߰�
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

//��û�� ������� ���� �л� �̱�
void FourthPriority(vector<Student>& candidate, size_t& remainMax, wstring filename) {
	//locale::global(locale::classic());
	//cout << "4��° �켱���� �ܰ� ����" << endl;
	//cout << candidate.size() << "�� �� " << remainMax << "���� �� �̾ƾ� ��" << endl << endl;
	//locale::global(locale("ko_KR.UTF-8"));
	//PrintCandidateInfo(candidate);
	//cout << endl << endl;
	int* appliedSubjectNum = new int[candidate.size()];
	//�л����� ��û���� ���� ��� ��û����� ���� ��
	for (int i = 0; i < candidate.size(); i++) {
		wstring filename = candidate[i].GetStudentNum() + L"_" + candidate[i].GetStudentName() + L"_������û���.txt";
		wfstream f(filename);
		wstring line;		//�� �� �ִ��� üũ�ϴ� �ڵ� �� �־���
		if (f.is_open()) {
			//cout << "���� ����" << endl;
			int lineCount = 0;
			while (getline(f, line)) {
				locale::global(locale("ko_KR.UTF-8"));
				lineCount++;
			}
			f.close();
			*(appliedSubjectNum + i) = lineCount;		//lineCount�� �� ���ϱ� ��û������� ��
			candidate[i].SetAppliedSubjectNum(lineCount);
		}
	}
	sort(appliedSubjectNum, appliedSubjectNum + candidate.size());
	/*	������������ ��û����� ���� sorting�Ǿ����� Ȯ��
	for (int i = 0; i < candidate.size(); i++) {
		cout << appliedSubjectNum[i] << " ";
	}
	cout << endl;
	*/
	vector<Student> newCandidate;
	vector<Student> definiteVec;
	if (appliedSubjectNum[remainMax - 1] != appliedSubjectNum[remainMax]) {
		//��û������� appliedSubjectNum[remainMax-1] ���� �۰ų� ���� �л��� �⼮�ο� �߰�
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
		//definite vector�� �� �л��� �⼮�ο� �߰��ϴ� �ڵ�

		remainMax = remainMax - definiteVec.size();
		FifthPriority(newCandidate, remainMax, filename);
	}
}

//��������� ���� �л� �̱�
void FifthPriority(vector<Student>& candidate, size_t& remainMax, wstring filename) {
	//locale::global(locale::classic());
	//cout << "5��° �켱���� �ܰ� ����" << endl;
	//cout << candidate.size() << "�� �� " << remainMax << "���� �� �̾ƾ� ��" << endl << endl;
	//locale::global(locale("ko_KR.UTF-8"));
	//PrintCandidateInfo(candidate);
	//cout << endl << endl;
	vector<int> achievedCreditVec;
	for (int i = 0; i < candidate.size(); i++) {
		achievedCreditVec.push_back(candidate[i].GetAchievedCredit());
	}
	sort(achievedCreditVec.begin(), achievedCreditVec.end());
	/*	������� ������������ �� ���ĵǾ����� Ȯ��
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

//���� ������ �߰��� �л� �̱�
void SixthPriority(vector<Student>& candidate, size_t& remainMax, wstring filename) {
	//locale::global(locale::classic());
	//cout << "6��° �켱���� �ܰ� ����" << endl;
	//cout << candidate.size() << "�� �� " << remainMax << "���� �� �̾ƾ� ��" << endl;
	//locale::global(locale("ko_KR.UTF-8"));
	//PrintCandidateInfo(candidate);
	//cout << endl << endl;
	vector<int> orderOfApply;
	for (int i = 0; i < candidate.size(); i++) {
		orderOfApply.push_back(candidate[i].GetStudentOrder());
	}
	sort(orderOfApply.begin(), orderOfApply.end());
	/*	������������ sorting �� �Ǿ����� Ȯ��
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
		if (f.is_open()) cout << "����" << endl;
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
