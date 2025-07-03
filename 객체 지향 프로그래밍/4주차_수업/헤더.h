#pragma once
#include <iostream>

using namespace std;

#ifndef tower_h
#define tower_h
class Tower {
private:
	int height;
public:
	Tower();
	Tower(int h);
	double getHeight();
};
#endif