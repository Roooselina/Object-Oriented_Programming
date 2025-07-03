#include <iostream>
using namespace std;

int flip(int* a, int b); // flip expects an input pointer

int main() {
    cout << "let's get it done!\n";
    int a[10] = { 1,2,3,4,5,6,7,8,9,10 };
    int noelements = sizeof(a) / sizeof(a[0]); //sizeof(): no of bytes, where 1 byte = 8 bits = 2 hexadecimals
    cout << "a[0] is " << a[0] << endl;
    cout << "a's address is " << a << endl;
    cout << "no of elements in a is " << noelements << endl;
    cout << "========== prior to the function ==========" << endl;
    cout << "about to enter the function" << endl;
    flip(a, noelements);
    cout << "========== posterior to the function ==========" << endl;
    for (int element : a) {
        cout << element << " ";
    }
    return 0;
}

int flip(int* a, int noelements) {
    cout << "========== inside the function ==========" << endl;
    for (int i = 0; i < noelements; i++) {
        cout << a[i] << ",";
    }
    cout << endl;

    // Reverse the array
    for (int i = 0; i < noelements / 2; i++) {
        int temp = a[i];
        a[i] = a[noelements - i - 1];
        a[noelements - i - 1] = temp;
    }

    cout << "Array has been reversed!" << endl;
    cout << "========== exiting the function ==========" << endl;

    return 0;
}
