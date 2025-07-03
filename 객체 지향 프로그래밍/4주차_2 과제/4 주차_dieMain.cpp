//===================================================
// Lab Page 2
//===================================================

#include <iostream>
#include "die.h"
#include "mathFunc.h"

using namespace std;

die::die() {
	face = rand() % 6 + 1;
	cout << "the face value = " << face << endl;
}

void die::roll() {
	face = rand() % 6 + 1;
}

double die::getFace() {
	return face;
}


 mathFunc::mathFunc(int n, int r){
	 epoch = n;
	 val = r;
}

long mathFunc:: nCr() {
	return fact(epoch) / (fact(val) * fact(epoch - val)); // nCr = n!/(r!(n-r)!)
}
long mathFunc::fact(int n){
	if (epoch == 0)
		return 1;
	long res = 1;
	for (int i = 2; i <= n; i++) {
		res = res * i;
	}
	return res;
}

int main() {
    const int noTrials = 100000;
    srand(time(NULL));
    die myDie1, myDie2;
    int targetValue;
    double totalCount;

    // Case 1: 12가 나오는 실험적 확률
    targetValue = 3;
    totalCount = 0;
    for (int i = 0; i < noTrials; i++) {
        myDie1.roll();
        myDie2.roll();
        if (myDie1.getFace() + myDie2.getFace() == targetValue) {
            totalCount++;
        }
    }
    cout << "12가 나오는 실험적 확률: " << 100 * totalCount / noTrials << "%" << endl;

    // Case 2: 7이 나오는 실험적 확률
    targetValue = 3;
    totalCount = 0;
    for (int i = 0; i < noTrials; i++) {
        myDie1.roll();
        myDie2.roll();
        if (myDie1.getFace() + myDie2.getFace() == targetValue) {
            totalCount++;
        }
    }
    cout << "7이 나오는 실험적 확률: " << 100 * totalCount / noTrials << "%" << endl;

    // CHALLENGE: 7이 나오는 수학적 확률 계산
    int possibleNum = 0;
    cout << "계산할 숫자 = " << targetValue << endl;

    for (int i = 1; i <= 6; i++) {
        for (int j = 1; j <= 6; j++) {
            if (i + j == targetValue) {
                possibleNum++;
            }
        }
    }

    cout << "수학적 확률: " << (double)possibleNum / 36.0 * 100 << "%" << endl;

    return 0;
}