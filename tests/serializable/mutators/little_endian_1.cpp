// Copyright (C) 2012 iwg molw5
// For conditions of distribution and use, see copyright notice in COPYING

#include <iostream>
#include <sstream>
#include <UnitTest++/UnitTest++.h>

#include <framework/serializable/inline_object.hpp>
#include <framework/serializable/containers/value.hpp>
#include <framework/serializable/mutators/little_endian.hpp>
#include <framework/serializable/common_macros.hpp>

SUITE(framework_serializable_mutators_little_endian_hpp_1)
{
    TEST(Basic)
    {
        using namespace framework::serializable;

        inline_object <
            value <NAME("Field 1"), uint16_t>,
            value <NAME("Field 2"), little_endian <uint16_t>>
        > in {0x0102, 0x0102};

        inline_object <
            value <NAME("Field 1"), uint16_t>,
            value <NAME("Field 2"), uint16_t>
        > out;

        std::stringstream ss;
        CHECK(write(in, ss));
        CHECK(read(ss, out));
        CHECK(in.get <NAME("Field 1")> () == out.get <NAME("Field 1")> ());
        CHECK(in.get <NAME("Field 2")> () == out.get <NAME("Field 2")> ());
    }

    TEST(Nested)
    {
        using namespace framework::serializable;

        inline_object <
            value <NAME("Field 1"), little_endian <little_endian <uint16_t>>>
        > in {0x0102};

        inline_object <
            value <NAME("Field 1"), uint16_t>
        > out;

        std::stringstream ss;
        CHECK(write(in, ss));
        CHECK(read(ss, out));
        CHECK(in.get <NAME("Field 1")> () == out.get <NAME("Field 1")> ());
    }
}
