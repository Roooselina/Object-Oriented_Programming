////=========================================================
//// Introductory Example (Partial DIY)
////=========================================================
//#include <iostream>
//using namespace std;
//
//class Point
//{
//    int x, y;
//public:
//    void set(int x, int y)
//    {
//        this->x = x;
//        this->y = y;
//    }
//    void showPoint()
//    {
//        cout << "(" << x << "," << y << ")" << endl;
//    }
//};
//class ColorPoint : public Point {
//    string color;
//public:
//    void setColor(string color)
//    {
//        this->color = color;
//    }
//    void showColorPoint()
//    {
//        cout << color << ":";
//        showPoint();
//    }
//};
//
//int main()
//{
//    Point p;
//    ColorPoint cp;
//
//    cp.set(3, 4);
//    cp.setColor("Red");
//    cp.showColorPoint();
//    // cout << cp.x << endl; // Why is this wrong?
//    // ㄴ> public으로 상속받았기 때문에 point의 x, y는 private로 유지된다.
//    // ㄴ> getter, setter 사용해서 접근해야 함
//}   
//
////=========================================================
//// Sportrs Car Example (DIY)
////=========================================================
////#include <iostream>
////using namespace std;
////
////class Car
////{
////    int speed;
////public:
////    Car() { speed = 10; }
////    int getSpeed() { return speed; }
////};
////class SportsCar : public Car 
////{
////    bool turbo;
////public:
////    SportsCar() { turbo = true; }
////    bool getTurbo() { return turbo; }
////};
////
////int main()
////{
////    SportsCar c;
////    cout << c.getSpeed() << endl;
////    cout << c.getTurbo();
////}
//
////=========================================================
//// Shape Example (DIY)
////=========================================================
////#include <iostream>
////using namespace std;
////
////class Shape
////{
////    int x, y;
////public:
////    Shape() { x = 10; y = 20; }
////    int getX() { return x; }
////    int getY() { return y; }
////};
////class Circle : public Shape
////{
////    int r;
////public:
////    Circle() {
////        r = 10;
////        cout << "x: " << getX() <<" y: " << getY() << " r: " << r << endl;
////    }
////
////};
////
////int main()
////{
////    Circle c;
////}
//
//
////=========================================================
//// Constructor vs Destructor Example I
////=========================================================
////#include <iostream>
////using namespace std;
//// 
////class Shape {
////    int x, y;
////public:
////    Shape() { cout << "Shape 생성자() " << endl; }
////    ~Shape() { cout << "Shape 소멸자() " << endl; }
////};
////
////class Rectangle : public Shape {
////    int width, height;
////public:
////    Rectangle() : Shape() {
////        cout << "Rectangle 생성자()" << endl;
////    }
////    ~Rectangle() { cout << "Rectangle 소멸자()" << endl; }
////};
////
////int main()
////{
////    Rectangle  r;
////
////    return 0;
////}
//
////=========================================================
//// Constructor vs Destructor Example II
////=========================================================
////#include <iostream>
////using namespace std;
//// 
////class  A {
////public:
////    A() { cout << "생성자 A" << endl; }
////    A(int x) {
////        cout << "매개변수생성자 A" << x << endl;
////    }
////};
////
////class  B : public A {
////public:
////    B() {
////        cout << "생성자 B" << endl;
////    }
////    B(int x) : A(x + 3) {
////        cout << "매개변수생성자 B" << x << endl;
////    }
////};
////
////int main() {
////    B b1(5), b2;
////}
//
////=========================================================
//// Initialization Example
////=========================================================
////#include <iostream>
////using namespace std;
////
////class Shape {
////    int x, y;
////public:
////    Shape() {
////        cout << "Shape constructor " << endl;
////    }
////    Shape(int xloc, int yloc) : x{ xloc }, y{ yloc } {
////        cout << "Shape constructor(xloc, yloc) " << endl;
////    }
////    ~Shape() {
////        cout << "Shape destructor() " << endl;
////    }
////};
////class Rectangle : public Shape {
////    int width, height;
////public:
////    Rectangle(int x, int y, int w, int h) :Shape(x, y) {
////        width = w; height = h;
////        cout << "Rectangle constructor(x, y, w, h)" << endl;
////    }
////    ~Rectangle() {
////        cout << "Rectangle destructor()" << endl;
////    }
////};
////
////int main()
////{
////    Rectangle r(0, 0, 100, 100);
////    return 0;
////}
//
////=========================================================
//// Parent's Method vs. Child's Method
////=========================================================
////
////class ParentClass {
////public:
////    void print() {
////        cout << "부모 클래스의 print() 멤버 함수" << endl;
////    }
////};
////
////class ChildClass : public ParentClass {
////    int data;
////public:
////    void print() { //멤버 함수 재정의 
////        ParentClass::print();
////        cout << "자식 클래스의 print() 멤버 함수 " << endl;
////    }
////};
//
//
////=========================================================
//// Multiple Inheritance Example (DIY)
////=========================================================
////#include <iostream>
////using namespace std; 
////
////class Father {
////private:
////    
////public:
////    int x = 10;
////};
////class Mother {
////private:
////    
////public:
////    int x = 20;
////};
////class Child : public Father, public Mother{
////private:
////
////public:
////
////};
////
////int main() {
////    Child c1;
////    cout << c1.Father::x << endl;
////    cout << c1.Mother::x << endl;
////    return 0;
////}

#include <iostream>
using namespace std;

int main() {
    // 예시 1: 16진수 출력
    int number = 255;
    cout << "10진수: " << number << endl;
    cout << "16진수: " << hex << number << endl;
    cout.setf(ios::uppercase); // 대문자 설정
    cout << "16진수 (대문자): " << hex << number << endl;
    cout.unsetf(ios::uppercase); // 대문자 설정 해제

    // 예시 2: 과학 산술용 출력
    double pi = 3.14159265359;
    cout << "일반 표기: " << pi << endl;
    cout.setf(ios::scientific, ios::floatfield); // 과학 표기법 설정
    cout << "과학 표기: " << pi << endl;
    cout.setf(ios::fixed, ios::floatfield); // 고정 소수점 설정
    cout << "고정 소수점 표기: " << pi << endl;

    return 0;
}
