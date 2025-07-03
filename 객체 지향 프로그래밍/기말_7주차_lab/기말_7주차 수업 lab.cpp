// RecordAudio.cpp : This file contains the 'main' function. Program execution begins and ends there.
#pragma comment(lib,"winmm.lib")

#include <windows.h>
#include <mmsystem.h>
#include <fstream>
#include <iostream>

using namespace std;

int main()
{
    // WAVEFORMATEX 구조체를 채워 녹음할 오디오 포맷 설정
    // 예제에서는 "CD 품질"(44100Hz, 스테레오, 16비트)로 설정
    WAVEFORMATEX wfx = {};
    wfx.wFormatTag = WAVE_FORMAT_PCM;       // PCM 형식 사용
    wfx.nChannels = 2;                      // 2채널 = 스테레오
    wfx.nSamplesPerSec = 44100;             // 샘플레이트: 44100Hz
    wfx.wBitsPerSample = 16;                // 16비트 샘플
    wfx.nBlockAlign = wfx.wBitsPerSample * wfx.nChannels / 8; // 블록 크기
    wfx.nAvgBytesPerSec = wfx.nBlockAlign * wfx.nSamplesPerSec; // 초당 바이트

    // 'waveIn' 녹음 장치 열기
    HWAVEIN wi;
    waveInOpen(&wi,            // 장치 핸들을 wi에 저장
        WAVE_MAPPER,           // 기본 장치 사용
        &wfx,                  // 오디오 포맷 전달
        NULL, NULL,            // 콜백 사용 안 함
        CALLBACK_NULL | WAVE_FORMAT_DIRECT   // 콜백 없이 처리
    );

    // 녹음된 오디오를 저장할 버퍼와 헤더 준비
    char buffers[2][44100 * 2 * 2 / 2];    // 2개의 버퍼, 각각 0.5초 길이
    WAVEHDR headers[2] = { {},{} };        // 헤더 초기화
    for (int i = 0; i < 2; ++i)
    {
        headers[i].lpData = buffers[i];    // 버퍼 포인터 설정
        headers[i].dwBufferLength = 44100 * 2 * 2 / 2; // 버퍼 크기 설정

        // 헤더 준비
        waveInPrepareHeader(wi, &headers[i], sizeof(headers[i]));

        // 대기열에 버퍼 추가
        waveInAddBuffer(wi, &headers[i], sizeof(headers[i]));
    }

    // 녹음 데이터를 저장할 바이너리 파일 열기
    ofstream outfile("my_recorded_audio.bin", ios_base::out | ios_base::binary);

    // 사용자에게 안내 메시지 출력
    cout << "Now recording audio.  Press Escape to stop and exit." << endl;

    // 녹음 시작
    // 큐에 녹음 버퍼들이 채워짐
    waveInStart(wi);

    // 녹음된 버퍼를 지속적으로 확인하고 파일에 저장
    while (!(GetAsyncKeyState(VK_ESCAPE) & 0x8000))  // Esc 키를 누를 때까지 루프
    {
        for (auto& h : headers)      // 각 헤더 확인
        {
            if (h.dwFlags & WHDR_DONE)           // 해당 헤더가 완료되었는지 확인
            {
                // 완료된 버퍼를 파일에 저장
                outfile.write(h.lpData, h.dwBufferLength);

                // 버퍼를 대기열에 다시 추가
                h.dwFlags = 0;          // 완료 플래그 초기화
                h.dwBytesRecorded = 0;  // 녹음된 바이트 수 초기화
                waveInPrepareHeader(wi, &h, sizeof(h));
                waveInAddBuffer(wi, &h, sizeof(h));
            }
        }
    }

    // Esc 키가 눌리면 녹음 중단 및 정리
    waveInStop(wi);
    for (auto& h : headers)
    {
        waveInUnprepareHeader(wi, &h, sizeof(h));
    }
    waveInClose(wi);

    // 파일 닫기
    outfile.close();

    // 녹음된 파일을 재생
    ifstream infile("my_recorded_audio.bin", ios_base::in | ios_base::binary);
    if (!infile)
    {
        cerr << "Error: Could not open the recorded audio file for playback." << endl;
        return 1;
    }

    // 'waveOut' 재생 장치 열기
    HWAVEOUT wo;
    waveOutOpen(&wo, WAVE_MAPPER, &wfx, NULL, NULL, CALLBACK_NULL);

    // 녹음된 데이터를 메모리에 저장
    infile.seekg(0, ios::end);
    size_t dataSize = infile.tellg();
    infile.seekg(0, ios::beg);
    char* dataBuffer = new char[dataSize];
    infile.read(dataBuffer, dataSize);
    infile.close();

    // 재생을 위한 WAVEHDR 준비
    WAVEHDR playbackHeader = {};
    playbackHeader.lpData = dataBuffer;
    playbackHeader.dwBufferLength = dataSize;

    waveOutPrepareHeader(wo, &playbackHeader, sizeof(playbackHeader));
    waveOutWrite(wo, &playbackHeader, sizeof(playbackHeader));

    // 재생 완료를 기다림
    cout << "Playing back recorded audio..." << endl;
    while (!(playbackHeader.dwFlags & WHDR_DONE))
    {
        Sleep(100);  // 100ms 대기
    }

    // 정리 작업
    waveOutUnprepareHeader(wo, &playbackHeader, sizeof(playbackHeader));
    waveOutClose(wo);
    delete[] dataBuffer;

    cout << "Playback finished." << endl;

    return 0;
}
