#ifndef die_h
#define die_h

#include <iostream>

using namespace std;

class die {
private:
	int face;
public:
	die();
	void roll();
	double getFace();
};

#endif