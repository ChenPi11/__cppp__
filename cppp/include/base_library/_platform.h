/**
 * @file include/base_library/_platform.h
 * @author ChenPi11
 * @copyright Copyright (C) 2023
 * @date 2023-1-8
 * @language C
 * @brief C++ Plus platform infomation defines
 * @version 1.0.0.0
 */
#ifndef _CPPP_BASELIB_PLATFORM_H_
#define _CPPP_BASELIB_PLATFORM_H_

//C++ Plus Runtime platform is Linux
#define CPPPRT_PLATFORM_LINUX 0
//C++ Plus Runtime platform is Win32
#define CPPPRT_PLATFORM_WIN32 1
//C++ Plus Runtime platform is Darwin
#define CPPPRT_PLATFORM_DARWIN 2
//C++ Plus Runtime platform is Unix
#define CPPPRT_PLATFORM_UNIX 3
//C++ Plus Runtime platform is Android
#define CPPPRT_PLATFORM_ANDROID 4
//Unknown C++ Plus Runtime platform
#define CPPPRT_PLATFORM_UNKNOWN 255


#if defined(_WIN32)
//you are in Win32
#define _CPPPRT_PLATFORM CPPPRT_PLATFORM_WIN32
#elif defined(__ANDROID__)
//you are in Android
#define _CPPPRT_PLATFORM CPPPRT_PLATFORM_ANDROID
#elif defined(__linux__)
//you are in Linux
#define _CPPPRT_PLATFORM CPPPRT_PLATFORM_LINUX
#elif defined(__APPLE__)
//you are in Apple
#define _CPPPRT_PLATFORM CPPPRT_PLATFORM_DARWIN
#elif defined(_UNIX)
//you are in Unix
#define _CPPPRT_PLATFORM CPPPRT_PLATFORM_UNIX
#else
//you are in unknown OS
#define _CPPPRT_PLATFORM CPPPRT_PLATFORM_UNKNOWN
#endif

#ifdef _DEBUG
//This C++ Plus program is in Debug mode (only MSVC)
#define _CPPPRT_PLATFORM_DEBUG 1
#else
//This C++ Plus program is in Release mode (only MSVC)
#define _CPPPRT_PLATFORM_DEBUG 0
#endif

//This C++ Plus program compiled by MSVC
#define CPPPRT_PLATFORM_COMPILER_MSVC 0
//This C++ Plus program compiled by GCC
#define CPPPRT_PLATFORM_COMPILER_GCC 1
//This C++ Plus program compiled by BORLANDC
#define CPPPRT_PLATFORM_COMPILER_BORLANDC 2
//This C++ Plus program compiled by clang
#define CPPPRT_PLATFORM_COMPILER_CLANG 3
//This C++ Plus program compiled by unknown compiler
#define CPPPRT_PLATFORM_COMPILER_OTHER 255

#if defined(_MSC_VER)
#define _CPPPRT_PLATFORM_COMPILER CPPPRT_PLATFORM_COMPILER_MSVC
#elif defined(__BORLANDC__)
#define _CPPPRT_PLATFORM_COMPILER CPPPRT_PLATFORM_COMPILER_BORLANDC
#elif defined(__clang__)
#define _CPPPRT_PLATFORM_COMPILER CPPPRT_PLATFORM_COMPILER_CLANG
#elif defined(__GNUC__)
#define _CPPPRT_PLATFORM_COMPILER CPPPRT_PLATFORM_COMPILER_GCC
#else
#define _CPPPRT_PLATFORM_COMPILER CPPPRT_PLATFORM_COMPILER_OTHER
#endif

//The architecture of this C++ Plus program is X86
#define CPPPRT_PLATFORM_ARCH_X86 0
//The architecture of this C++ Plus program is ARM
#define CPPPRT_PLATFORM_ARCH_ARM 1
//The architecture of this C++ Plus program is other architecture
#define CPPPRT_PLATFORM_ARCH_OTHER 255

#if defined(_M_IX86) || defined(_M_X64) || defined(__x86_64__)
#define _CPPPRT_PLATFORM_ARCH CPPPRT_PLATFORM_ARCH_X86
#elif defined(__arm__) || defined(__arm64__) || defined(__aarch64__)
#define _CPPPRT_PLATFORM_ARCH CPPPRT_PLATFORM_ARCH_ARM
#else
#define _CPPPRT_PLATFORM_ARCH CPPPRT_PLATFORM_ARCH_OTHER
#endif


#ifndef __POINTER_WIDTH__
#if defined(__arm64__) || defined(__aarch64__) || defined(_M_X64) || defined(__x86_64__)
//This is a 64 bit program
#define __POINTER_WIDTH__ 64
#define __POINTER_TYPE__ unsigned long long//pointer is int64
#else
//This is a 32 bit program
#define __POINTER_WIDTH__ 32
#define __POINTER_TYPE__ unsigned long//pointer is int32
#endif
#endif

#if __POINTER_WIDTH__ == 64
//This is a 64 bit program
#define __64arch__
#endif

#if _CPPPRT_PLATFORM_ARCH != CPPPRT_PLATFORM_ARCH_X86
#define __fastcall
#endif

#if defined(_MSVC_LANG) && !defined(_CRT_SECURE_NO_WARNINGS)
//This C++ Plus program doesn't use C Runtime Secure no warning
#define _CPPPRT_CRT_SECURE_NO_WARNINGS 0
#else
//This C++ Plus program use C Runtime Secure no warning
#define _CPPPRT_CRT_SECURE_NO_WARNINGS 1
#endif


//fix MSVC __cplusplus==199711L
#ifdef _MSVC_LANG
//MSVC C++ Plus
#define __CPPP_CPPVER _MSVC_LANG
#else
#ifndef __cplusplus
//C
#define __CPPP_CPPVER 0L
#else
//C++ Plus C++ Version
#define __CPPP_CPPVER __cplusplus
#endif
#endif

//C++03
#define __CPPP_CPPVER_CXX03 199711L
//C++11
#define __CPPP_CPPVER_CXX11 201103L
//C++14
#define __CPPP_CPPVER_CXX14 201402L
//C++17
#define __CPPP_CPPVER_CXX17 201703L
//C++20
#define __CPPP_CPPVER_CXX20 202002L

#if __CPPP_CPPVER >=__CPPP_CPPVER_CXX14
#define _CPPP_CONSTEXPR14 constexpr
#else
#define _CPPP_CONSTEXPR14
#endif

#if __CPPP_CPPVER <=__CPPP_CPPVER_CXX11
#define _CPPP_CONSTEXPR11 constexpr
#else
#define _CPPP_CONSTEXPR11
#endif

#ifndef __cplusplus
#define nullptr (void*)0
#endif



#endif