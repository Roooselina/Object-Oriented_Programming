#include <iostream>
using namespace std;

void swap(int& x, int& y) {  // 참조 매개변수
    int temp = x;
    x = y;
    y = temp;
}

void reverse(int x[], int y) {  // 참조 매개변수
    for (int i = 0; i < y / 2; i++)
        swap(x[i], x[y - i - 1]);
}

void draw(int n) {
    int j, i;
    for (i = 1; i <= n; i++) {
        for (j = 1; j<=i;j++)
            cout << j;
        for (int k = n - j; k >= 0; k--)
            cout << "*";
        cout << endl;
    }
}

int aa(){
    int a = 10, b = 20;
    cout << "a= " << a << "\tb= " << b << endl;
    //a = 10, b =20;

    //swap
    swap(a, b);
    cout << "a= " << a << "\tb= " << b << endl;
    //a = 20, b= 10;
    
    int* pA = &a;
    int** ppA = &pA;

    cout << "a lives at " << &a << endl;
    cout << "pa lives at " << pA << endl;
    //&a의 주소를 포인터 pa 가 저장, 따라서 &a = pa임
    //포인터: 주소 저장 변수

    cout << "ppA lives at " << ppA << endl;
    //당연히 ppa는 포인터 변수 주소를 가리킴

    cout << "*ppA is pointing:" << *ppA << endl;
    //*를 통해 pa의 값인 a의 주소를 참조; pa 값(=pa가 저장하는 주소) 출력
    cout << "*ppA is pointing:" << **ppA << endl;
    //**를 통해 a의 주소에 도달; *pa랑 같다. a값 출력
   
    int c[] = { 1,2,3,4,5 };
    int d[] = { 2,3,4,5,6,7,8 };

    cout << c << endl;
    cout << d << endl;
    reverse(c, 5);
    reverse(d, 7);
    for (int i = 0; i < 5; i++) {
        cout << c[i] << " ";
    }
    cout << endl;
    for (int i = 0; i < 7; i++) {
        cout << d[i] << " ";
    }
    cout << endl;

    draw(7);
    cout << endl;
    draw(3);


    return 0;
}
