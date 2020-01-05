#include <dynamic_library/math_function.h>

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

TEST_CASE("simple")
{
    Math math;
    auto res = math.add(5, 5);

    REQUIRE(res == 10);
}