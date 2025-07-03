// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.

//=========================================================
// Upcasting vs. Downcasting (What is wrong with the age?)
//=========================================================
#include <iostream>
#include <string>
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

using namespace std;

//class Animal {
//public:
//    int age;
//    // Virtual 쓰는 이유: virtual 쓰지 않을 시 dog, cat speak가 animal것으로 실행됨
//    // 다만 age = 0 은 그대로 내려옴(에러) ; age는 자식 멤버에 접근 x
//        virtual void speak() { cout << "To be implemented... "; }
//    virtual ~Animal() = default;
//};
//
//class Dog : public Animal {
//public:
//    int age = 1;
//    void speak() override { cout << "Woof woof "; }
//};
//
//class Cat : public Animal {
//public:
//    int age = 1;
//    void speak() override { cout << "Meow meow "; }
//};
//
//void clearLine() {
//    std::cout << "\033[2K\r";
//    std::cout.flush();
//}
//
//int main() {
//    cout << "=====Upcasting Example=====" << endl;
//    Animal* pAD = new Dog();
//    Animal* pAC = new Cat();
//    cout << "Dog and Cat objects are upcasted to be referenced by the Animal pointer." << endl;
//    cout << "pAD->speak(): "; pAD->speak(); cout << " pAD->age: " << pAD->age << endl;
//    cout << "pAC->speak(): "; pAC->speak(); cout << " pAC->age: " << pAC->age << "              ";
//    system("pause");
//    cout << endl;
//
//    cout << "Is Dog* pD = new Dog() an only solution?" << endl;
//    // new : dynamic memory 
//    Dog* pD = new Dog();
//    Cat* pC = new Cat();
//    cout << "pD->speak(): "; pD->speak(); cout << " pD->age: " << pD->age << endl;
//    cout << "pC->speak(): "; pC->speak(); cout << " pC->age: " << pC->age << "              ";
//    system("pause");
//    cout << endl;
//    cout << "Shouldn't there be any way to use pAD (or pAC) to access Dog's members if necessary?              ";
//    system("pause");
//    cout << endl;
//
//    //===== Downcasting Example =====
//    cout << "Downcasting is a solution to this issue" << endl;
//    cout << "Dog* pDdown1 = dynamic_cast<Dog*>(pAD);" << endl;
//    cout << "pDdown1->age & pDdown1->speak(): " << endl;
//    // 부모(업캐스팅) 속성을 가지고 있을 때, 자식 속성을 가지려고 할 때
//    // 다운캐스팅
//    // Dog* pDdown1 = (Dog*) pAD; 도 가능
//    Dog* pDdown1 = dynamic_cast<Dog*>(pAD);
//    if (pDdown1) {
//        cout << pDdown1->age << " & "; pDdown1->speak();
//        cout << "\npAD is transformed into pDdown1 correctly              ";
//    }
//    else {
//        cout << "Unable to downcast pAD to Dog*" << endl;
//    }
//    system("pause");
//    cout << endl;
//
//    //===== Wrong Downcasting Example =====
//    cout << "What if a regular base pointer, Animal* pAA = new Animal(), is mistakenly treated as an upcasted pointer like pAD as below?" << endl;
//    cout << "Dog* pDdown2 = dynamic_cast<Dog*>(pAA);" << endl;
//    // 이게 언제 문제가 생길까?
//    // 애초에 업캐스팅이 적용되지 않았던 객체는 다운캐스팅이 안된다.
//    cout << "What would be the consequence of this seemingly minor mistake?              ";
//    system("pause");
//    cout << "Here is what happens!" << endl;
//    // 
//    for (int ct = 1; ct <= 3; ct++) {
//        clearLine();
//        Sleep(125);
//        cout << "......";
//        Sleep(375);
//    }
//    cout << endl;
//    Animal* pAA = new Animal();
//    Dog* pDdown2 = dynamic_cast<Dog*>(pAA);
//    if (pDdown2) {
//        cout << "pDdown2->age: " << pDdown2->age << " & pDdown2->speak(): "; pDdown2->speak();
//    }
//    else {
//        cout << "Warning: Attempted downcast of pAA to Dog* failed. pAA is not actually a Dog instance." << endl;
//    }
//    cout << endl;
//    cout << "pAA could not be safely transformed into pDdown2, which prevented unintended behavior.              ";
//    system("pause");
//    cout << endl;
//    Sleep(3);
//
//    cout << "How could this potential error be prevented?" << endl;
//    Sleep(1);
//    cout << "   You have 5 seconds to come up with the answer!" << endl;
//    cout << to_string(0);
//    for (int ct = 1; ct <= 5; ct++) {
//        Sleep(1500); clearLine(); cout << to_string(ct);
//    }
//    clearLine();
//    cout << endl;
//    cout << "Dynamic Casting is the way to go!!!              ";
//    system("pause");
//    cout << endl;
//
//    cout << endl;
//    string message2 = "To implement the dynamic casting to catch the error of the inappropriate downcasting!\n\n";
//    for (int i = 0; i != message2.size(); ++i) {
//        cout << message2[i];
//        Sleep(25);
//    }
//
//    // Corrected dynamic casting (modified as per your image)
//    // DYNAMIC CAST는 virtual(가상함수) 일 때에만 사용
//    Dog* pDynamic = dynamic_cast<Dog*>(pAA);  // dynamic_cast 사용
//    if (pDynamic) {
//        pDynamic->speak();
//    }
//    else {
//        cout << "Error" << endl;  // 오류 대신 "Error" 출력
//    }
//
//    return 0;
//}


//=========================================================
// Inheritance Example
//=========================================================
#include <iostream>
#include <string>
#include <windows.h>
#include <ctime>

using namespace std;

class Shape {
protected:
	int x, y;
public:	
	Shape(int x, int y) : x(x), y(y) {	}
	virtual void draw() {
		cout << "Shape Draw" << endl;
	}
};

class Rect : public Shape {
private:
	int width, height;
public:
	Rect(int x, int y, int w, int h) : Shape(x, y), width(w), height(h) {	}
	virtual void draw() {
		HDC hdc = GetWindowDC(GetForegroundWindow());
		Rectangle(hdc, x, y, x + width, y + height);
		ReleaseDC(GetForegroundWindow(), hdc);
	}
};

class Circle : public Shape {
private:
	int radius;
public:
	Circle(int x, int y, int r) : Shape(x, y), radius(r) {   }
	virtual void draw() {
		HDC hdc = GetWindowDC(GetForegroundWindow());
		Ellipse(hdc, x - radius, y - radius, x + radius, y + radius);
		ReleaseDC(GetForegroundWindow(), hdc);
	}
};

int main() {
	srand(time(NULL));

	const int noShapes = 10;
	Shape* shapes[noShapes];

	for (int i = 0; i < noShapes; i++) {
		int a = rand()%2;
		if (a) {
			shapes[i] = new Rect(rand() % 600, rand() % 300 + 50, rand() % 50, rand() % 50);
		}
		else {
			shapes[i] = new Circle(rand() % 600, rand() % 300 + 50, rand() % 50);
		}
	
	}

	for (int i = 0; i < noShapes; i++) {
		shapes[i]->draw();
	}

	/*for (auto& e : shapes) {
		e->draw();
	}*/

	return 0;
}