#include "Student.h"

// 생성자
Student::Student(wstring name, wstring startTime)
    : name(name), starParticipateTime(startTime), participateNum(0), overallParticipateNum(0) {}

// 이름
wstring Student::getName() const {
    return name;
}

// 참여 횟수
void Student::setParticipateNum() {
    participateNum++;
}

int Student::getParticipateNum() const {
    return participateNum;
}

// 종료 시간
void Student::setEndTime(const wstring& endtime) {
    endParticipateTime = endtime;
}

wstring Student::getEndTime() {
    return endParticipateTime;
}

// 전체 참여 횟수
void Student::setOverallParticipateNum() {
    overallParticipateNum++;
}

int Student::getOverallParticipateNum() const {
    return overallParticipateNum;
}

// Q 배열
void Student::setQ(int index, int value) {
    if (index >= 0 && index < Q.size()) {
        Q[index] = value;
    }
}

int Student::getQ(int index) const {
    if (index >= 0 && index < Q.size()) {
        return Q[index];
    }
    return -1;
}

void Student::addQ(int value) {
    Q.push_back(value);
}

vector<int> Student::getAllQ() const {
    return Q;
}
