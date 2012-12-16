// Copyright (C) 2012 iwg molw5
// For conditions of distribution and use, see copyright notice in COPYING

/**
* \file
* \brief Common STL string aliases.
*
* \copyright
* Copyright &copy; 2012 iwg molw5<br>
* For conditions of distribution and use, see copyright notice in COPYING
*/

#pragma once

#pragma once

#include <string>

#include <framework/serializable/mutators/variable_container.hpp>
#include <framework/serializable/mutators/terminated.hpp>

namespace framework
{
    namespace serializable
    {
        /**
        * \brief Common STL string specification.
        */
        template <typename Size>
        using stl_string = variable_container <Size, char, std::string>;

        /**
        * \brief Common STL string specification, null terminated.
        */
        template <typename Size>
        using stl_null_string = terminated <char, '\0', std::string>;

        /**
        * \brief Common STL wstring specification.
        */
        template <typename Size>
        using stl_wstring = variable_container <Size, little_endian <wchar_t>, std::wstring>;

        /**
        * \brief Common STL wstring specification, null terminated.
        */
        template <typename Size>
        using stl_null_wstring = terminated <little_endian <wchar_t>, L'\0', std::wstring>;
    }
}
