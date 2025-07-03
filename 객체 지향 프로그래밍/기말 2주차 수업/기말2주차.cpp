// CopyConstructor.cpp : This file contains the 'main' function. 
// Program execution begins and ends there.

//=========================================================
// Lecture Example 1
//=========================================================
#include <iostream>
using namespace std;

class Circle {
private:
	int radius;
public:
	Circle();
	Circle(int r);
	~Circle();
	double getArea() { return 3.14 * radius * radius; }
	int getRadius() { return radius; }
	void setRadius(int radius) { this->radius = radius; }
};
Circle::Circle() {
	radius = 1;
	cout << "Constructor: radius = " << radius << endl;
}
Circle::Circle(int radius) {
	this->radius = radius;
	cout << "Constructor: radius = " << radius << endl;
}

Circle::~Circle() {
	cout << "Destructor: radius = " << radius << endl;
}
void increase(Circle& c) {
	int r = c.getRadius();
	c.setRadius(r + 10);
	cout << "Increased Radius= " << c.getRadius() << endl;
}

int main() {
	Circle waffle(30);

	increase(waffle);

	return 0;
}

//=========================================================
// Lecture Example 2
//=========================================================
/*#include <iostream>
using namespace std;

class Complex { //Complex numbers: (a+bi), a, b는 실수.
public:
	double real, imag;
	Complex(double r = 0.0, double i = 0.0) : real{ r }, imag{ i } {
		cout << "Calling the Constructor";
		print();
	}
	~Complex() { cout << "Calling the Destructor"; print(); }
	void print() {
		cout << real << "+" << imag << "i" << endl;
	}
};
Complex add(Complex c1, Complex c2) {
	Complex temp;

	temp.real = c1.real + c2.real;
	temp.imag = c1.imag + c2.imag;

	return temp;
}
//Complex add(Complex& c1, Complex& c2) {
//	Complex temp;
//
//	temp.real = c1.real + c2.real;
//	temp.imag = c1.imag + c2.imag;
//
//	return temp;
//}

int main()
{
	Complex c1{ 1,2 }, c2{ 3,4 };
	Complex t;

	t = add(c1, c2);
	t.print();

	return 0;
}*/

//=========================================================
// Lecture Example 3
//=========================================================
//#include <iostream>
//using namespace std;
//
//class complex {
//public:
//	double real, imag;
//	complex(double r = 0.0, double i = 0.0) : real{ r }, imag{ i } {
//		cout << "calling the constructor";
//		print();
//	}
//	~complex() { cout << "calling the destructor"; print(); }
//	void print() {
//		cout << real << "+" << imag << "i" << endl;
//	}
//	complex(complex& c) {
//		real = c.real; imag = c.imag;
//		cout << "calling the copy constructor "; print();
//	}
//};
//
//complex add(complex c1, complex c2) {
//	complex temp;
//
//	temp.real = c1.real + c2.real;
//	temp.imag = c1.imag + c2.imag;
//
//	return temp;
//}
//
//int main()
//{
//	complex c1{ 1,2 }, c2{ 3,4 };
//	complex t;
//
//	t = add(c1, c2);
//	cout << "the result of addition: "; t.print();
//
//	return 0;
//}

//=========================================================
// Lecture Example 4
//=========================================================
/*#include <iostream>
using namespace std;

class person {
public:
	int age;
	person() : age{0} {}
	person(int a) : age{ a } {    }

	person(person& c) {
			age = c.age;
			cout << "calling the copy constructor \n";
	}
};

void update(person p) { p.age = p.age+5; }

int main() {
	person kim(21);
	cout << "check point 1" << endl;
	person clone{ kim }; // copying an object
	cout << "check point 2" << endl;
	person clone2;
	cout << "check point 3" << endl;
	update(clone);
	cout << "check point final" << endl;
	cout << "kim's age: " << kim.age << " clone's age: " << clone.age << endl;

	kim.age = 23;
	cout << "kim's age: " << kim.age << " clone's age: " << clone.age << endl;

	clone2 = clone;      // object substitution
	cout << "kim's age: " << kim.age << " clone2's age: " << clone.age << endl;

	return 0;
}*/

