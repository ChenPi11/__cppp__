/**
 * @file include/base_library/basedef.hpp
 * @author ChenPi11
 * @copyright Copyright (C) 2023
 * @date 2023-1-8
 * @language C++
 * @brief C++ Plus base defines
 */
#ifndef _CPPP_BASE_DEFINES_
#define _CPPP_BASE_DEFINES_

#include "_cpppinclude.h"
#include "_encoding.hpp"

#define __cppp_substring(s,start,end) s.substr(start,end-start)
namespace _cpppbase
{
	constexpr const wchar_t* default_codename = L"utf-8";
	namespace base_algo
	{
		//Byte unsigned char
		typedef unsigned char Byte;
		constexpr bool isunreprable(const char c)
		{
			return (' ' <= c && c <= '~');
		}
		inline bool isreprable(const wchar_t c)
		{
			return iswcntrl(c);
		}
		_CONSTEXPR20 std::wstring getrepr(const char c)
		{
			switch (c)
			{
			case '\r':
				return L"\\r";
			case '\t':
				return L"\\t";
			case '\\':
				return L"\\\\";
			case '\a':
				return L"\\a";
			case '\f':
				return L"\\f";
			case '\'':
				return L"\\\'";
			case '\"':
				return L"\\\"";
			case '\v':
				return L"\\v";
			case '\b':
				return L"\\b";
			case '\n':
				return L"\\n";
			default:
				constexpr unsigned long long _bufsize = 5;// '\\','x','0','0' -> '\x00'
				wchar_t str[_bufsize] {};
				int l;
#if _CPPPRT_PLATFORM == CPPPRT_PLATFORM_WIN32
				if ((Byte)c <= 0xf)
				{
					l = swprintf_s(str, _bufsize, L"\\x0%x", (Byte)c);
				}
				else
				{
					l = swprintf_s(str, _bufsize, L"\\x%x", (Byte)c);
				}
#else
				l = swprintf(str, _bufsize, L"\\x%x", (Byte)c);
#endif
				if (l <= 0)
				{
					return { (wchar_t)btowc(c) };
				}
				return str;
			}
		}
		_CONSTEXPR20 std::wstring getwrepr(const wchar_t c)
		{
			switch (c)
			{
			case L'\r':
				return L"\\r";
			case L'\t':
				return L"\\t";
			case L'\\':
				return L"\\\\";
			case L'\a':
				return L"\\a";
			case L'\f':
				return L"\\f";
			case L'\'':
				return L"\\\'";
			case L'\"':
				return L"\\\"";
			case L'\v':
				return L"\\v";
			case L'\b':
				return L"\\b";
			case L'\n':
				return L"\\n";
			default:
				int l;
				constexpr unsigned long long _bufsize = 7;// \x0000
				wchar_t str[_bufsize]{};
#if _CPPPRT_PLATFORM == CPPPRT_PLATFORM_WIN32
				l = swprintf_s(str, _bufsize, L"\\x%04lx", c);
#else
				l = swprintf(str, _bufsize, L"\\x%04lx", (Byte)c);
#endif
				return str;
			}
		}
		_CONSTEXPR20 std::wstring repr(const std::string& s)
		{
			std::wstring res;
			for (auto& i : s)
			{
				if (isunreprable(i))
				{
					res.push_back(btowc(i));
				}
				else
				{
					res+=getrepr(i);
				}
			}
			return res;
		}
		_CONSTEXPR20 std::wstring repr(const char* s, size_t l)
		{
			std::wstring res;
			for (size_t i = 0; i < l; i++)
			{
				if (isunreprable(s[i]))
				{
					res.push_back(btowc(s[i]));
				}
				else
				{
					res+=getrepr((int)*(unsigned char*)(void*)(s + i));
				}
			}
			return res;
		}

		_CONSTEXPR20 std::wstring repr(const std::wstring& s)
		{
			std::wstring res;
			for(auto& w : s)
			{
				if (isreprable(w))
				{
					res.append(getwrepr(w));
				}
				else
				{
					res.push_back(w);
				}
			}
			return res;
		}
		template <typename T> constexpr auto endwith(std::basic_string<T> s, std::basic_string<T> c) { return (s.find_last_of(c) + c.size() == s.size()); }
		template <typename T> constexpr auto startwith(std::basic_string<T> s, std::basic_string<T> c) { return (s.find_first_of(c) == 0); }
		template <typename T>
		constexpr std::basic_string<T> replace(std::basic_string<T> s1, const std::basic_string<T>& s2, const std::basic_string<T>& s3)
		{
			size_t pos = 0;
			size_t a = s2.size();
			size_t b = s3.size();
			while ((pos = s1.find(s2, pos)) != std::basic_string<T>::npos)
			{
				s1.erase(pos, a);
				s1.insert(pos, s3);
				pos += b;
			}
			return s1;
		}
		
		template<typename T>
		std::vector<T> make_vector(T* p, size_t len)
		{
			std::vector<T> v(len);
			for (size_t i = 0; i < len; i++)
			{
				v.push_back(p[i]);
			}
			return v;
		}

		namespace cxxtypes
		{
			template<typename T>
			auto type_name()
			{
				return typeid(T).name();
			}
			
		}
}
}
#endif