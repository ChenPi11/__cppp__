/**
 * @file include/base_library/cppptypes/baseclass.hpp
 * @author ChenPi11
 * @copyright Copyright (C) 2023
 * @date 2023-1-15
 * @language C++
 * @brief C++ Plus Type class 
 */
#ifndef _CPPP_TYPES_BASE_CLASS_HPP_
#define _CPPP_TYPES_BASE_CLASS_HPP_
#include "../_cpppinclude.h"
#include "../_encoding.hpp"
namespace _cpppbase
{
    namespace types
    {
        namespace gettype
        {
            /**
             * @date 2023-1-18
             * @brief get type name
             * @tparam T type
             * @return const wchar_t* const name
             */
            template<typename T>
            constexpr const wchar_t* const gty()
            {
                return  (std::is_class_v<T>)    ? L"class"      :
                        (std::is_union_v<T>)    ? L"value"      :
                        (std::is_pointer_v<T>)  ? L"pointer"    :
                        (std::is_enum_v<T>)     ? L"enum"       :
                        (std::is_array_v<T>)    ? L"array"      :
                        (std::is_void_v<T>)     ? L"void"       :
                        (std::is_function_v<T>) ? L"function"   :
                                                  L"type";
            }
        }
        /**
         * @date 2023-1-18
         * @brief C++ Plus Type class
         */
        class Type
        {
        public:
            /**
             * @date 2023-1-18
             * @brief C++ Plus Type class default construct method
             */
            Type() noexcept = default;
            /**
             * @date 2023-1-18
             * @brief C++ Plus Type class construct method
             * @tparam T type
             */
            template<typename T>
            Type(const T&)
            {
                set<T>();
            }
            //raw text
            std::wstring __raw__;
            //multi-bytes raw string
            std::string __braw__;
            //multi-bytes name string
            std::string __bname__;
            //name text
            std::wstring __name__;
            //type text
            std::wstring __type__;
            //typeid hash
            size_t __hash__ = 0;
            /**
             * @date 2023-1-18
             * @brief set Type data
             * @tparam Ty type
             */
            template<typename Ty>
            inline Type& set() noexcept
            {
                __hash__ = typeid(Ty).hash_code();
                __bname__ = typeid(Ty).name();
#if _CPPPRT_PLATFORM == CPPPRT_PLATFORM_WIN32
                __braw__ = typeid(Ty).raw_name();
#else
                __braw__ = __bname__;
#endif
                wchar_t* out;
                size_t lout;
                auto e=_cpppbase::_encoding::atow(__bname__.c_str(),__bname__.size(),L"utf-8",&out,&lout,false,BUFSIZ);
                if(!(e.eno || e.msg))
                {
                    __type__.assign(gettype::gty<Ty>());
                    __name__.assign(out, lout);
                }
                e=_cpppbase::_encoding::atow(__braw__.c_str(),__braw__.size(),L"utf-8",&out,&lout,false,BUFSIZ);
                if(!(e.eno || e.msg))
                {
                    __raw__.assign(out,lout);
                }
                return *this;
            }
            /**
             * @date 2023-1-18
             * @brief set Type data
             * @tparam Ty type
             * @param [arg1] infer source
             * @return Type& self
             */
            template<typename Ty>
            inline Type& set(const Ty&) noexcept
            {
                return set<Ty>();
            }
            /**
             * @date 2023-1-18
             * @brief get repr text
             * @return std::wstring repr text
             */
            std::wstring __repr__() const noexcept
            {
                return L"<" + __type__ + L" \"" + __name__ + L"\" " + __raw__ + L">";
            }
            /**
             * @date 2023-1-18
             * @brief get multi-bytes name string
             * @return std::string string
             */
            _CONSTEXPR20 operator std::string() const noexcept{ return __bname__; }
            /**
             * @date 2023-1-18
             * @brief get name text
             * @return std::wstring text
             */
            _CONSTEXPR20 operator std::wstring() const noexcept { return __name__; }
            /**
             * @date 2023-1-18
             * @brief get type hash
             * @return size_t hash
             */
            constexpr operator size_t() const noexcept { return __hash__; }
            /**
             * @date 2023-1-18
             * @brief compare Type
             * @param other other object
             * @return bool result
             */
            inline bool operator==(const Type& other) const noexcept
            {
                return __braw__ == other.__braw__;
            }
            /**
             * @date 2023-1-18
             * @brief other not equ self
             * @param other other object
             * @return bool result
             */
            inline bool operator!=(const Type& other) const noexcept
            {
                return __braw__ != other.__braw__;
            }
            /**
             * @date 2023-1-18
             * @brief set type info
             * @param other source type info
             * @return Type& self
             */
            inline Type& operator=(const Type& other) noexcept
            {
                __raw__ = other.__raw__;
                __braw__ = other.__braw__;
                __bname__ = other.__bname__;
                __name__ = other.__name__;
                __type__ = other.__type__;
                __hash__ = other.__hash__;
                return *this;
            }
        };
    }
}
#endif