/**
 * @file include/base_library/cppptypes/baseobject.hpp
 * @author ChenPi11
 * @copyright Copyright (C) 2023
 * @date 2023-1-15
 * @language C++
 * @brief C++ Plus Object type base
 */
#ifndef _CPPP_TYPES_BASE_OBJECT_HPP_
#define _CPPP_TYPES_BASE_OBJECT_HPP_

#include "../_cpppinclude.h"
#include "../_encoding.hpp"
#include "baseclass.hpp"
namespace _cpppbase
{
	namespace types
	{
		/**
		 * @date 2023-1-15
		 * @brief set object class name
		 * @param name class name
		 */
#		define cppp_setclass(name) private:

		/**
		 * @date 2023-1-17
		 * @brief define a C++ Plus derive class
		 * @param name class name
		 * @param derive father class
		 */
#		define cppp_begin_derive_class(name,derive) class name :public _cpppbase::types::Object ,derive { cppp_setclass(name)	//别问，就是没括号

		/**
		 * @date 2023-1-17
		 * @brief define a C++ Plus class
		 * @param name class name
		 * @param derive father class
		 */
#		define cppp_begin_class(name) class name :public _cpppbase::types::Object { cppp_setclass(name)	//别问，就是没括号
		
		/**
		 * @date 2023-1-15
		 * @brief C++ Plus class end
		 */
#		define cppp_end_class };
		
		/**
		 * @date 2023-1-15
		 * @brief get object class name
		 * @tparam ObjectClass cppp object type template
		 * @return class name
		 * @pre only C++ Plus class!!!
		 */
		template<typename ObjectClass>
		constexpr std::wstring _get_obj_cls(const ObjectClass&) noexcept
		{
			Type t;
			t.set<ObjectClass>();
			return t.__name__;
		}

		/**
		 * @date 2023-1-15
		 * @brief C++ Plus Object
		 */
		class Object
		{
			cppp_setclass(Object)
		public:
		};

		namespace templates
		{
			/**
			 * @date 2023-1-18
			 * @brief class has __repr__ function
			 * @tparam T class
			 * @return value result
			 */
			template<typename T> struct class_has_repr
			{
			private:
				//check (has)
				template<typename U> static auto Check(int) -> decltype(std::declval<U>().__repr__(), std::true_type());
				//check (not)
				template<typename U> static auto Check(...) -> decltype(std::false_type());
			public:
				//result
				static const bool value = std::is_same<decltype(Check<T>(0)), std::true_type>::value;
			};
			/**
			 * @date 2023-1-18
			 * @brief class has __str__ function
			 * @tparam T class
			 * @return value result
			 */
			template<typename T> struct class_has_str
			{
			private:
				//check (has)
				template<typename U> static auto Check(int) -> decltype(std::declval<U>().__str__(), std::true_type());
				//check (not)
				template<typename U> static auto Check(...) -> decltype(std::false_type());
			public:
				//result
				static const bool value = std::is_same<decltype(Check<T>(0)), std::true_type>::value;
			};
		}

		/**
		 * @date 2023-1-18
		 * @brief get object printable string
		 * @tparam T class
		 * @return printable string
		 */
		template<typename T, 
				typename std::enable_if<templates::class_has_repr<T>::value, T>::type* = nullptr>
		std::wstring repr(const T& t)
		{
			return t.__repr__();
		};
		/**
		 * @date 2023-1-18
		 * @brief get object printable string
		 * @tparam T class
		 * @return printable string
		 */
		template<typename T, 
				typename std::enable_if<!templates::class_has_repr<T>::value, T>::type* = nullptr,
				typename std::enable_if<std::is_base_of<Object,T>::value,T>::type* = nullptr
				>
		std::wstring repr(const T& t)
		{
			return std::wstring(L"<")+
					_get_obj_cls<T>(t)+L" object at "+
					std::to_wstring((__POINTER_TYPE__)(void*)&t)
					+ L">";
		}
		
		/**
		 * @date 2023-1-18
		 * @brief object to string
		 * @tparam T class
		 * @return printable string
		 */
		template<typename T,
			typename std::enable_if<templates::class_has_str<T>::value, T>::type* = nullptr>
		std::wstring str(const T& t)
		{
			return t.__str__();
		};
		/**
		 * @date 2023-1-18
		 * @brief object to string
		 * @tparam T class
		 * @return printable string
		 */
		template<typename T,
			typename std::enable_if<!templates::class_has_str<T>::value, T>::type* = nullptr,
			typename std::enable_if<std::is_base_of<Object, T>::value, T>::type* = nullptr
		>
		std::wstring str(const T& t)
		{
			return repr<T>(t);
		}

	}
}

#endif