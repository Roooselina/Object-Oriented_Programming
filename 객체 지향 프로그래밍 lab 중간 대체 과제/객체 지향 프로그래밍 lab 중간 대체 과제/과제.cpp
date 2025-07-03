#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <windows.h>
#include <vector>
#include <string>
#include <fstream>
#include <unordered_map>
#include <locale>
#include <codecvt>
#include <algorithm>
#include <ctime>

#include <io.h>      
#include <fcntl.h>

#include "student.h"
#include "StudentInfo.h"

using namespace std;

// 문자열의 앞뒤 공백을 제거하는 함수
wstring trim(const std::wstring& str) {
    // 문자열의 시작 부분에서 공백을 제거
    size_t start = str.find_first_not_of(L" \t\r\n");
    if (start == wstring::npos)
        return L""; // 문자열이 모두 공백인 경우

    // 문자열의 끝 부분에서 공백을 제거
    size_t end = str.find_last_not_of(L" \t\r\n");
    return str.substr(start, end - start + 1);
}

// 매크로 검사
int checkMacro(wstring storedTime, wstring inputTime) {
    int inputHour, inputMin, inputSec;
    int storedtHour, storedMin, storedSec;

    // input  시간 분리
    swscanf(inputTime.c_str(), L"%d:%d:%d", &inputHour, &inputMin, &inputSec);
    // 기준 시 분리
    swscanf(storedTime.c_str(), L"%d:%d:%d", &storedtHour, &storedMin, &storedSec);

    // 총 시간 계산
    // 뺄셈 결과 3초보다 작을 시 매크로로 간주
    int inputTotalSeconds = inputHour * 3600 + inputMin * 60 + inputSec;
    int storedTotalSeconds = storedtHour * 3600 + storedMin * 60 + storedSec;

    if (inputTotalSeconds - storedTotalSeconds < 3) {
        return 1;
    }
    else {
        return 0;
    }
}

// 학생 삽입 함수
void insertStudent(const wstring& info, StudentInfo& studentInfoStructure, vector<Student>& studentVector, size_t startName, const wstring& name, int allOveralQuestionNum) {
    wstring date = info.substr(0, startName - 1);

    // 해당 학생 데이터가 이미 존재하는지 검사
    auto it = studentInfoStructure.studentIndex.find(name);
    if (it != studentInfoStructure.studentIndex.end()) { // 존재할 시
        // 학생 객체의 인덱스 도출
        size_t index = it->second;

        // 매크로 검사
        if (checkMacro(studentVector[index].getEndTime(), date) == 1) {
            return;
        }
        else {
            // 데이터 재설정
            studentVector[index].setEndTime(date);      // 마지막 참여 시간 재설정
            studentVector[index].setParticipateNum();   // participateNum 증가

            if (allOveralQuestionNum >= 0 && studentVector[index].getOverallParticipateNum() < allOveralQuestionNum) {
                // Q 값 동기화
                studentVector[index].addQ(allOveralQuestionNum); // allOveralQuestionNum 값을 직접 Q에 추가
                studentVector[index].setOverallParticipateNum();
            }
        }
    }
    else {
        // 검사 결과에 없을 때에는 새로운 학생 객체 추가
        size_t value = studentInfoStructure.StudentNum;
        studentInfoStructure.studentIndex[name] = value;
        studentInfoStructure.StudentNum++;

        // 새로운 Student 객체를 생성하고 벡터에 추가
        Student newStudent(name, date);

        // 첫 번째 Q 값 추가
        if (allOveralQuestionNum > 0) {
            newStudent.setOverallParticipateNum();
            newStudent.addQ(allOveralQuestionNum); // allOveralQuestionNum 값을 직접 Q에 추가
        }

        studentVector.push_back(newStudent);
    }
}


// 대소문자를 무시하고 비교하는 함수
bool equalsIgnoreCase(const std::wstring& a, const std::wstring& b) {
    if (a.size() != b.size()) return false;
    for (size_t i = 0; i < a.size(); ++i) {
        if (towlower(a[i]) != towlower(b[i])) return false;
    }
    return true;
}

// 내림차순 정렬 함수
void sortStudentsByParticipation(vector<Student>& studentVector) {
    sort(studentVector.begin(), studentVector.end(), [](const Student& a, const Student& b) {
        return a.getParticipateNum() > b.getParticipateNum();
        });
}

