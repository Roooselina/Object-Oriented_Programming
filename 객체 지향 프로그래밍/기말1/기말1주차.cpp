#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

//=========================================================
// An example of pointers using dynamic memory
//=========================================================
//int main()
//{
//    srand(time(NULL));
//
//    int number = 10;
//    int* ptr1 = &number;
//    cout << "understadning the pointer" << endl; 
//    cout << "Content of p= " << ptr1 << endl;
//    cout << "Address of 'number'= " << &number << endl;
//    cout << "*Pointer= " << *ptr1 << endl;
//    cout << "Address of the pointer= " << &ptr1 << endl << endl;
//   
//    const int noelements = 5;
//    int* ptr2 = new int[noelements] {};
//    // int * const ptr2 : 포인터 주소 고정   
//    // const int * const ptr2: 포인터 주소 및 값 전부 고정     
//    cout << "Understadning the dynamic memory pointer" << endl;
//    for (int id = 0;id < noelements;id++) {
//        ptr2[id] = rand()%100+1;
//    }
//    for (int id = 0;id < noelements;id++) {
//        cout << ptr2[id] << " vs " << *(ptr2 + id) << endl;
//    }
//    
//    delete[] ptr2;    // 반드시 해주어야 함; 아니면 오류
//    return 0;
//}

//=========================================================
// Pointers for class objects
//=========================================================
//class Circle {
//    int radius;
//public:
//    Circle() { 
//        radius = 1;
//        cout << "Tada (r=" << radius << ")" << endl;
//    }
//    Circle(int r) { 
//        radius = r; 
//        cout << "Tada (r=" << radius << ")" << endl;
//    }
//    ~Circle(){cout<<"Gone with the wind (r=" << radius << ")"<< endl; }
//    double getArea();
//};
//double Circle::getArea() {
//    return 3.14 * radius * radius; 
//}
//int main() {
//    Circle donut, pizza(30);
//
//    cout << donut.getArea() << endl;
//
//    Circle* ptr1;
//    Circle* ptr2;
//    ptr1 = &donut;
//    ptr2 = &pizza;
//    cout << (*ptr1).getArea() << endl; 
//    cout << ptr2->getArea() << endl;
//    // ptr2. getArea() : 오류;
//    // why? 포인터의 메서드를 사용하는 것인데 객체의 메서드에 접근 하는 것 처럼 작성했기 때문
//
//    return 0;
//}

//=========================================================
// Pointers for dynamic memory class objects
//=========================================================
//class Circle {
//    int radius;
//public:
//    Circle() { 
//        radius = 1; 
//        cout << "Let it (r=" << radius << ") be!" << endl; 
//    };
//    Circle(int r) {
//        radius = r;
//        cout << "Let it (r=" << radius << ") be!" << endl;
//    }
//    ~Circle() { cout << "Gone with the wind (r=" << radius << ")" << endl; };
//    void setRadius(int r) { radius = r; }
//    double getArea() { return 3.14 * radius * radius; };
//};
//
//int main() {
//    Circle* ptr1;
//    Circle* ptr2;
//
//    ptr1 = new Circle;
//    ptr2 = new Circle(30);
//
//    cout << (*ptr1).getArea() << endl;
//    cout << ptr2->getArea() << endl;
//    cout << "The vectors in the dynamic memory can be destructed in any order" << endl; 
//    delete ptr1;
//    delete ptr2;
//
//    return 0;
//}

//=========================================================
// In-Class Practice
//=========================================================
//#include <windows.h>
//#include <vector>
//#include <iostream>
//#include <cstdlib>
//#include <ctime>
//#include <string>
//
//class Circle {
//public:
//    int x, y, radius;
//    int num;
//    Circle(int x, int y, int radius, int num) : x(x), y(y), radius(radius), num(num){ cout << "CONSTRUCTOR " << num<<" |"; }
//
//    void draw() {
//        // 랜덤 색상 생성
//        int red = rand() % 256;
//        int green = rand() % 256;
//        int blue = rand() % 256;
//
//        // 그리기 메서드
//        HDC hdc = GetWindowDC(GetForegroundWindow());
//
//        HBRUSH brush = CreateSolidBrush(RGB(red, green, blue));
//        HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, brush);
//
//        Ellipse(hdc, x - radius, y - radius, x + radius, y + radius);
//
//        SelectObject(hdc, oldBrush);
//        DeleteObject(brush);
//    }
//};
//
//int main() {
//    int n;
//    char isRepeat;
//    vector<Circle> circles; 
//
//    srand(time(NULL));
//
//    cout << "How many circles do you need? ";
//    cin >> n;
//
//    // 원 생성
//    for (int i = 0; i < n; i++) {
//        int x = 100 + rand() % 300;
//        int y = 200 + rand() % 200;
//        int radius = rand() % 50;
//
//        Circle c(x, y, radius, i);
//        c.draw();
//        circles.push_back(c);
//    }
//
//
//    return 0;
//}

//=========================================================
// Lab Assignment
//=========================================================
//#include <vector> 
//
//class circle {
//private:
//    int radius;
//public:
//    circle(int r) : radius(r) {
//        cout << "Crying" << endl;
//    }
//    ~circle() {
//        cout << "Dying" << endl;
//    }
//    int getRadius() {
//        return radius;
//    }
//};
//
//int main()
//{
//    srand(time(NULL));
//
//    vector<circle> cirvector;
//    vector<circle>::iterator ptr;
//    unsigned int address1, address2;
//
//    for (int id = 1; id <= 30; id++) {
//        int radius = id * 10;
//
//        cout << endl << "A new iteration" << endl;
//        circle c(radius);
//        if (id != 1) {
//            address1 = reinterpret_cast<int>(&(*ptr));
//        }
//        cirvector.push_back(c);
//        dying은 push_back과 동시에 진행됨
//        /*
//        메모리가 몇 번 할당 된 이후에는 기존 메모리의 1.5배씩 할당되기 때문입니다.
//        1.5배 할당된 된 이후, 값을 더 추가할 때에는 메모리 추가 할당할 필요가 없습니다.
//        따라서 dying 이 생기지 않습니다.
//
//        dying은 n-1개만큼 생김; 1개 push_back하면 n개 완성
//        */
//        ptr = cirvector.begin();
//        if (id != 1) {
//            address2 = reinterpret_cast<int>(&(*ptr));
//            cout << "The address of the first element: " << address1 << " vs " << address2 << endl;
//        }
//        cout << "The capacity of the vector: " << cirvector.capacity() << endl;
//    }
//
//    cout << endl << "Check the radius values!" << endl;
//    for (auto& c : cirvector) {
//        cout << c.getRadius() << endl;
//    }
//
//    cout << endl << "Main function is about to be done" << endl;
//    cout << "The circle objects in the vector need to be destructed" << endl;
//    return 0;
//}
//


