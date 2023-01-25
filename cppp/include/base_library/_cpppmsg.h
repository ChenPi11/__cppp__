/**
 * @file include/base_library/_cpppmsg.h
 * @author ChenPi11
 * @copyright Copyright (C) 2023
 * @date 2023-1-10
 * @language C
 * @brief C++ Plus library messages
 * @version 1.0.0.0
 */
#ifndef _CPPPMSG_H_
#define _CPPPMSG_H_
//iconv.hpp



//_encoding.hpp
//iconv++ error msg

//C++ Plus error msg : unknown encoding
#define _CPPPMSG_ERROR_UNKNOWN_ENCODING L"Unknown encoding"
//C++ Plus error msg : invalid code page
#define _CPPPMSG_ERROR_INVALID_CP L"Invalid code page"
//C++ Plus error msg : iconv error
#define _CPPPMSG_ERROR_ICONV_ERROR L"iconv error"


//exception.hpp

#define _CPPPMSG_ERROR_IOError_DEFAULT_MSG L"I/O Error"
#define _CPPPMSG_ERROR_NullPointerError_DEFAULT_MSG L"Null pointer"
#define _CPPPMSG_ERROR_BadPointerError_DEFAULT_MSG L"Bad pointer"
#define _CPPPMSG_ERROR_IndexError_DEFAULT_MSG L"Bad Index"

//_memory.hpp

//C++ Plus error msg : malloc error
#define _CPPPMSG_ERROR_MALLOC_ERR L"malloc error"
//C++ Plus error msg : calloc error
#define _CPPPMSG_ERROR_CALLOC_ERR L"calloc error"
//C++ Plus error msg : realloc error
#define _CPPPMSG_ERROR_REALLOC_ERR L"realloc error"
//C++ Plus error msg : bad pointer
#define _CPPPMSG_ERROR_BAD_POINTER L"Bad pointer"


//bytes.hpp/string.hpp

//C++ Plus error msg : index out of range
#define _CPPPMSG_ERROR_INDEX_OUT_OF_RANGE L"Index out of range"
//C++ Plus error msg : null pointer
#define _CPPPMSG_ERROR_NULL_POINTER L"Null pointer"
#endif