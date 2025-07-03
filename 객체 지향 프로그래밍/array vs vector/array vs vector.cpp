// Array&Vector.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <ctime>

using namespace std;

//=========================================================
// Creating Object Arrays
//=========================================================
//class Circle {
//public:
//    int x, y, radius;
//    Circle() :x(0),y(0),radius(0) {}
//    Circle(int x, int y, int r) :x(x), y(y), radius(r) {}
//    ~Circle() {
//        cout << "I (r:"<<radius<<") am going away." << endl;
//    }
//    void print() {
//        cout << "A circle with a radius " << radius << "@(" << x << ", " << y << ")" << endl;
//    }
//};
//
//int main()
//{
//    const int noObjects = 10;
//    Circle objArray[noObjects];
//    
//    for (Circle& c: objArray) {
//        c.x = rand() % 500;
//        c.y = rand() % 300;
//        c.radius = rand() % 100;
//    }
//    cout << "Tne end of the first FOR loop" << endl;
//    for (Circle c: objArray) {
//        c.print();        
//    }
//    /*for (Circle c : objArray) {
//        c.print();
//    }*/
//    cout << "Tne end of the second FOR loop" << endl;
//
//    return 0;
//}

//=========================================================
// Creating Multiple Book Objects
//=========================================================
//class Book {
//    int price;
//    string title;
//public:
//    Book():price(25),title("TBD") {}
//        Book(int p, string t) : price(p), title{t} {}
//    ~Book() {
//        cout << "Au revoir "<<title<< endl;
//    }
//    void print() {
//        cout << "Title: " << title << ",\tPrice: $" << price << endl;
//    }
//};
//
//int main() {
//    Book bookArray[2] = {
//        Book(25,"Welcome C++"),
//        Book(20,"Welcome C")
//    };
//    cout << "List of the Books" << endl;
//    cout << "=====================================" << endl;
//    for (Book& b:bookArray) {
//        b.print();
//    }
//    cout << "=====================================" << endl;
//    return 0;
//}

//=========================================================
// Draw Random Circles
//=========================================================
//#include<windows.h>
//#include<conio.h> //for console input/output
//
//using namespace std;
//
//class Circle{ 
//public:
//    int x, y, radius;    
//    Circle() :x{0},y{0},radius{0}{
//    }
//    Circle(int x,int y,int r) :x{x},y{y},radius{r}{
//    }
//    void draw() { 
//        HDC hdc = GetWindowDC(GetForegroundWindow());
//        Ellipse(hdc,x - radius,y - radius,x + radius,y + radius);
//    } 
//};
//
//int main(void){
//    Circle objArray[10];
//    srand(time(NULL));
//
//    while(true){
//        for(Circle& c:objArray){
//            c.x=rand()%500+100;
//            c.y=rand()%300+100;
//            c.radius=rand()%100;
//            c.draw();
//        }
//        char ch=_getch(); //Get a character from the Windows console
//        if (ch == 'q') {
//            break;
//        }
//    }
//    return 0;
//}

//=========================================================
// Introduction to Vectors
//=========================================================
//#include <vector> //중간고사 출제 유망
//
//int main() {
//    vector<int> fibonacci = {0,1};
//
//    for (int i = 2;i < 12;i++) {
//        fibonacci.push_back(fibonacci[i - 1] + fibonacci[i-2]);    
//        // fibonacci.insert(index,value);
//    }
//    for (auto& element:fibonacci) {
//        cout<<element<<" ";
//    }
//    cout << endl; 
//    do {
//        cout << fibonacci.back() << endl;     //.back = peek()과 같다. 값만 출력함
//        fibonacci.pop_back(); // push_back vs pop_back
//    } while (fibonacci.empty() != true);
//    cout << endl;
//
//    return 0;
//}

//=========================================================
// Introduction to push_back vs pop_back
//=========================================================
//#include <vector>
//
//int main(void) {
//    vector<int> V; // Create an empty vector v
//    for(int i=0; i<10; ++i){
//        V.push_back(i);
//        cout << "The current element = " << V[i] << endl;
//    }    
//    cout<<endl;
//    
//    while(V.empty()!=true){
//        cout << "The deleted element = ";
//        cout<< V.back() << " " << endl;
//        V.pop_back();
//    }
//    cout<<endl;
//}

//=========================================================
// Introduction to Vector Iterator
//=========================================================
//#include <vector>
//
//int main(){
//    srand(time(NULL));
//    vector<int> v1 = {rand()%5,rand()%5,rand()%5,rand()%5,rand()%5};
//    vector<int>::iterator p;
//
//    for (p = v1.begin(); p != v1.end(); p++) {        
//        cout << *p << endl;   // *p = 이 포인터가 가리키는 그 값, &p = 이 포인터가 가리키는 값의 주소 p = 
//    }
//    cout << endl;
//
//    v1.erase(v1.begin() + 2);
//    for (p = v1.begin(); p != v1.end(); p++) {
//        cout << *p << endl;
//    }
//    return 0;
//}

