#include <Windows.h>

#include <iostream>
#include <string>
using namespace std::string_literals;

#include "printing.hpp"

void setEnvironment(LPWCH strings, const std::wstring& name)
{
    std::wcout << "\nsetEnvironment(" << name << L")\n";

    // Accoring to https://docs.microsoft.com/en-us/windows/win32/api/processenv/nf-processenv-setenvironmentstringsw
    // SetEnvironmentStringsW should return S_OK (0) on success, but it doesn't:
    // it returns TRUE (1) on success and FALSE (0) on failure.
    // It also sets an error code obtainable via GetLastError().
    const auto retVal{SetEnvironmentStringsW(strings)};
    if (retVal == FALSE)
    {
        std::wcout << L"SetEnvironmentStringsW(" << name << L") failed, retVal: "
            << retVal << L", GetLastError(): " << GetLastError() << L"\n";
    }
    else
    {
        std::wcout << L"SetEnvironmentStringsW(" << name << L") succeeded, retVal: "
            << retVal << L"\n";
    }

    std::wcout << "retVal == S_OK: " << std::boolalpha << (retVal == S_OK) << L"\n\n";
}

int main()
{
    std::wcout << L"main()\n";
    printCurrentEnvironment();
    
    auto currentError = GetLastError();
    std::wcout << L"Current error value: " << currentError << L"\n";
    setEnvironment(L"adjsiojqwoidm190"s.data(), L"badEnv");
    printCurrentEnvironment();
    
    setEnvironment(
        L"GoodEnvVarName1=GoodEnvVarValue1\0GoodEnvVarName2=GoodEnvVarValue2\0\0"s.data(),
        L"goodEnv"
    );
    printCurrentEnvironment();
}
