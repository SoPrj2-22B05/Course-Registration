#pragma once
#include <iostream>
#include <string>
using namespace std;
class Student {
private:
	wstring studentNum;
	wstring studentName;
	wstring studentMajor;
	int achievedCredit;
	int grade;
	int mileage;
	int order;
	int appliedSubjectNum;
public:
	Student(wstring studentNum, wstring name, int mileage, int order) {
		this->studentNum = studentNum;
		this->studentName = name;
		this->mileage = mileage;
		this->order = order;
		studentMajor = L"ÇÐºÎ";
		grade = 1;
		achievedCredit = 0;
		appliedSubjectNum = 0;
	}
	void PrintStudentInfo() {
		wcout << studentNum << L" " << studentName << L" " << mileage << L" " << order << endl;
	}
	int GetMileage() {
		return this->mileage;
	}
	wstring GetStudentNum() {
		return this->studentNum;
	}
	wstring GetStudentName() {
		return this->studentName;
	}
	wstring GetStudentMajor() {
		return this->studentMajor;
	}
	int GetStudentGrade() {
		return this->grade;
	}
	int GetAchievedCredit() {
		return this->achievedCredit;
	}
	int GetAppliedSubjectNum() {
		return this->appliedSubjectNum;
	}
	int GetStudentOrder() {
		return this->order;
	}
	void SetStudentMajor(wstring major) {
		studentMajor = major;
	}
	void SetStudentGrade(int grade) {
		this->grade = grade;
	}
	void SetAchievedCredit(int credit) {
		achievedCredit = credit;
	}
	void SetAppliedSubjectNum(int num) {
		appliedSubjectNum = num;
	}
};