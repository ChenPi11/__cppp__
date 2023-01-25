#include <base_library/cppptypes/sln_string.hpp>
using namespace _cpppbase::types;
int main()
{
	setlocale(LC_ALL, "en_US.UTF-8");
	while (1)
	{
		wprintf(repr(String(L"测试abc123=~")).c_str());
		wprintf(L"\n");
	}
}