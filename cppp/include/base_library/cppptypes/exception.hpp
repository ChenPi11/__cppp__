#include "basebytes.hpp"
#include "baseexception.hpp"
#include "baseobject.hpp"
#include "basestring.hpp"
#include "../_cpppinclude.h"
#include "string.hpp"
#include <exception>
namespace _cpppbase
{
    namespace types
    {
        class Errno : public Object
        {
        public:
            Errno() noexcept = default;
            Errno(_In_ const Errno& e) noexcept : code(e.code), iswinerror(e.iswinerror) {}
            Errno(_In_ const int __c, _In_ const bool __i = false) noexcept : code(__c), iswinerror(__i) {}
#if _CPPPRT_PLATFORM ==CPPPRT_PLATFORM_WIN32
            Errno(_In_ const DWORD __c, _In_ const bool __i = true) noexcept : code((int)__c), iswinerror(__i) {}
            constexpr void set(_In_ const DWORD __c, _In_ const bool __i = false) noexcept
            {
                code = (int)__c;
                iswinerror = __i;
            }
            operator DWORD() { return (DWORD)code; }
            inline Errno& operator=(const DWORD c) noexcept
            {
                code = (int)c;
                return *this;
            }
            constexpr bool operator==(const DWORD c) const noexcept
            {
                return code == c;
            }
#endif
            constexpr void set(_In_ const int __c, _In_ const bool __i = false) noexcept
            {
                code = __c; iswinerror = __i;
            }
            String strerror() const noexcept
            {
                auto e = _cpppbase::types::exc::se(code, iswinerror);
                String res;
                res.assign(e.buf, e.length);
                return res;
            }
            operator String() const noexcept { return strerror(); }
            operator int() const noexcept { return code; }
            inline Errno& operator=(const Errno& e) noexcept
            {
                code = e.code; iswinerror = e.iswinerror;
                return *this;
            }
            inline Errno& operator=(const int c) noexcept
            {
                code = c;
                return *this;
            }
            constexpr bool operator==(const Errno& e) const noexcept
            {
                return code == e.code && iswinerror == e.iswinerror;
            }
            constexpr bool operator==(const int c) const noexcept
            {
                return code == c;
            }
            int code = 0;
            bool iswinerror = false;
        };

        class Exception : public Object
        {
        public:
            Exception() = default;
            Exception(const Exception& e) : msg(e.msg), name(e.name), code(e.code), info(e.info) {}
            Exception(const String& __m, Errno __c = Errno(0), void* __i = NULL, String __n = String(L"Exception")) : msg(__m), code(__c), info(__i), name(__n) {}

            virtual std::wstring __str__() const { return name + L": " + msg; }
            virtual std::wstring __repr__() const
            {
                return name + L"(" + msg + L")";
            }
            
            operator std::wstring() const { return __str__(); }
            //operator std::string() const { return what(); }
            String msg;
            Errno code;
            void* info = NULL;
            ~Exception() noexcept = default;
        protected:
            String name;
        };

        template<typename T>
        String tostring(const T& x)
        {
            return String(std::to_wstring(x).c_str(),1);
        }

        class OSError : public Exception
        {
        public:
            OSError() noexcept
            {
                name = String(L"OSError");
            }
            OSError(const String& __m, Errno __c = Errno(0), void* __i = NULL, String __n = String(L"OSError")) noexcept
            {
                msg = __m;
                code = __c;
                info = __i;
                name = __n;
            }
            OSError(const Errno __c)
            {
                name = String(L"OSError");
                code = __c;
                msg = L"";
                info = NULL;
            }
            std::wstring __str__() const
            {
                if (code == (int)0)
                {
                    return name + L": " + msg;
                }
                else
                {
                    return name + L": [Errno " + tostring((unsigned long)code.code) + L"q " +
                        code.strerror() + L"]: " + msg;
                }
            }
        };

#define CPPP_MAKE_EXCEPTION(name,der) class name:public der {}

    }

    namespace builtins
    {
        typedef _cpppbase::types::OSError UnicodeDecodeError;
        typedef _cpppbase::types::Exception IndexError;
    }
}