#include <base_library/cppptypes/sln_string.hpp>
using namespace _cpppbase::types;

int inline __forceinline s()
{
    return 0;
}

int main(int argc,char* argv[])
{
#if _CPPPRT_PLATFORM == CPPPRT_PLATFORM_WIN32
    SetConsoleCP(GetConsoleCP());
    SetConsoleOutputCP(GetConsoleOutputCP());//refresh codepage
#endif
    setlocale(LC_ALL, "en_US.utf-8");//init locale
    //wprintf(L"C++ Version: %d", __cplusplus);
    size_t size=4321432,x=0;
    while(1)
    {
    Type t;
	t.set<Object>();
	std::wcout<<t.__name__;
    }
    return 0;
}