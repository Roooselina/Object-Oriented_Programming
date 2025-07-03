#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <windows.h>
#include <mmsystem.h>
#include <fstream>
#include <string>
#include <io.h>
#include <fcntl.h>
#include <tchar.h>
#include <conio.h>
#include <locale>
#pragma comment(lib, "winmm.lib")

using namespace std;

// 기본 클래스
class FileHandler {
public:
    virtual void displayData(const wstring& filePath) = 0;
    virtual ~FileHandler() = default;
};

// 텍스트 파일 처리
class TextFileHandler : public FileHandler {
public:
    void displayData(const wstring& filePath) override {
        wifstream file(filePath);
        if (!file) {
            wcerr << L"텍스트 파일 로딩 실패" << filePath << endl;
            return;
        }

        wcout << L"텍스트 파일 내용:" << endl;
        wstring line;
        while (getline(file, line)) {
            wcout << line << endl;
        }
        file.close();
    }
};

// 오디오 파일 처리
class AudioFileHandler : public FileHandler {
public:
    void displayData(const wstring& filePath) override {
        if (PlaySound(filePath.c_str(), NULL, SND_FILENAME | SND_SYNC)) {
            wcout << L"오디오 재생 완료: " << filePath << endl;
        }
        else {
            wcerr << L"오디오 로딩 실패" << filePath << endl;
        }
    }
};

// 이미지 파일 처리
class ImageFileHandler : public FileHandler {
public:
    void displayData(const wstring& filePath) override {
        HDC hDC, hMemDC;
        HBITMAP hBitmap, hOldBitmap;
        BITMAP Bitmap;
        RECT WindowRect;

        HWND hWnd = GetConsoleWindow();
        hDC = GetDC(hWnd);
        hMemDC = CreateCompatibleDC(hDC);

        // 비트맵 파일 로드
        hBitmap = (HBITMAP)LoadImage(NULL, filePath.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        if (hBitmap == NULL) {
            wcerr << L"이미지 로딩 오류" << endl;
            DeleteDC(hMemDC);
            ReleaseDC(hWnd, hDC);
            return;
        }

        hOldBitmap = (HBITMAP)SelectObject(hMemDC, hBitmap);
        GetObject(hBitmap, sizeof(BITMAP), &Bitmap);
        GetClientRect(hWnd, &WindowRect);
        BitBlt(hDC, 50, 150, Bitmap.bmWidth, Bitmap.bmHeight, hMemDC, 0, 0, SRCCOPY);

        SelectObject(hMemDC, hOldBitmap);
        DeleteObject(hBitmap);
        DeleteDC(hMemDC);
        ReleaseDC(hWnd, hDC);
    }
};


// Main 함수
int main() {
    // 텍스트 | 오디오 | 이미지 handler
    TextFileHandler textHandler;
    AudioFileHandler audioHandler;
    ImageFileHandler imageHandler;

    // 콘솔 출력 인코딩 UTF-8로 변경
    // for 한국어 출력
    SetConsoleOutputCP(CP_UTF8);

    locale::global(locale("en_US.UTF-8"));
    wcin.imbue(locale());
    wcout.imbue(locale());

    wcout << L"프로그램 실행 : 스페이스 바 입력해주세요" << endl;
    _getch();
    // 텍스트 파일 처리
    textHandler.displayData(L"C:\\Users\\kuroc\\Documents\\OOP lab files\\TestText.txt");

    wcout << L"이미지 파일 로딩 : 스페이스 바 입력해주세요" << endl;
    _getch();
    // 이미지 파일 처리 및 렌더링
    imageHandler.displayData(L"C:\\Users\\kuroc\\Documents\\OOP lab files\\TestBmp.bmp");

    wcout << L"오디오 파일 로딩 : 스페이스 바 입력해주세요" << endl;
    _getch();
    // 오디오 파일 처리
    audioHandler.displayData(L"C:\\Users\\kuroc\\Documents\\OOP lab files\\TestWav.wav");

    // 종료 대기
    wcout << L"모든 프로그램 실행을 완료하였습니다" << endl;
    _getch();

    return 0;
}
