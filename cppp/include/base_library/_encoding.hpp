/**
 * @file include/base_library/_encoding.hpp
 * @author ChenPi11
 * @copyright Copyright (C) 2023
 * @date 2023-1-13
 * @language C++
 * @brief C++ Plus encoding support
 */
#ifndef _CPPP_BASELIB_ENCODING_H_
#define _CPPP_BASELIB_ENCODING_H_
#include "_cpppinclude.h"
#include "_codepages.h"
namespace _cpppbase
{
	namespace _encoding
	{
		constexpr static const wchar_t* const default_encoding = L"utf-8";
		struct _encoding_error_t
		{
			int eno;
			const wchar_t* msg;
		};
		/**
		 * @date 2023-1-13
		 * @brief convert multi-byte string to Unicode string by "cp"
		 * @param str	source multi-byte string
		 * @param slen	source string length
		 * @param cp	codename
		 * @param out	output string
		 * @param lout	output length
		 * @param strict	is strict mode
		 * @param bufsiz	convert buffer size (only Linux)
		 * @return _encoding_eror_t error info if errno
		 */
		inline _encoding_error_t atow(const char* str, const size_t slen,
			const wchar_t* cp,
			wchar_t** out, size_t* lout,
			const bool strict,const size_t bufsiz);
		/**
		 * @date 2023-1-13
		 * @brief convert Unicode string to multi-byte string by "cp"
		 * @param wstr	source Unicode string
		 * @param slen	source length
		 * @param cp	codename
		 * @param out	output string
		 * @param lout	output length
		 * @param strict	is strict mode
		 * @param bufsiz	convert buffer size (only Linux)
		 * @return _encoding_eror_t error info if errno
		 */
		inline _encoding_error_t wtoa(const wchar_t* wstr, const size_t slen,
			const wchar_t* cp,
			char** out, size_t* lout,
			const bool strict, const size_t bufsiz);
		
		template<size_t retlen>
		std::string to_asciistring(const wchar_t* wch)
		{
			char res[retlen]{};
			wcstombs(res, wch, retlen);
			return res;
		}
#if _CPPPRT_PLATFORM == CPPPRT_PLATFORM_WIN32
		inline _encoding_error_t atow(const char* str, const size_t slen,
			const wchar_t* cp,
			wchar_t** out, size_t* lout,
			const bool strict, const size_t bufsiz)
		{
			UINT code = _codepages::__cppp_encoding_getcp(cp);
			if (code == (UINT)-1)
			{
				return _encoding_error_t{ 0, _CPPPMSG_ERROR_INVALID_CP };//codepage name not found
			}
			if (slen == 0) { out = NULL; lout = 0; return {}; }
			int len = MultiByteToWideChar(code, 0, str, (int)slen, NULL, 0);
			wchar_t* wch = new wchar_t[(size_t)len + 1];
			int res = MultiByteToWideChar(code, 0, str, (int)slen, wch, len);
			if (res == 0 && strict)
			{
				delete[] wch;
				return _encoding_error_t{ (int)GetLastError(),NULL };
			}
			wch[len] = 0;
			*out = wch;
			*lout = (size_t)len;
			return {};
		}
		inline _encoding_error_t wtoa(const wchar_t* wstr, const size_t slen,
			const wchar_t* cp,
			char** out, size_t* lout,
			const bool strict, const size_t bufsiz)
		{
			UINT code = _codepages::__cppp_encoding_getcp(cp);
			if (code == (UINT)-1)
			{
				return { 0, _CPPPMSG_ERROR_INVALID_CP };//codepage name not found
			}
			if (slen == 0) { out = NULL; lout = 0; }//return { 0,NULL };}
			int len = WideCharToMultiByte(code, 0, wstr, (int)slen, NULL, 0, NULL, NULL);
			char* m_char = new char[(size_t)len + 1];
			int res = WideCharToMultiByte(code, 0, wstr, (int)slen, m_char, len, NULL, NULL);
			if (res == 0 && strict)
			{
				delete[] m_char;
				return _encoding_error_t{ (int)GetLastError(),NULL };
			}
			m_char[(size_t)len]=0;
			*out = m_char;
			*lout = (size_t)len;
			return {};
		}
#else
		namespace _iconv
		{
			template<typename T>
			_encoding_error_t convert(const char* from,const char* to,
				const bool strict,const size_t buf_size_,
				const char* in,const size_t inlen,
				T** out,size_t& outlen)
			{
				outlen = 0;
				iconv_t iconv_ = ::iconv_open(to, from);
				if (iconv_ == (iconv_t)(-1))
				{
					return { errno,L"iconv open error" };
				}
				const bool ignore_error_ = !strict;
				std::vector<char> in_buf(in, in+inlen);
				char* src_ptr = &in_buf[0];
				size_t src_size = inlen;
				//std::vector<char> buf(buf_size_);
				char* buf = new char[buf_size_] {};
				//std::string dst;
				std::vector<char> dst;
				while (0 < src_size) {
					char* dst_ptr = buf;
					size_t dst_size = buf_size_;
					size_t res = ::iconv(iconv_, &src_ptr, &src_size, &dst_ptr, &dst_size);
					if (res == (size_t)-1) {
						if (errno == E2BIG) {
							// ignore this error
						}
						else if (ignore_error_) {
							// skip character
							++src_ptr;
							--src_size;
						}
						else
						{
							int le = errno;
							if (le == EINVAL)
							{
								le = EILSEQ;
							}
							::iconv_close(iconv_);
							delete[] buf;
							return { le,NULL };
						}
					}
					for (size_t i = 0; i < buf_size_ - dst_size; i++)
					{
						dst.push_back(buf[i]);
						outlen++;
					}
					//dst.append(&buf[0], buf.size() - dst_size);
					//outlen += buf.size() - dst_size;
				}
				//dst.swap(output);
				::iconv_close(iconv_);
				char* pout = new char[dst.size() + sizeof(T)] {};
				for (size_t i = 0; i < dst.size(); i++)
				{
					pout[i] = buf[i];
				}
				*out = (T*)pout;
				return { 0,NULL };
			}
		}
		inline _encoding_error_t atow(const char* str, const size_t slen,
			const wchar_t* cp,
			wchar_t** out, size_t* lout,
			const bool strict, const size_t bufsiz)
		{
			size_t _lout;
			wchar_t* pout;
			_encoding_error_t ret=_iconv::convert(to_asciistring<20>(cp).c_str(), "WCHAR_T", strict, bufsiz,
				str, slen, &pout,_lout);
			*out =  pout;
			*lout = _lout / sizeof(wchar_t);
			return ret;
		}
		inline _encoding_error_t wtoa(const wchar_t* wstr, const size_t slen,
			const wchar_t* cp,
			char** out, size_t* lout,
			const bool strict,const size_t bufsiz)
		{
			char* pout;
			_encoding_error_t ret= _iconv::convert<char>("WCHAR_T", to_asciistring<20>(cp).c_str(), strict, bufsiz,
				(const char*)wstr, slen * sizeof(wchar_t), &pout, *lout);
			*out = pout;
			return ret;
		}
#endif
	}
}

#endif