// ============================================ //
//  math.h                                      //
//  Template MetaProgramming                    //
//                                              //
//  /* Meta functions */                        //
//  is_true                                     //
//  add                                         //
//  subtract                                    //
//  multiply                                    //
//  divide                                      //
//  remaind                                     //
//  bw_and                                      //
//  bw_or                                       //
//  compare                                     //
//  is_prime                                    //
//  power                                       //
//  factorial                                   //
//  fibonacchi                                  //
//  p_int                                       //
//  n_int                                       //
//  g_int                                       //
//  s_int                                       //
//                                              //
//  Created by MacBook Pro on 2019/06/19.       //
//  Copyright © 2019 물방울. All rights reserved. //
// ============================================ //

#ifndef math_h
#define math_h

#include "type_traits.h"


/* is_true */
template <bool expr>
struct is_true { enum { value = (expr == true) }; };

/* add */
template <int left, int right>
struct add { enum { value = (left + right) }; };

/* subtract */
template <int left, int right>
struct subtract { enum { value = (left - right) }; };

/* multiply */
template <int left, int right>
struct multiply { enum { value = (left * right) }; };

/* divide */
template <int left, int right>
struct divide { enum { value = (left / right) }; };

/* remind */
template <int left, int right>
struct remaind { enum { value = (left % right) }; };

/* bw_and */
template <int left, int right>
struct bw_and { enum { value = (left & right) }; };

/* bw_or */
template <int left, int right>
struct bw_or { enum { value = (left | right) }; };

/* compare */
template <int left, int right>
struct compare { enum { value = ((left < right) ? left : right) }; };

/* is_prime */
template <int val, int index>
struct is_prime_base { enum { value = (val % index == 0) || is_prime_base<val, index+1>::value }; };
template <int val>
struct is_prime_base<val, val/2> { enum { value = val % (val/2) == 0 }; };
template <int val>
struct is_prime { enum { value = !is_prime_base<val, 2>::value }; };
template <>
struct is_prime<2> : true_type {};
template <>
struct is_prime<3> : true_type {};

/* power */
template <int base, int exponent>
struct power { enum { value = base * power<base, exponent-1>::value }; };
template <int base>
struct power<base, 0> { enum { value = 1 }; };

/* factorial */
template <int val>
struct factorial { enum { value = val * factorial<val-1>::value }; };
template <>
struct factorial<0> { enum { value = 1 }; };

/* fibonacchi */
template <int index>
struct fibonacchi { enum { value = fibonacchi<index-1>::value + fibonacchi<index-2>::value }; };
template <>
struct fibonacchi<1> { enum { value = 1 }; };
template <>
struct fibonacchi<0> { enum { value = 0 }; };

/* positive int */
template <int val, int std, bool cmp>
struct __int_base { enum { value = val }; };
template <int val, int std>
struct __int_base<val, std, false> { enum { value = std }; };
template <int val>
struct p_int : __int_base<val, 0, (val>0)> {};

/* negative int */
template <int val>
struct n_int : __int_base<val, 0, (val<0)> {};

/* greater than int */
template <int val, int std>
struct g_int : __int_base<val, std, (val>std)> {};

/* smaller than int */
template <int val, int std>
struct s_int : __int_base<val, std, (val<std)> {};

#endif /* math_h */
