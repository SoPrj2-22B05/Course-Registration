#pragma once
#include "IntegrityCheck.h"
#include "SubjectData.h"

#include <iostream>
#include <string>

using namespace std;

int main() {
	Integrity_Check();
	cout << "================ ���� ������ �׽�Ʈ ��� ================" << endl;
	for (int i = 0; i < 10000; i++) {
		if (Subject[i] != NULL) {
			cout << Subject[i]->id << " ";
			cout << Subject[i]->name << " ";
			cout << Subject[i]->credit << " ";
			cout << Subject[i]->major << " ";
			cout << Subject[i]->grade << " ";
			cout << Subject[i]->time << " ";
			cout << Subject[i]->max << endl;
		}
	}
	return 0;
}