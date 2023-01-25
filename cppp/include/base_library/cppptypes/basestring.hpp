/**
 * @file include/base_library/cppptypes/basestring.hpp
 * @author ChenPi11
 * @copyright Copyright (C) 2023
 * @date 2023-1-15
 * @language C++
 * @brief C++ Plus String type base
 */
#ifndef _CPPP_TYPES_BASE_STRING_HPP_
#define _CPPP_TYPES_BASE_STRING_HPP_

#include <iostream>
namespace _cpppbase
{
	namespace types
	{
		/**
		 * @date 2023-1-15
		 * @brief C++ Plus BaseString
		 */
		class BaseString
		{
		public:
			//construct
			BaseString() = default;
			//deconstruct
			~BaseString() = default;
			_CONSTEXPR20 operator std::wstring()
			{
				return std::wstring(_data, _len);
			}
		protected:
			//data
			_Field_z_ wchar_t* _data = nullptr;
			//length
			_Field_range_(0, (size_t)(-1)) size_t _len=0;
			//construct
			BaseString(_In_ size_t __len, _In_reads_or_z_(__len) wchar_t* __data) : _data(__data),_len(__len) {}
		};

		template<typename T>
		_Ret_z_ inline wchar_t* cppp_copy_z(_In_ const size_t len,_In_reads_(len) const T* src) noexcept
		{
			T* res = new T[len+1];
			for (size_t i = 0; i < len; i++)
			{
				res[i] = src[i];
			}
			res[len] = 0;
			return res;
		}
		template<typename T>
		inline void cppp_memwrite(_In_ const T* src,_In_ const size_t len, _In_reads_(len) T* begin) noexcept
		{
			for (size_t i = 0; i < len; i++)
			{
				begin[i] = src[i];
			}
		}
		inline wchar_t* _wchhex(wchar_t c,wchar_t* res)
		{
			typedef unsigned char sint;
#define tow(wch) (wchar_t)(wch < 10 ? (L'0' + wch) : L'a' + (wch - 10))
			res[0] = L'\\';
			res[1] = L'x';
			sint i;
			for (i = 2; i < 6; i++)
			{
				res[i] = L'0';
			}
			i = 5;
			while (i>=2)
			{
				res[i]=tow(c%16);
				c = c / 16;
				i--;
			}
			return res;
#undef tow
		}
		inline size_t wrepr_size(_In_z_count_(len) const wchar_t* s, _In_ const size_t len)
		{
			size_t res=0;
			for (size_t i = 0; i < len; i++)
			{
				switch (s[i])
				{
				case L'\r':
				case L'\t':
				case L'\\':
				case L'\a':
				case L'\f':
				case L'\'':
				case L'\"':
				case L'\v':
				case L'\b':
				case L'\n':// '\\','x'
					res += 2;
					break;
				default:
					if (iswprint(s[i]) && !iswcntrl(s[i]))
					{
						//'c'
						res++;
					}
					else
					{
						// '\','x','0','0','0','0'
						res += 6;
						
					}
				}
			}
			return res;
		}
#define _c_string(s) s,((sizeof(s)/sizeof(s[0]))-1)
#define _s _c_string
		inline wchar_t* wsrepr(_In_z_count_(len) const wchar_t* s, _In_ const size_t len,
			_Out_ size_t& rlen)
		{
			rlen = wrepr_size(s,len)+2;
			wchar_t* res = new wchar_t[rlen + 1];//'"','"','\0'
			res[0] = L'\"';
			res[rlen-1] = L'\"';
			res[rlen] = L'\0';
			size_t cur = 1;

			for (size_t i = 0; i < len; i++)
			{
				switch (s[i])
				{
				case L'\r':
					cppp_memwrite(_s(L"\\r"), res + cur);
					cur += 2;
					break;
				case L'\t':
					cppp_memwrite(_s(L"\\t"), res + cur);
					cur += 2;
					break;
				case L'\\':
					cppp_memwrite(_s(L"\\\\"), res + cur);
					cur += 2;
					break;
				case L'\a':
					cppp_memwrite(_s(L"\\a"), res + cur);
					cur += 2;
					break;
				case L'\f':
					cppp_memwrite(_s(L"\\f"), res + cur);
					cur += 2;
					break;
				case L'\"':
					cppp_memwrite(_s(L"\\\""), res + cur);
					cur += 2;
					break;
				case L'\v':
					cppp_memwrite(_s(L"\\v"), res + cur);
					cur += 2;
					break;
				case L'\b':
					cppp_memwrite(_s(L"\\b"), res + cur);
					cur += 2;
					break;
				case L'\n':// '\\','x'
					cppp_memwrite(_s(L"\\n"), res + cur);
					cur += 2;
					break;
				default:
					if (iswprint(s[i]) && !iswcntrl(s[i]))
					{
						//'c'
						*(res+cur) = s[i];
						cur++;
					}
					else
					{
						// '\','x','0','0','0','0'
						_wchhex(s[i], res + cur);
						cur += 6;
					}
				}
			}
			return res;
		}

#undef _s
	}
}
#endif