//=========================================================
// Assign vs. Copy
//=========================================================
/*#include <iostream>
using namespace std;

class Person {
public:
	int age;
	Person(int a) : age(a) {    }
	Person(Person& p) {
		age = p.age;
		cout << "calling the copy constructor \n";
	}
};

int main()
{
	Person obj1(20);
	cout << "Copying here" << endl;
	Person obj2(obj1);
	cout << obj1.age << " vs. " << obj2.age << endl;

	obj1.age = 30;
	cout << "Update the first age: " << obj1.age << endl;
	cout << obj1.age << " vs. " << obj2.age << endl;

	cout << "Assigning here" << endl;
	obj2 = obj1;
	cout << obj1.age << " vs. " << obj2.age << endl;

	return 0;
}*/

//=========================================================
// Proper Copy (Shallow vs Deep)
//=========================================================
/*#include <iostream>
#include <vector>
using namespace std;

class MyArray {
public:
	int size;
	int* data;
	MyArray(int size);
	MyArray(const MyArray& other);
	~MyArray();
};

MyArray::MyArray(int size)
{
	this->size = size;
	data = new int[size];
	for (int id = 0;id < size; id++) {
		data[id] = rand();
	}
}

MyArray::~MyArray() {
	if (data != nullptr) delete[] this->data;
	data = nullptr;
}

// Deep copy
/*MyArray::MyArray(const MyArray& other)
{
	this->size = other.size;
	this->data = new int[other.size];
	for (int i = 0; i < size; i++)
		this->data[i] = other.data[i];
}

// Shallow copy
MyArray::MyArray(const MyArray& other)
{
	this->size = other.size;
	this->data = other.data;
}

int main() {
	MyArray buffer1(10);
	MyArray buffer2(buffer1);

	cout << buffer1.data << endl;
	cout << buffer2.data << endl << endl;

	return 0;
}*/

//=========================================================
// Static vs Non-static (Instance)
//=========================================================
/*#include <iostream>
#include <vector>
using namespace std;

class Person {
public:
	double privateMoney;
	void addPrivate(int money) {
		this->privateMoney += money;
	}
	static int sharedMoney;
	static void addShared(int n) {
		sharedMoney += n;
	}
};

int Person::sharedMoney = 10;

int main() {
	Person::addShared(50);
	cout << Person::sharedMoney << endl;

	Person han;
	cout << han.sharedMoney << endl;

	han.privateMoney = 100;
	han.addPrivate(200);
	han.sharedMoney = 200;
	cout << "han's money: " << han.privateMoney << ' ' << han.sharedMoney << endl;
	cout << "Class's money: " << Person::sharedMoney << endl;

	Person::sharedMoney = 300;
	cout << "Shared: " << han.sharedMoney << ' ' << Person::sharedMoney << endl;

	Person::addShared(100);
	cout << "Shared: " << han.sharedMoney << ' ' << Person::sharedMoney << endl;
}

*/

#include <iostream>

class Camera {
public:
	// Singleton 객체를 얻기 위한 정적 메서드
	static Camera& getInstance() {
		static Camera instance; // 정적 객체, 프로그램 종료 시까지 하나만 존재
		return instance;
	}

	// Camera 클래스의 기능 메서드
	void capture() {
		std::cout << "Capturing image..." << std::endl;
	}

	void adjustFocus(int level) {
		std::cout << "Adjusting focus to level: " << level << std::endl;
	}

private:
	// 생성자, 복사 생성자 및 대입 연산자를 private으로 제한하여 외부에서 인스턴스 생성을 막음
	Camera() {
		std::cout << "Camera initialized." << std::endl;
	}
	~Camera() {}

	// 복사 생성자와 대입 연산자 삭제
	Camera(const Camera&) = delete;
	Camera& operator=(const Camera&) = delete;
};

int main() {
	// Singleton 인스턴스 호출
	Camera& cam1 = Camera::getInstance();
	cam1.capture();
	cam1.adjustFocus(5);

	// 두 번째 호출은 동일한 인스턴스를 반환
	Camera& cam2 = Camera::getInstance();
	cam2.adjustFocus(10);

	return 0;	//static 함수 사용 예시
	//기존 객체 주소를 계속 return 함
}
