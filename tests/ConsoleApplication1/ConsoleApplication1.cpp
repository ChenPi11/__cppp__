#include <iostream>
#include <Windows.h>
#include "../../cppp/include/base_library/cppptypes/sln_string.hpp"

int dt = 0;
constexpr int foo()
{
    return dt;
}
volatile int x;
int main(void)
{
    size_t _;
    for (size_t j = 0; j < 1000; j++)
    {
        size_t l = GetTickCount64();
        for (size_t i = 0; i < 100000000; i++)
        {
            x = foo();
        }
        _ = GetTickCount64();
        std::cout << (_-l)<<"\n";
        std::cerr << j/10 << "\n";
    }
}
