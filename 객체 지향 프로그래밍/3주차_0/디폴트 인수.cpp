#include <iostream>
using namespace std;

int sum(int x, int y, int z = 1000, int w = 100) {   
    // 디폴트 인수는 항상 일반 매개변수 뒤에 와야 함, 아니면 오류
    return x + y + z + w;
}

int main() {
    cout << "sum(10, 15) = " << sum(10, 15) << endl;
    // z, w가 전달되지 않았으므로, z,w 적용; 10+25+1000+100 = 1125;
    cout << "sum(10, 15, 25) = " << sum(10, 15, 25) << endl;
    //전달된 z는 실제로 사용함; w만 전달 x; 디폴트 인수 사용; 10+15+25+100=150;
    cout << "sum(10, 15, 25, 30) = " << sum(10, 15, 25, 30) << endl;
    //전부 전달되었으므로 아무 디폴트 인수 사용 x; 10+15+25+30=80;
    return 0;
}