#include <iostream>
using namespace std;

int main() {
    int n = 10;
    int& ref = n;

    ref = ref + 20;

    cout << ref <<" " << n << endl;
    return 0;
}