void displayParticipationPercentages(const vector<Student>& studentVector, int allOveralQuestionNum, string file) {
    if (studentVector.empty()) {
        return;
    }

    // 어드레스 지정
    time_t now = time(nullptr);
    tm* localTime = localtime(&now);
    wchar_t datePart[50];
    wcsftime(datePart, 50, L"%Y-%m-%d_", localTime);

    // 파일 경로에 날짜와 파일 매개변수를 포함
    wstring filePath = L"C:\\Users\\kuroc\\Documents\\OOP files\\Analyze Files\\";
    filePath += datePart;
    filePath += std::wstring(file.begin(), file.end());
    filePath += L"_chatAnalyze.txt";

    // 파일을 utf-8로 열기
    wofstream outFile(filePath);
    outFile.imbue(locale(outFile.getloc(), new codecvt_utf8<wchar_t>));
    if (!outFile) {
        wcerr << L"쓰기 실패." << endl;
        return;
    }

    // 최대 participateNum 값을 기준으로 함
    int maxParticipation = 0;
    for (const auto& student : studentVector) {
        if (student.getParticipateNum() > maxParticipation) {
            maxParticipation = student.getParticipateNum();
        }
    }

    // 출력
    for (const auto& student : studentVector) {
        double percentage = (static_cast<double>(student.getParticipateNum()) / maxParticipation) * 100;

        // Q 상태 표시
        vector<int> qValues = student.getAllQ();
        wstring absoluteMeasure = L"Absolute Measure: ";
        int overallCount = 0; // (O)로 표시된 Q의 개수를 세는 변수

        // Q값에 따라 O/X를 출력하며 (O)인 경우에만 overallCount 증가
        for (int i = 1; i <= allOveralQuestionNum; ++i) {
            if (find(qValues.begin(), qValues.end(), i) != qValues.end()) {
                absoluteMeasure += L"Q" + to_wstring(i) + L"(O), ";
                overallCount++; // (O)로 표시되면 count 증가
            }
            else {
                absoluteMeasure += L"Q" + to_wstring(i) + L"(X), ";
            }
        }

        // 마지막 쉼표 제거
        if (!absoluteMeasure.empty() && absoluteMeasure.back() == L' ') {
            absoluteMeasure.pop_back();
            absoluteMeasure.pop_back();
        }

        absoluteMeasure += L": Overall " + to_wstring(overallCount) + L"/" + to_wstring(allOveralQuestionNum);

        // 출력 문자열 구성
        wstring relativeMeasure = L"Relative Measure: " + to_wstring(static_cast<int>(percentage)) + L"%";
        wstring output = student.getName() + L": " + relativeMeasure + L" vs\t " + absoluteMeasure;

        // 출력
        wcout << output << endl;
        outFile << output << endl;
    }

    outFile.close();
}



int checkAnswer(wstring line) {
    // 이모지 감지
    if (line.find(L"Reacted to ") != wstring::npos && line.find(L"with") != wstring::npos) {
        return 0;
    }
    if (line.find(L"Removed a ") != std::wstring::npos && line.find(L"reaction from") != std::wstring::npos) {
        return 0;
    }

    // 마지막 인사 감지
    if (line.find(L"감사") != std::wstring::npos ||
        line.find(L"고생하셨습니다") != std::wstring::npos ||
        line.find(L"수고") != std::wstring::npos) {
        return 0;
    }
    return 1;
}

int checkTime(wstring startTime, wstring inputTime) {
    int inputHour, inputMin, inputSec;
    int startHour, startMin, startSec;

    // input  시간 분리
    swscanf(inputTime.c_str(), L"%d:%d:%d", &inputHour, &inputMin, &inputSec);
    // 기준 시 분리
    swscanf(startTime.c_str(), L"%d:%d:%d", &startHour, &startMin, &startSec);

    // 총 시간 계산
    // 뺄셈 결과 300보다 클 시, 5분이 지난 것으로 간주
    int inputTotalSeconds = inputHour * 3600 + inputMin * 60 + inputSec;
    int startTotalSeconds = startHour * 3600 + startMin * 60 + startSec;

    if (inputTotalSeconds > startTotalSeconds + 300) {
        return 0;
    }
    else {
        return 1;
    }
}

