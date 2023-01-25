/**
 * @file include/base_library/_cpppinclude.h
 * @author ChenPi11
 * @copyright Copyright (C) 2023
 * @date 2023-1-10
 * @language C++
 * @brief C++ Plus base library includes
 * @version 1.0.0.0
 */
#ifndef _CPPP_INCLUDE_H_
#define _CPPP_INCLUDE_H_

//C/C++ defines
//#define _CRT_SECURE_NO_WARNINGS

#if _WIN32
//Windows include
#ifdef _AFXDLL
//MFC include
#include <afxwin.h>
#else
//WINAPI include
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif
#else
//Linux include

#ifndef CPPP_USE_LIBICONV
#include <iconv.h>
#else
#include <libiconv.h>
#endif

#ifdef __cplusplus
#include <codecvt>
#include <cstring>
#include <locale>
#include <string>

#endif
#endif

//C include
#include <errno.h>
#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <malloc.h>

//C++ include
#ifdef __cplusplus
#include <iostream>
#include <vector>
#include <exception>
#include <set>
#include <algorithm>
#include <initializer_list>
#include <sstream>
#include <type_traits>
#include <map>
#endif

//C++ Plus include
#include "_platform.h"
#include "_cpppmsg.h"
#include "_cpppsal.h"

//C++ Plus defines
# ifndef _CONSTEXPR20
#    if _HAS_CXX20
#        define _CONSTEXPR20 constexpr
#    else
#        define _CONSTEXPR20 inline
#    endif
# endif
# ifndef __cplusplus
#	define constexpr
# endif
# ifndef _NODISCARD
#	if _HAS_CXX17
#		define _NODISCARD [[nodiscard]]
#	else
#		define _NODISCARD
#	endif
# endif
# ifdef _MAC
#	ifndef wchar_t
#		define unsigned short wchar_t // some Macintosh compilers don't define wchar_t in a convenient location, or define it as a char
#	endif
# endif
#endif