//=========================================================
// Introduction to Vector Iterator
//=========================================================
//#include <vector>
//
//int main(void) {
//	vector<int> v1 = { 5,4,3,2,1 };
//	vector<int> v2(v1); // Duplicate
//
//	if (v1 == v2) {
//		cout << "Two vectors are identical" << endl; 
//	}
//	else if (v1 != v2) {
//		cout << "They are not identical" << endl; 
//	}
//
//	return 0;
//}

//=========================================================
// Introduction to Vector Iterator
//=========================================================
//#include <vector>
//
//class Circle 
//{
//public:
//    int x, y, radius;
//    Circle() :x(0),y(0),radius(0) {}
//    Circle(int x, int y, int r) :x(x), y(y), radius(r) {}
//    void print() {
//        cout << "A circle with a radius " << radius << "@(" << x << ", " << y << ")" << endl;
//    }
//};
//
//int main()
//{
//    const int noObjects = 10;
//    vector<Circle> objVector;
//    
//    srand(time(NULL));
//    for (int id = 0; id < 10; id++) {
//        Circle object{rand()%300,rand()%300,rand()%100};
//        objVector.push_back(object);
//    }
//    cout << "Tne end of the first FOR loop" << endl;
//    for (Circle& c: objVector) {
//        c.print();        
//    }
//    /*for (Circle c : objVector) {
//        c.print();
//    }*/
//    cout << "Tne end of the second FOR loop" << endl;
//
//    return 0;
//}

//=========================================================
// STL Algorithm
//=========================================================
//#include <vector>
//#include <algorithm> // List of STL Algorithms: https://cplusplus.com/reference/algorithm/
//
//class Person {
//private:
//    string name;
//    int age;
//public:
//    Person(string n, int a) {
//        name = n;
//        age = a;
//    }
//    string getName() {
//        return name;
//    }
//    int getAge() {
//        return age;
//    }
//    void print() {
//        cout << name << "-" << age << " years old" << endl;
//    }
//};
//
//bool compareDescend(Person& p1, Person& p2) {
//    return p1.getAge() > p2.getAge();
//}
//bool compareAscend(Person& p1, Person& p2) {
//    return p1.getAge() < p2.getAge();
//}
//
//int main() 
//{
//    vector<Person> list;
//
//    list.push_back(Person("Kim", 30));
//    list.push_back(Person("Park", 22));
//    list.push_back(Person("Lee", 26));
//    list.push_back(Person("Moon", 55));
//    list.push_back(Person("Kang", 35));
//
//    sort(list.begin(),list.end(),compareDescend);
//
//    for (auto& element : list) {
//        element.print();
//    }
//    cout << "The end of the descending-order sorting" << endl << endl; 
//    
//    sort(list.begin(), list.end(), compareAscend);
//
//    for (auto& element : list) {
//        element.print();
//    }
//    cout << "The end of the ascending-order sorting" << endl << endl;
//
//    return 0;
//}

//=========================================================
// What about Array
//=========================================================
//#include <array>
//
//int main() 
//{
//	array<int, 3> list={10,20,30};
//	for (int id = 0; id < list.size(); ++id) {
//		--list[id];
//	}
//	for (auto& element: list) {
//		cout<< element <<" ";
//	}
//	return 0;
//}

//=========================================================
// Lab Practice: Vectors
//=========================================================
// Task: Create a vector holding various food item classes
#include <vector>
#include <algorithm>

class Food
{
public:
    string name;
    Food() :name("Water") {}
    Food(string item) :name(item) {}
    void print() {
        cout << "The name of food items is " << name << endl;
    }
};

bool compareAscend(Food& f1, Food& f2) {
    return f1.name < f2.name;
}

int main()
{
    const int noItems = 5;
    string FoodNames[noItems] = { "MILK","BUTTER","BREAD","SALAD","CUCUMBER" };
    vector<Food> foodVector;
    vector<Food>::iterator p;

    cout << "Completing a vector" << endl;
    for (int id = 0; id < noItems; id++) {
        Food itemCurrent(FoodNames[id]);
        foodVector.push_back(itemCurrent);
    }
    cout << "Tne end of the first FOR loop" << endl << endl;

    for (Food& f : foodVector) {
        f.print();
    }
    cout << "Tne end of the second FOR loop" << endl << endl;


    sort(foodVector.begin(), foodVector.end(), compareAscend);
    for (p = foodVector.begin(); p != foodVector.end(); p++) {
        Food f = *p;
        f.print();
    }
    cout << "Tne end of the third FOR loop" << endl;

    return 0;
}

//=========================================================
// Lab Assignment
//=========================================================
//class Circle {
//private:
//    ? ;
//public:
//    ? ;
//
//};
//
//int main() 
//{
//    vector<Circle> cirVector;
//
//    for (int id = 1; id < 4; id++) {
//        int radius = id * 10;
//        Circle c(radius);
//        cirVector.push_back(c);
//    }
//
//    for (auto& c: cirVector) {
//        cout << c.getRadius() << endl; 
//    }
//    return 0;
//}