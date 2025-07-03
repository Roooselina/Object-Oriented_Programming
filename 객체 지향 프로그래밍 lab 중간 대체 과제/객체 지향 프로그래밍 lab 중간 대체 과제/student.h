#ifndef STUDENT
#define STUDENT

#include <string>
#include <vector>
using namespace std;

class Student {
private:
    wstring name;
    wstring starParticipateTime;
    wstring endParticipateTime;
    int participateNum;
    int overallParticipateNum;
    vector<int> Q;

public:
    // 생성자
    Student(wstring name, wstring startTime);

    // 이름
    wstring getName() const;

    // 참여 횟수
    void setParticipateNum();
    int getParticipateNum() const;

    // 종료 시간
    void setEndTime(const wstring& endtime);
    wstring getEndTime();

    // 전체 참여 횟수
    void setOverallParticipateNum();
    int getOverallParticipateNum() const;

    // Q 배열 관련 메서드
    void setQ(int index, int value); // 특정 Q값 설정
    int getQ(int index) const;      // 특정 Q값 get
    void addQ(int value);           // Q배열 값 추가
    vector<int> getAllQ() const;    // 전체 Q return
};

#endif
