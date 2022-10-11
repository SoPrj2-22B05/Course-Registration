#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <locale.h>
#include <vector>
#include <algorithm>
#include <atlconv.h>
#include "AttendanceStudentData.h"
using namespace std;

void Administrator_menu();
bool StartOrEnd(int command);
void Prioritizing();
void FirstPriority(vector<Student>& v1, int& max, int& subGrade, wstring subMajor, wstring filename);
void SecondPriority(vector<Student>& candidate, size_t& remainMax, int& subGrade, wstring subMajor, wstring filename);
void ThirdPriority(vector<Student>& candidate, size_t& remainMax, int& subGrade, wstring filename);
void FourthPriority(vector<Student>& candidate, size_t& remainMax, wstring filename);
void FifthPriority(vector<Student>& candidate, size_t& remainMax, wstring filename);
void SixthPriority(vector<Student>& candidate, size_t& remainMax, wstring filename);
void PrintCandidateInfo(vector<Student>& candidateVec);
void FinalizeAttendanceBook(vector<Student>& v1, wstring filename, bool addEnd);