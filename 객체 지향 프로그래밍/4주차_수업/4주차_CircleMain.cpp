#include <iostream>

using namespace std;
 #include "Circle.h"

// Circle::Circle(){	//circle 선 선언 되어있지 않아서 오류 생김
//	radius = 1;
//	cout << "Radius = " << radius;
//	cout << "\tA new circle object is created" << endl;
//}
//Circle::Circle(int r) {
//	radius = r;
//	cout << "Radius = " << radius;
//	cout << "\tA new circle object is created"<< endl;
//}
//double Circle::getArea(){
//	return 3.14 * radius * radius;
//}
//
//int main() {
//	Circle donut;
//	//매개변수를 전달하지 않았기 때문에 기본 생성자가 호출; 실제 메모리 할당 된 상태
//	double area = donut.getArea();
//	cout << "the area of a donut = ";
//	cout << area << endl;
//	Circle pizza(30);
//	area = pizza.getArea();
//	cout << "the area of a donut = ";
//	cout << area << endl;
//	return 0;
//}

//그냥 돌리면 위 코드는 오류 생김. 왜?
//	ㄴ> default 생성자가 없으면 오류 생김
//===================================================
// Implement the Combination function
//===================================================
long nCr(int, int);
long fact(int);

int main()
{
    int n, r;
    cout << "전체 샘플 수: ";
    cin >> n;
    cout << "선택할 샘플 수: ";
    cin >> r;
    cout << n << "C" << r << " = " << nCr(n, r) << endl;
    cout << "총 " << n << "개의 샘플 중 " << r << "개의 샘플을 선택하는 방법은 " << nCr(n, r) << "가지가 있습니다." << endl;
    return 0;
}

// nCr을 반환 (조합, 순서가 중요하지 않은 경우)
long nCr(int n, int r)
{
    return fact(n) / (fact(r) * fact(n - r)); // nCr = n! / (r!(n - r)!)
}

// n의 팩토리얼을 반환
long fact(int n)
{
    if (n == 0)
        return 1;
    long res = 1;
    for (int i = 2; i <= n; i++) {
        res = res * i;
    }
    return res;
    /*
    *   n의 팩토리얼을 재귀 호출로 반환
        long fact(int n) {
        if (n <= 1)  // 기본 경우: n이 0 또는 1일 때 팩토리얼은 1
            return 1;
        else
            return n * fact(n - 1);  // 재귀 호출을 통해 n * (n-1)! 계산
        } 
    */
}