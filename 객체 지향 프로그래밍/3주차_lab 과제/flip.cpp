#include <iostream>
using namespace std;

int flip(int* a, int b);
int swap(int& a, int& b);

int main() {
    int a[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    int noelements = sizeof(a) / sizeof(a[0]); // sizeof(): 바이트 수 반환, 1 바이트 = 8 비트 = 2 16진수

    cout << "a의 주소는 " << a << "입니다." << endl;
    //왜 주소 출력되는가? a는 배열이라 포인터와 동일한 역할 하고 있음

    cout << "a의 요소 개수는 " << noelements << "입니다." << endl;
    cout << "========== 함수 실행 전 ==========" << endl;
    for (int element : a) {
        cout << element << " ";
    }

    cout << "========== 함수 실행 후 ==========" << endl;
    flip(a, noelements);
    for (int element : a) {
        cout << element << " ";
    }
    return 0;
}

int swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;

    return 0;
}

int flip(int* a, int noelements) {
    cout << "========== 함수 내부 ==========" << endl;
    for (int i = 0; i < noelements/2; i++) {
        swap(a[i], a[noelements -1-i]);
    }
    return 0;
}
