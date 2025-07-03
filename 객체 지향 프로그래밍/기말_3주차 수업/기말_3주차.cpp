//=========================================================
// What is the meaning of "+"?
//=========================================================
//#include <iostream>
//#include <string>
//using namespace std;
//
//int main()
//{
//    string s1 = "Rogue One:", s2 = "A Star Wars Saga";
//    string s3; 
//    s3 = s1 + s2;
//    cout << "The result of s1+s2 is equal to " << endl << s3 << endl;
//
//    return 0;
//}

//=========================================================
// Overloading Operators as if they are functions 
//=========================================================
//#include <iostream>
//#include <string>
//using namespace std;
//
//class MyVector 
//{
//    int x, y; 
//public:
//    MyVector(int x = 0.0, int y = 0.0) : x(x), y(y) {}
//    string NumtoString() {
//        return "("+to_string(x) +","+to_string(y)+")";
//    }
//    // operator+() as a function
//    MyVector operator+(const MyVector& v);
//    // operator-() as a function
//    MyVector operator-(const MyVector& v);
//    // operator*() as a function
//    int operator*(const MyVector& v);
//};
//
//MyVector MyVector::operator+(const MyVector& v)
//{
//    MyVector v2return;
//    v2return.x = this->x + v.x;
//    v2return.y = this->y + v.y;
//
//    return v2return;
//}
//
//MyVector MyVector::operator-(const MyVector& v)
//{
//    MyVector v2return;
//    v2return.x = this->x - v.x;
//    v2return.y = this->y - v.y;
//
//    return v2return;
//}
//
//int MyVector::operator*(const MyVector& v)
//{
//    int product2return;
//    product2return = this->x * v.x + this->y * v.y;
//
//    return product2return;
//}
//
//int main() 
//{
//    MyVector v1(1, 2), v2(3, 4);
//    MyVector v3 = v1 + v2;
//    MyVector v4 = v1 - v2;
//    int v5 = v1 * v2;
//    cout << v1.NumtoString() << "+" << v2.NumtoString() << "=" << v3.NumtoString() << endl;
//    cout << v1.NumtoString() << "-" << v2.NumtoString() << "=" << v4.NumtoString() << endl;
//    cout << v1.NumtoString() << "*" << v2.NumtoString() << "=" << to_string(v5) << endl;
//
//    return 0;
//}

//=========================================================
// Overloading Operators == and !=
//=========================================================
//#include <iostream>
//using namespace std;
//
//class Time
//{
//    int hour, min, sec;
//public:
//    Time(int h = 0, int m = 0, int s = 0) : hour(h), min(m), sec(s) {}
//    bool operator==(const Time& t);
//    bool operator!=(const Time& t);
//};
//
//bool Time::operator==(const Time& t) {
//    return(this->hour == t.hour && this->min == t.min && this->sec == t.sec);
//}
//
//bool Time::operator!=(const Time& t) {
//    return !(*this==t);
//}
//
//int main()
//{
//    Time t1(10, 5, 35), t2(10, 5, 35);
//
//    cout << "Is t1 equal to t2? " << (t1 == t2) << endl;
//    cout << "Is t1 unequal to t2? " << (t1 != t2) << endl;
//    return 0;
//}

//=========================================================
// Overloading Operators ++
//=========================================================
//#include <iostream>
//using namespace std;
//
//class Counter
//{
//    int value;
//public:
//    Counter() :value(0) {};
//    int getValue() const { return value; }
//    void setValue(int x) { value = x; }
//    Counter& operator++()
//    {
//        this->value += 1;
//        return *this;
//    }
//    Counter& operator++(int)
//    {
//        this->value += 1;
//        return *this;
//    }
//};
//
//int main()
//{
//    Counter c;
//    cout << "The value of the counter: " << c.getValue() << endl;   // C = 0;
//    ++c;
//    // ++C = > 0에서 1로 C가 바뀜
//
//    cout << "The value of the counter: " << c.getValue() << endl;   // C = 1;
//    ++c;
//    // ++C = > 1에서 2로 C가 바뀜
//
//    cout << "The value of the counter: " << c.getValue() << endl;   // C = 2;
//    c++;     
//    // C++ = > 2에서 3로 C가 바뀜
//
//    cout << "The value of the counter: " << c.getValue() << endl;   // C = 3;
//
//    return 0;
//}

//=========================================================
// Friend Functions
//=========================================================
#include <iostream>
using namespace std;

class Date {
friend bool equals(Date d1, Date d2);
private:
    int year, month, day;
public:
    Date(int y = 0, int m = 0, int d = 0) : year(y), month(m), day(d) {   }
};

bool equals(Date d1, Date d2) {
    return (d1.year == d2.year && d1.month == d2.month
        && d1.day == d2.day);
}

int main() {
    Date d1(1960, 5, 23), d2(2002, 7, 23);
    if (equals(d1, d2) == true)
    {
        cout << "Equal" << endl;
    }
    else
    {
        cout << "Different" << endl;
    }

    return 0;
}
