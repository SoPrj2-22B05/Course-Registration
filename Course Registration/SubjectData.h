#pragma once
#include <string>

using std::string;

struct SubjectData {
	string id;
	string name;
	int credit;
	string major;
	int grade;
	string time;
	int max;
};

extern SubjectData* Subject[10000];