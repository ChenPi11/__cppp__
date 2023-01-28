#pragma once
#ifndef _CPPP_TYPES_SLN_STRING_HPP_
#define _CPPP_TYPES_SLN_STRING_HPP_
#include "string.hpp"
#include "exception.hpp"
void mv(wchar_t* v,size_t x)
{
	for(size_t i=0;i<x;i++)
	{
		std::wcout << i << "\t" << (int)v[i]<<"\t";
		std::wcout<<(v[i]);
		std::wcout << "\n";
	}
}

_cpppbase::types::String::String() noexcept =default;

_cpppbase::types::String::String(_In_ size_t __len, _In_reads_or_z_(__len) wchar_t* __data)
{
	_data = __data; _len = __len;
}

_cpppbase::types::String::String(_In_z_count_(srclen) const wchar_t* src, _In_ const size_t srclen) noexcept : _cpppbase::types::String::String(srclen, cppp_copy_z(srclen, src)) {}

_cpppbase::types::String::String(_In_ const String& src) noexcept :
	_cpppbase::types::String::String(src._data, src._len) {}

_cpppbase::types::String::String(_In_z_ const wchar_t* src) noexcept :
	_cpppbase::types::String::String(src,wcslen(src)) {}

_cpppbase::types::String::String(_In_ const std::wstring& src) noexcept :
	_cpppbase::types::String::String(src.c_str(),src.length()) {}

_cpppbase::types::String::String(_In_ const std::string& src, _In_ const std::wstring encoding, _In_ const bool strict,_In_ const size_t bufsiz) : 
	_cpppbase::types::String::String(src.c_str(),src.length(),encoding,strict,bufsiz) {}

_cpppbase::types::String::String(_In_z_count_(srclen) const char* src, _In_ const size_t srclen, _In_ const std::wstring encoding, _In_ const bool strict, _In_ const size_t bufsiz)
{
	auto err = _cpppbase::_encoding::atow(src, srclen, encoding.c_str(), &_data, &_len, strict, bufsiz);
	if (err.eno != 0 || err.msg != NULL)
	{
#if _CPPPRT_PLATFORM == CPPPRT_PLATFORM_WIN32
		throw _cpppbase::builtins::UnicodeDecodeError(String(err.msg), Errno(err.eno, true));
#else
		throw _cpppbase::builtins::UnicodeDecodeError(String(err.msg), Errno(err.eno, false));
#endif
	}
}

_cpppbase::types::String::~String() noexcept
{
	delete[] _data;
}

_Ret_maybenull_ _CPPP_CONSTEXPR14 wchar_t* _cpppbase::types::String::data() const noexcept
{
	return _data;
}

_Ret_z_ inline _CPPP_CONSTEXPR14 const wchar_t* _cpppbase::types::String::c_str() const noexcept
{
	return _len==0?L"":_data;
}

inline _CPPP_CONSTEXPR14 size_t _cpppbase::types::String::len() const noexcept
{
	return _len;
}

inline _CPPP_CONSTEXPR14 size_t _cpppbase::types::String::length() const noexcept
{
	return _len;
}

inline _CPPP_CONSTEXPR14 size_t _cpppbase::types::String::size() const noexcept
{
	return _len;
}

std::wstring _cpppbase::types::String::__str__() const noexcept
{
	return std::wstring(_data, _len);
}

void _cpppbase::types::String::assign(_In_z_count_(srclen) wchar_t* src, _In_ const size_t srclen) noexcept
{
	delete[] _data; _data = src; _len = srclen;
}

wchar_t& _cpppbase::types::String::at(_In_ const size_t off) const
{
	if (off >= _len)
	{
		throw _cpppbase::builtins::IndexError(_CPPPMSG_ERROR_INDEX_OUT_OF_RANGE);
	}
	return _data[off];
}

std::wstring _cpppbase::types::String::__repr__() const
{
	if (_len)
	{
		size_t olen;
		wchar_t* r=wsrepr(_data, _len, olen);
		std::wstring res(r, olen);
		delete[] r;
		return res;
	}
	return std::wstring(_c_string(L"\"\""));// ""
}

_cpppbase::types::String _cpppbase::types::String::capitalize() const
{
	String res;
	if (_len)
	{
		wchar_t* rd = cppp_copy_z(_len, _data);
		rd[0] = towupper(rd[0]);
		for (size_t i = 0; i < _len; i++)
		{
			rd[i] = towlower(rd[i]);
		}
		res.assign(rd, _len);
	}
	return res;
}

_cpppbase::types::String _cpppbase::types::String::center(_In_ const size_t width, _In_ const wchar_t fill) const
{
	if (width <= _len)
	{
		return String(*this);
	}
	size_t begin_chars = (width - _len) / 2;
	wchar_t* res = new wchar_t[width+1];
	res[width] = L'\0';
	for (size_t i = 0; i < begin_chars; i++)
	{
		res[i] = fill;//begins
	}
	for (size_t i = 0; i < _len; i++)
	{
		res[i + begin_chars] = _data[i];//texts
	}
	for (size_t i = begin_chars + _len; i < width; i++)
	{
		res[i] = fill;//ends
	}
	return String(width, res);
}


template<size_t srclen>
_cpppbase::types::String::String(const wchar_t(&src)[srclen]) noexcept :
	_cpppbase::types::String::String(src,srclen) {}



_cpppbase::types::String _cpppbase::types::String::operator+(_In_ const String& s2) const
{
	wchar_t* buf = new wchar_t[_len + s2._len+1];
	buf[_len + s2._len] = L'\0';
	for (size_t i = 0; i < _len; i++)
	{
		buf[i] = _data[i];
	}
	wchar_t* _ = buf + _len;
	for (size_t i = 0; i < s2._len; i++)
	{
		_[i] = s2._data[i];
	}
	return String(_len + s2._len, buf);
}

_cpppbase::types::String& _cpppbase::types::String::operator=(_In_ const String& s2)
{
	assign(cppp_copy_z(s2._len, s2._data),s2._len);
	return *this;
}

_cpppbase::types::String::operator std::wstring() const noexcept
{
	return __str__();
}

#endif