#include <iostream>
#include <string>
using namespace std; // 삭제 시 오류 발생

    /*
    #include <iostream>
    #include <string>

    int main() {
        std::string name;
        int age;

        std::cout << "What's your name? "; // std::cout<<을 통해 << 뒤의 문자 출력
        std::cin >> name;                  // std::cin에서 받은 입력 값을 name 변수에 저장
        
        처럼 std::를 붙임으로서 std 선언 하지 않고서도 출력 가능함
    }
    */


int main() {
    string name;
    int age;
    bool isAdult; // true or false 값 저장

    cout << "Enter your name and age: ";  // 사용자에게 이름과 나이를 입력하도록 요청
    cin >> name >> age;                  // name과 age를 한 줄에 입력받음 (공백으로 구분)

    // 나이가 18세 이상이면 true, 그렇지 않으면 false
    isAdult = (age >= 18); // true or false 값 저장
    cout << isAdult << endl;

    cout << "Your name is " << name << " and you are " << age << " years old." << endl;
    cout << "Are you an adult? " << (isAdult ? "true" : "false") << endl;

    return 0;
}