int main() {
    /* 임의로 위 폴더에 모든 파일 데이터가 있다고 가정
    파일 이름에 한글이 있으면 제대로 파일 감지가 되지 않음 */
    string targetPath = "C:\\Users\\kuroc\\Documents\\OOP files";

    // setCurrentDirectoryA를 통해 디렉토리 변경
    if (SetCurrentDirectoryA(targetPath.c_str())) {
        wcout << "디렉토리가 바뀌었습니다.\n" << endl;
    }
    else {
        wcout << "디렉토리 이동에 오류가 발생하였습니다." << endl;
        return 1;
    }

    // 파일의 정보를 저장하는 구조체
    WIN32_FIND_DATAA findFile;

    // 디렉토리 내에서 파일을 접근하기 위한 구조체
    HANDLE hFind = FindFirstFileA("*.txt", &findFile);

    if (hFind == INVALID_HANDLE_VALUE) {
        wcout << "유효 데이터가 없습니다." << endl;
        return 1;
    }

    // 파일 및 학생 정보 저장할 벡터
    vector<string> txtFiles;

    do {
        // 벡터에 파일 이름만을 저장
        txtFiles.push_back(findFile.cFileName);
    } while (FindNextFileA(hFind, &findFile) != 0);

    // 파일 탐색 중지
    FindClose(hFind);

    // 모든 파일 목록 출력
    wcout << "파일 목록:\n";
    for (auto& file : txtFiles) {
        cout << file << endl;
    }

    _setmode(_fileno(stdout), _O_U16TEXT);
    _setmode(_fileno(stdin), _O_U16TEXT);

    // 콘솔 인코딩을 UTF-8로 설정
    SetConsoleOutputCP(CP_UTF8);

    //초반 대답을 감지하는 함수
    wstring startTime;
    int isCheck = 0;
    int allOveralQuestionNum = 0;

    for (auto& file : txtFiles) {
        // 학생 정보
        StudentInfo studentInfoStructure;
        vector<Student> studentVector;

        // 파일 열기
        wifstream fileStream(file);
        if (!fileStream.is_open()) {
            wcout << L"ERROR: " << wstring(file.begin(), file.end()) << endl;
            continue;
        }

        // 파일 내용 읽기
        std::wstring line1, line2;
        fileStream.imbue(std::locale(std::locale(), new std::codecvt_utf8<wchar_t>));

        while (std::getline(fileStream, line1)) {
            // 첫 번째 줄이 비어있지 않고 숫자로 시작하는지 확인
            if (!line1.empty() && iswdigit(line1[0])) {
                if (std::getline(fileStream, line2)) {
                    if (isCheck == 0) {
                        isCheck = 1;
                        startTime = line1.substr(0, 8);
                    }

                    // 추출한 문자열의 앞뒤 공백을 제거
                    wstring trimmedLine2 = trim(line2);

                    size_t startName = line1.find(L"From ");
                    if (startName == wstring::npos) {
                        continue;  // "From "이 문자열에 없는 경우 다시 line 탐색
                    }
                    size_t endName = line1.find(L" to");
                    if (endName == wstring::npos) {
                        continue;  // " to"가 문자열에 없는 경우 다시 line 탐색
                    }

                    wstring name = trim(line1.substr(startName + 5, endName - (startName + 5)));
                    if (name.back() == L'_') {
                        name.pop_back();
                    }

                    if (equalsIgnoreCase(name, L"Sunghan Kim")) {
                        if (line2.find(L"참여도") != wstring::npos && line2.find(L"질문") != wstring::npos && line1.find(L"direct message") == wstring::npos) {
                            if (line2.find(L"direct message") == wstring::npos) { // direct message 조건 추가
                                allOveralQuestionNum++;
                            }
                        }
                    }

                    else {
                        if (checkTime(startTime, line1.substr(0, 8)) == 1 &&
                            (trimmedLine2.find(L"나") != wstring::npos || trimmedLine2.find(L"아니오") != std::wstring::npos)) {
                            continue;
                        }
                        else {
                            // 두 번째 줄 대답 검사
                            if (checkAnswer(trimmedLine2) == 1) {
                                insertStudent(line1, studentInfoStructure, studentVector, startName, name, allOveralQuestionNum);
                            }
                            else {
                                continue;
                            }
                        }
                    }
                }
            }
        }
        // 파일 닫기
        fileStream.close();

        // participateNum을 기준으로 내림차순 정렬
        sortStudentsByParticipation(studentVector);

        // file 변수 대문자로 변환
        string upperFile = file;
        transform(upperFile.begin(), upperFile.end(), upperFile.begin(), ::toupper);

        // upperFile을 사용해 출력
        wcout << endl << endl << std::wstring(upperFile.begin(), upperFile.end()) << L" >> RESULT:" << endl;
        wcout << "========================================================================================" << endl;

        // 정렬된 결과 출력 
        displayParticipationPercentages(studentVector, allOveralQuestionNum, file);
        allOveralQuestionNum = 0;
        isCheck = 0;
    }
    return 0;
}
