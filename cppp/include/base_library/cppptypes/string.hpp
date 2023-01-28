#ifndef _CPPP_TYPES_STRING_HPP_
#define _CPPP_TYPES_STRING_HPP_
#include "basebytes.hpp"
#include "baseexception.hpp"
#include "baseobject.hpp"
#include "basestring.hpp"
#include "../_cpppinclude.h"

namespace _cpppbase
{
    namespace types
    {
        class String : public _cpppbase::types::Object, public _cpppbase::types::BaseString
        {
        public:
            static _CPPP_CONSTEXPR11 const size_t npos = (size_t)(-1);
            String() noexcept;
            String(_In_ size_t __len, _In_reads_or_z_(__len) wchar_t* __data);
            String(_In_z_count_(srclen) const wchar_t* src, _In_ const size_t srclen) noexcept;
            String(_In_ const String& src) noexcept;
            template<size_t srclen> String(_In_z_ const wchar_t(&src)[srclen]) noexcept;
            String(_In_z_ const wchar_t* src) noexcept;
            String(_In_ const std::wstring& src) noexcept;
            String(_In_ const std::string& src, _In_ const std::wstring encoding = _cpppbase::_encoding::default_encoding, _In_ const bool strict = false,_In_ const size_t bufsiz = BUFSIZ);
            String(_In_z_count_(srclen) const char* src, _In_ const size_t srclen, _In_ const std::wstring encoding = _cpppbase::_encoding::default_encoding, _In_ const bool strict = false, _In_ const size_t bufsiz = BUFSIZ);
            ~String() noexcept;
            _Ret_maybenull_ inline _CPPP_CONSTEXPR14 wchar_t* data() const noexcept;
            _Ret_z_ inline _CPPP_CONSTEXPR14 const wchar_t* c_str() const noexcept;
            inline _CPPP_CONSTEXPR14 size_t len() const noexcept;
            inline _CPPP_CONSTEXPR14 size_t length() const noexcept;
            inline _CPPP_CONSTEXPR14 size_t size() const noexcept;
            inline std::wstring __str__() const noexcept;
            void assign(_In_z_count_(srclen) wchar_t* src, _In_ const size_t srclen) noexcept;
            inline wchar_t& at(_In_ const size_t off) const;
            std::wstring __repr__() const;
            String capitalize() const;
            String center(_In_ const size_t width, _In_ const wchar_t fill = L' ') const;
            size_t count(_In_ const wchar_t chr) const;
            BaseBytes encode(_In_ const String& encoding = _cpppbase::_encoding::default_encoding,_In_ const bool strict = true,_In_ const size_t bufsiz=BUFSIZ) const;
            bool endswith(_In_ const String& suffix) const;
            String expandtabs(_In_ const size_t& n = 8) const;
            size_t find(_In_ const String& sub, _In_ const size_t off = 0) const;
            String format(_In_ const String&, ...) const;
            String format_map(_In_ const std::map<String, String>& mapping) const;
            bool is_alnum() const;
            bool is_alpha() const;
            bool is_ascii() const;
            bool is_decimal() const;
            bool is_digit() const;
            bool is_lower() const;
            bool is_printable() const;
            bool is_isspace() const;
            bool is_upper() const;
            String join(_In_ const std::vector<String>& iterable) const;
            String ljust(_In_ const size_t width, _In_ const wchar_t fill = L' ') const;
            String lower() const;
            String lstrip() const;
            String replace(_In_ const String& from, _In_ const String& to) const;
            size_t rfind() const;
            String rjust(_In_ const size_t width, _In_ const wchar_t fill = L' ') const;
            String rstrip() const;
            std::vector<String> split(_In_ const String& sep,_In_ const size_t maxsplit) const;
            bool startswith() const;
            String strip() const;
            String title() const;
            String upper() const;
            operator std::wstring() const noexcept;
            operator wchar_t* () const noexcept;
            operator const wchar_t* ()const noexcept;
            inline constexpr wchar_t& operator[](_In_ const size_t off) const noexcept;
            String operator+(_In_ const String& s2) const;
            String& operator= (_In_ const String& s2);
            String operator==(_In_ const String& s2) const;
            String operator*(_In_ const size_t count) const;
            String operator+=(_In_ const String& s2);
        };
        
    }
}
#endif