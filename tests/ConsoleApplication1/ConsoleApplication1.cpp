#include <iostream>
#include <Windows.h>
#include "../../cppp/include/base_library/cppptypes/sln_string.hpp"
//#include <stacktrace>
int main(void)
{
    _cpppbase::types::String wstr, s,__;
    wstr = L"test测试";
    s = L"abcd测试";
    
    for (size_t i = 0; i < 100; i++)
    {
        auto x=GetTickCount64();
        for (size_t j = 0; j < 500000; j++)
        {
            __=wstr + s;
        }
        std::cout<<GetTickCount64()-x<<"\n";
    }
}
