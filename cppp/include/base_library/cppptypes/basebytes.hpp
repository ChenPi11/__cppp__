/**
 * @file include/base_library/cppptypes/basebytes.hpp
 * @author ChenPi11
 * @copyright Copyright (C) 2023
 * @date 2023-1-16
 * @language C++
 * @brief C++ Plus Bytes type base
 */
#ifndef _CPPP_TYPES_BASE_BYTES_HPP_
#define _CPPP_TYPES_BASE_BYTES_HPP_

#include <cstdio>
namespace _cpppbase
{
	namespace types
	{
		/**
		 * @date 2023-1-15
		 * @brief C++ Plus Byte
		 */
		using Byte = unsigned char;
		/**
		 * @date 2023-1-15
		 * @brief C++ Plus BaseBytes
		 */
		class BaseBytes
		{
		public:
			//construct
			BaseBytes() = default;
			//deconstruct
			~BaseBytes() = default;
		protected:
			//data
			Byte* _data;
			//length
			size_t _len;
			//construct
			BaseBytes(size_t __len, Byte* __data) : _data(__data), _len(__len) {}
		};
	}
}
#endif