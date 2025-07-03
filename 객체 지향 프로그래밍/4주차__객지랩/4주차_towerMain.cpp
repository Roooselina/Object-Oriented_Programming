//===================================================
// Lab Page 1
//===================================================

#include <iostream>
#include "tower.h"

using namespace std;

// 구조체 정의
Tower::Tower() {
	height = 75;
	cout << "Height = " << height << endl;
}

Tower::Tower(int h) {
	height = h;
	cout << "Height = " << height << endl;
}

// 함수 정의
int Tower::getHeight() {
	return height;
}

void Tower::setHeight(int h) {
	height = h;
}

int main() {
	Tower myTower;
	Tower seoulTower(100);

	myTower.setHeight(myTower.getHeight() * 2);

	cout << "My tower's height is " << myTower.getHeight() << " meters" << endl;
	cout << "Seoul Tower's height is " << seoulTower.getHeight() << " meters" << endl;

	return 0;
}