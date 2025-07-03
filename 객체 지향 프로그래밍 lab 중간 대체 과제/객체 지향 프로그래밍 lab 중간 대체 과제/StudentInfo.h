// StudentInfo.h
#pragma once

#include <unordered_map>
#include <string>

struct StudentInfo {
    int StudentNum = 0;
    std::unordered_map<std::wstring, int> studentIndex;
};
