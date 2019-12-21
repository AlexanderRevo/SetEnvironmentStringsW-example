#pragma once

#include <Windows.h>

#include <iostream>
#include <string>
#include <vector>

std::vector<std::wstring> rawStringsToVector(LPWCH rawStrings)
{
    std::vector<std::wstring> result;
    for (; *rawStrings != 0; ++rawStrings)
    {
        auto begin = rawStrings;
        while (*rawStrings != 0)
        {
            ++rawStrings;
        }
        result.emplace_back(begin, rawStrings);
    }
    return result;
}

void printCurrentEnvironment()
{
    auto envStrings{GetEnvironmentStringsW()};
    if (envStrings == nullptr)
    {
        std::wcout << L"Failed to get environment strings\n";
        return;
    }
    auto strings{rawStringsToVector(envStrings)};
    FreeEnvironmentStringsW(envStrings);

    std::wcout << L"Current environment strings:\n";
    for (const auto& string : strings)
    {
        std::wcout << string << L'\n';
    }
}
