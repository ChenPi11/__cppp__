/**
 * @file include/base_library/cppptypes/baseexception.hpp
 * @author ChenPi11
 * @copyright Copyright (C) 2023
 * @date 2023-1-16
 * @language C++
 * @brief C++ Plus Exception type base
 */
#ifndef _CPPP_TYPES_BASE_EXCEPTION_HPP_
#define _CPPP_TYPES_BASE_EXCEPTION_HPP_
#include "../_cpppinclude.h"
#include "../_encoding.hpp"

namespace _cpppbase
{
	namespace types
	{
		namespace exc
		{
			using namespace _cpppbase::_encoding;
			/**
			 * @date 2023-1-16
			 * @brief C wstring type
			 */
			_Struct_size_bytes_(length) struct c_wstring
			{
				//wstring length
				_Field_range_(0, (size_t)(-1)) size_t length;
				//wstring buffer
				_Field_size_(length) wchar_t* buf;
			};

			c_wstring wstrerror(const int c)
			{
#if _CPPPRT_PLATFORM == CPPPRT_PLATFORM_LINUX
				//GNU has locale mode
				char* _msg = strerror_l(c, LC_GLOBAL_LOCALE);
#else
#if _CPPPRT_CRT_SECURE_NO_WARNINGS
				//CRT no warnings mode (default)
				char* _msg = strerror(c);
#else
				//MSVC CRT secure mode (MSVC)
				char _msg[BUFSIZ]{};
				strerror_s(_msg, c);
#endif
#endif
				wchar_t* out=NULL;
				size_t len;
				atow(_msg, strlen(_msg), default_encoding, &out, &len, false, BUFSIZ);
				if (out == NULL)
				{
					return {0, const_cast <wchar_t*>(L"") };
				}
				return { len,out };
			}
			/**
			 * @date 2023-1-16
			 * @brief C strerror
			 * @param c errno	[in]
			 * @return c_wstring error wstring
			 */
			c_wstring u_se(const int c)
			{
				return wstrerror(c);
			}
#if _CPPPRT_PLATFORM == CPPPRT_PLATFORM_WIN32
			/**
			 * @date 2023-1-16
			 * @brief get formatted message
			 * @param pMessage source message [in]
			 * @param msgsiz result message length [out]
			 * @return c_wstring error wstring result
			 */
			inline LPWSTR _GetFormattedMessage(LPWSTR pMessage, size_t* msgsiz, ...)
			{
				if (pMessage)
				{
					LPWSTR pBuffer{};
					va_list args = NULL;
					va_start(args, msgsiz);
					*msgsiz = FormatMessageW(FORMAT_MESSAGE_FROM_STRING | FORMAT_MESSAGE_ALLOCATE_BUFFER,
						pMessage, 0, 0, (LPWSTR)&pBuffer, 0, &args);
					va_end(args);
					LocalFree(pMessage);
					return pBuffer;
				}
				return NULL;
			}
			/**
			 * @date 2023-1-16
			 * @brief get Windows error 
			 * @param c Windows errror code [in]
			 * @return c_wstring error wstring
			 */
			c_wstring w_se(const DWORD c)
			{
				LPWSTR lpMsgBuf{};
				size_t msgsiz = FormatMessageW(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL,
					(DWORD)c, LANG_USER_DEFAULT, (LPWSTR)&lpMsgBuf, 0, NULL);
				if (lpMsgBuf == NULL)//FormatMessageW error
				{
					DWORD le = GetLastError();
					std::wstringstream wss{};
					wss << std::hex << c;
					std::wstring hexle;
					wss >> hexle;
					
					FormatMessageW(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL,
						(DWORD)le, LANG_USER_DEFAULT, (LPWSTR)&lpMsgBuf, 0, NULL);
					if (lpMsgBuf == NULL)
					{
					ERR2:
						//wchar_t* buf = new wchar_t[1]{L''};
						//_ultow_s(le, buf,11, 10);
						//return { 11,buf };
						return {0, nullptr};
					}
					lpMsgBuf = _GetFormattedMessage(lpMsgBuf, &msgsiz, hexle.c_str(), L"This Application");
					if (lpMsgBuf == NULL)
					{
						le = GetLastError();
						goto ERR2;
					}
				}
				wchar_t* res = new wchar_t[msgsiz]; {};
				size_t o = 0;
				for (size_t i = 0; i < msgsiz; i++)
				{
					if (lpMsgBuf[i] != L'\r' && lpMsgBuf[i] != L'\n')
					{
						res[o] = lpMsgBuf[i];
						o++;
					}
				}
				LocalFree(lpMsgBuf);
				return { o + 1,res };
			}
#endif
			/**
			 * @date 2023-1-16
			 * @brief C++ Plus get OSError string
			 * @param c Windows errror code [in]
			 * @param iswinerr is windows error (only use in Windows platform)
			 * @return c_wstring error wstring
			 */
			c_wstring se(const int c,const bool iswinerr)
			{
#if _CPPPRT_PLATFORM == CPPPRT_PLATFORM_WIN32
				if (iswinerr)
				{
					return w_se((DWORD)c);
				}
#endif
				return u_se(c);
			}
		}
	}
}
#endif