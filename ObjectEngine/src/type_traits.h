// ============================================ //
//  type_traits.h                               //
//  Template MetaProgramming                    //
//                                              //
//  /* Meta types */                            //
//  true_type                                   //
//  false_type                                  //
//  value_type                                  //
//                                              //
//  /* Meta functions */                        //
//  remove_const                                //
//  is_same                                     //
//  is_void                                     //
//  is_null_pointer                             //
//  is_integral                                 //
//  is_floating_point                           //
//  is_arithmetic                               //
//  is_fundamental                              //
//  is_compound                                 //
//  is_pointer                                  //
//  is_reference                                //
//  is_const                                    //
//  is_volatile                                 //
//  is_signed                                   //
//  is_unsigned                                 //
//  is_member_pointer                           //
//  is_array                                    //
//                                              //
//  Created by MacBook Pro on 2019/06/11.       //
//  Copyright © 2019 물방울. All rights reserved. //
// ============================================ //

#ifndef type_traits_h
#define type_traits_h

#include <cstddef>


/* true_type, false_type */
struct true_type  { enum _value_ {value = true }; };
struct false_type { enum _value_ {value = false}; };

/* remove const */
template <typename T>
struct remove_const { typedef T type; };
template <typename T>
struct remove_const<const T> { typedef T type; };

/* value_type */
template <bool _value = false>
struct value_type : false_type {};
template <>
struct value_type<true> : true_type {};

/* is_same */
template <typename T1, typename T2>
struct is_same : false_type {};
template <typename T>
struct is_same<T, T> : true_type {};

/* is_void */
template <typename T>
struct is_void : is_same<typename remove_const<T>::type, void> {};

/* is_null_pointer */
template <typename T>
struct is_null_pointer : is_same<typename remove_const<T>::type, std::nullptr_t> {};

/* is_integral */
template <typename T>
struct is_integral_base : false_type {};
template <typename T>
struct is_integral : is_integral_base<typename remove_const<T>::type> {};
#define _INTEGRAL_SPECIALIZATION_(x) template <> struct is_integral_base<x> : true_type {}
_INTEGRAL_SPECIALIZATION_(signed int);
_INTEGRAL_SPECIALIZATION_(signed short);
_INTEGRAL_SPECIALIZATION_(signed long);
_INTEGRAL_SPECIALIZATION_(signed long long);
_INTEGRAL_SPECIALIZATION_(unsigned int);
_INTEGRAL_SPECIALIZATION_(unsigned short);
_INTEGRAL_SPECIALIZATION_(unsigned long);
_INTEGRAL_SPECIALIZATION_(unsigned long long);

/* is_floating_point */
template <typename T>
struct is_floating_point_base : false_type {};
template <typename T>
struct is_floating_point : is_floating_point_base<typename remove_const<T>::type> {};
#define _FLOATING_POINT_SPECIALIZATION_(x) template <> struct is_floating_point_base<x> : true_type {}
_FLOATING_POINT_SPECIALIZATION_(float);
_FLOATING_POINT_SPECIALIZATION_(double);
_FLOATING_POINT_SPECIALIZATION_(long double);

/* is_arithmetic */
template <typename T>
struct is_arithmetic : value_type<is_integral<T>::value || is_floating_point_base<T>::value> {};

/* is_fundamental */
template <typename T>
struct is_fundamental : value_type<is_arithmetic<T>::value || is_null_pointer<T>::value || is_void<T>::value> {};

/* is_compound */
template <typename T>
struct is_compound : value_type<!is_fundamental<T>::value> {};

/* is_pointer */
template <typename T>
struct is_pointer_base : false_type {};
template <typename T>
struct is_pointer_base<T*> : true_type {};
template <typename T>
struct is_pointer : is_pointer_base<typename remove_const<T>::type> {};

/* is_reference */
template <typename T>
struct is_reference : false_type {};
template <typename T>
struct is_reference<T&> : true_type {};
template <typename T>
struct is_reference<T&&> : true_type {};

/* is_const */
template <typename T>
struct is_const : false_type {};
template <typename T>
struct is_const<const T> : true_type {};

/* is_volatile */
template <typename T>
struct is_volatile : false_type {};
template <typename T>
struct is_volatile<volatile T> : true_type {};

/* is_signed */
template <typename T, bool _is_arithmetic = is_arithmetic<T>::value>
struct is_signed_base : value_type<T(-1) < T(0)> {};
template <typename T>
struct is_signed_base<T, false> : false_type {};
template <typename T>
struct is_signed : is_signed_base<T> {};

/* is_unsigned */
template <typename T, bool _is_arithmetic = is_arithmetic<T>::value>
struct is_unsigned_base : value_type<T(0) < T(-1)> {};
template <typename T>
struct is_unsigned_base<T, false> : false_type {};
template <typename T>
struct is_unsigned : is_unsigned_base<T> {};

/* is_member_pointer */
template <typename T>
struct is_member_pointer_base : false_type {};
template <typename T, typename U>
struct is_member_pointer_base<T U::*> : true_type {};
template <typename T>
struct is_member_pointer : is_member_pointer_base<typename remove_const<T>::type> {};

/* is_array */
template <typename T>
struct is_array : false_type {};
template <typename T>
struct is_array<T[]> : true_type {};
template <typename T, std::size_t arrSize>
struct is_array<T[arrSize]> : true_type {};

#endif /* type_traits_h */

