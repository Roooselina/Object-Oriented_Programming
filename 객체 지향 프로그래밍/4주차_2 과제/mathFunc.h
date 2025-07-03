#ifndef mathFunc_h
#define mathFunc_h

#include <iostream>
using namespace std;

class mathFunc {
private:
	int epoch;
	int val;
public:
	mathFunc(int n, int r);
	long nCr();
	long fact(int n);
};
#endif