#include <iostream>
#include <string>
using namespace std;

int main() {
	bool status=true;
	char ch;
	int notrials=0;

	string solution;
	string list[] = {"psychiatry","epistemology","astronomy","astrology","anthropology","cartography"};

	srand(time(NULL));
	int n = rand() % (sizeof(list)/sizeof(list[0]));
	//위에 n 원리 엄청 중요
	/*
	* 이대로만 진행하면 계속해서 똑같은 단어가 첫번째 문제로 선택이 됨
	* why? seed 값 설정 x
	* 
	* how to solve?
	* srand(time(NULL));
	* 
	*/
	solution = list[n];
    int noletters = solution.length();
	char initialsymbol = '_';
	string guess(noletters,initialsymbol);
	cout << "guess the name of an uncommon field of study\n";

	do {
		cout << guess << endl<<endl;
		cout << "enter a letter: ";
		cin >> ch; 
		notrials++;
		for (int i = 0;i < solution.length();i++) {
			if (ch==solution[i]) {
				guess[i] = ch;
			}
			if (solution == guess) {
				cout << solution << endl;
				cout << "success!";
				status = false;
				break;
			}
		}
	} while (status);
	cout << "you have tried " << notrials << " times!\n";
	return 0;
}