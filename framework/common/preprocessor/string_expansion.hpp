// Copyright (C) 2012 iwg molw5
// For conditions of distribution and use, see copyright notice in COPYING

/**
* \file
* \brief Template string expansion macros.
*
* \copyright
* Copyright &copy; 2012 iwg molw5<br>
* For conditions of distribution and use, see copyright notice in COPYING
*/

#pragma once

#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>

namespace framework
{
    namespace detail
    {
        template <unsigned int N>
        constexpr char extract_char (char const (&string) [N], unsigned int index)
        {
            return index < N ? string[index] : '\0';
        }
    }
}

#define EXPAND_STRING_N_IMPL(z, n, data) \
        BOOST_PP_COMMA_IF(n) framework::detail::extract_char(data, n)

/**
* \headerfile string_expansion.hpp <framework/common/preprocessor/string_expansion.hpp>
* \brief Expand string literal to char... pack.
*
* Expands a string literal to a sequence of \c LENGTH characters suitable for use in 
* \c char... template parameter pack.  Characters beyond the end of the string are
* converted to \c '\0' characters.  For example, the following are equivalent:
* \code
* template <char...>
* struct S;
*
* S <'H', 'e', 'l', 'l', 'o', ',', 'w', 'o', 'r', 'l', 'd', '!'> x;
* S <EXPAND_STRING("Hello World!", 12)> x;
*
* \brief LENGTH maximum string length
* \brief STRING string literal
*/
#define EXPAND_STRING_N(STRING, LENGTH) \
        BOOST_PP_REPEAT(LENGTH, EXPAND_STRING_N_IMPL, STRING)
