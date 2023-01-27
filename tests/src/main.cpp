#include <base_library/cppptypes/sln_string.hpp>
using namespace _cpppbase::types;
int main(int argc,char* argv[])
{
#if _CPPPRT_PLATFORM == CPPPRT_PLATFORM_WIN32
    SetConsoleCP(GetConsoleCP());
    SetConsoleOutputCP(GetConsoleOutputCP());//refresh codepage
#endif
    setlocale(LC_ALL, "en_US.utf-8");//init locale
    printf("C++ Version: %d", __cplusplus);
    String str(L"TEST");
    wprintf(str.c_str());
    return 0;
}