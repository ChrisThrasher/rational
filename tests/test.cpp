#include <catch2/catch_template_test_macros.hpp>
#include <complex>
#include <rational/rational.hpp>
#include <type_traits>

TEMPLATE_TEST_CASE("Type traits", "", std::int8_t, std::int16_t, std::int32_t, std::int64_t)
{
    STATIC_CHECK(sizeof(Rational<TestType>) == 2 * sizeof(TestType));
    STATIC_CHECK(alignof(Rational<TestType>) == alignof(TestType));
    STATIC_CHECK(std::is_default_constructible_v<Rational<TestType>>);
    STATIC_CHECK(std::is_trivially_copy_constructible_v<Rational<TestType>>);
    STATIC_CHECK(std::is_trivially_copy_assignable_v<Rational<TestType>>);
    STATIC_CHECK(std::is_trivially_move_constructible_v<Rational<TestType>>);
    STATIC_CHECK(std::is_trivially_move_assignable_v<Rational<TestType>>);
    STATIC_CHECK(std::is_nothrow_swappable_v<Rational<TestType>>);
    STATIC_CHECK(std::has_unique_object_representations_v<Rational<TestType>>);
    STATIC_CHECK(std::totally_ordered<Rational<TestType>>);
    STATIC_CHECK(std::three_way_comparable<Rational<TestType>>);
}

TEMPLATE_TEST_CASE("real()", "", std::int8_t, std::int16_t, std::int32_t, std::int64_t)
{
    STATIC_CHECK(Rational<TestType>(-1).real() == -1);
    STATIC_CHECK(Rational<TestType>(-100, 100).real() == -1);
    STATIC_CHECK(Rational<TestType>(120, 16).real() == 7.5);
    STATIC_CHECK(Rational<TestType>(10, 4).real() == 2.5);
    STATIC_CHECK(Rational<TestType, float>(10, 4).real() == 2.5f);
}

TEMPLATE_TEST_CASE("operator-()", "", std::int8_t, std::int16_t, std::int32_t, std::int64_t)
{
    STATIC_CHECK(-Rational<TestType>(2) == Rational<TestType>(-2));
    STATIC_CHECK(-Rational<TestType>(-42) == Rational<TestType>(42));
}

TEMPLATE_TEST_CASE("operator+(const Rational&)", "", std::int8_t, std::int16_t, std::int32_t, std::int64_t)
{
    STATIC_CHECK(Rational<TestType>(1) + Rational<TestType>(2) == Rational<TestType>(3));
    STATIC_CHECK(Rational<TestType>(7) + Rational<TestType>(11) == Rational<TestType>(18));
    STATIC_CHECK(Rational<TestType>(1, 3) + Rational<TestType>(1, 6) == Rational<TestType>(1, 2));
    STATIC_CHECK(Rational<TestType>(1, 8) + Rational<TestType>(1, 16) == Rational<TestType>(3, 16));
}

TEMPLATE_TEST_CASE("operator+=(const Rational&)", "", std::int8_t, std::int16_t, std::int32_t, std::int64_t)
{
    Rational<TestType> value(10, 3);
    value += { 11, 7 };
    CHECK(value == Rational<TestType>(103, 21));
}

TEMPLATE_TEST_CASE("operator-(const Rational&)", "", std::int8_t, std::int16_t, std::int32_t, std::int64_t)
{
    STATIC_CHECK(Rational<TestType>(1) - Rational<TestType>(2) == Rational<TestType>(-1));
    STATIC_CHECK(Rational<TestType>(17) - Rational<TestType>(13) == Rational<TestType>(4));
    STATIC_CHECK(Rational<TestType>(2) - Rational<TestType>(1, 6) == Rational<TestType>(11, 6));
}

TEMPLATE_TEST_CASE("operator-=(const Rational&)", "", std::int8_t, std::int16_t, std::int32_t, std::int64_t)
{
    Rational<TestType> value(10, 3);
    value -= { 11, 7 };
    CHECK(value == Rational<TestType>(37, 21));
}

TEMPLATE_TEST_CASE("operator*(const Rational&)", "", std::int8_t, std::int16_t, std::int32_t, std::int64_t)
{
    STATIC_CHECK(Rational<TestType>() * Rational<TestType>() == Rational<TestType>());
    STATIC_CHECK(Rational<TestType>(3, 5) * Rational<TestType>(7, 11) == Rational<TestType>(21, 55));
}

TEMPLATE_TEST_CASE("operator*=(const Rational&)", "", std::int8_t, std::int16_t, std::int32_t, std::int64_t)
{
    Rational<TestType> value(5, 3);
    value *= { 11, 7 };
    CHECK(value == Rational<TestType>(55, 21));
}

TEMPLATE_TEST_CASE("operator/(const Rational&)", "", std::int8_t, std::int16_t, std::int32_t, std::int64_t)
{
    STATIC_CHECK(Rational<TestType>() / Rational<TestType>(1) == Rational<TestType>());
    STATIC_CHECK(Rational<TestType>(3, 5) / Rational<TestType>(7, 11) == Rational<TestType>(33, 35));
}

TEMPLATE_TEST_CASE("operator/=(const Rational&)", "", std::int8_t, std::int16_t, std::int32_t, std::int64_t)
{
    Rational<TestType> value(5, 3);
    value /= { 11, 7 };
    CHECK(value == Rational<TestType>(35, 33));
}

TEMPLATE_TEST_CASE("operator==(const Rational&)", "", std::int8_t, std::int16_t, std::int32_t, std::int64_t)
{
    STATIC_CHECK(Rational<TestType>(1) == Rational<TestType>(1));
    STATIC_CHECK(Rational<TestType>(1) == Rational<TestType>(2, 2));
    STATIC_CHECK(Rational<TestType>(100, 25) == Rational<TestType>(4));

    STATIC_CHECK_FALSE(Rational<TestType>(1) == Rational<TestType>(2));
}

TEMPLATE_TEST_CASE("operator!=(const Rational&)", "", std::int8_t, std::int16_t, std::int32_t, std::int64_t)
{
    STATIC_CHECK(Rational<TestType>(2) != Rational<TestType>(1));
    STATIC_CHECK(Rational<TestType>(10, 3) != Rational<TestType>(3, 10));

    STATIC_CHECK_FALSE(Rational<TestType>(1) != Rational<TestType>(1));
    STATIC_CHECK_FALSE(Rational<TestType>(10) != Rational<TestType>(10, 1));
    STATIC_CHECK_FALSE(Rational<TestType>(10, 5) != Rational<TestType>(4, 2));
}

TEMPLATE_TEST_CASE("operator<(const Rational&)", "", std::int8_t, std::int16_t, std::int32_t, std::int64_t)
{
    STATIC_CHECK(Rational<TestType>() < Rational<TestType>(1));
    STATIC_CHECK(Rational<TestType>(1) < Rational<TestType>(2));
    STATIC_CHECK(Rational<TestType>(1, 2) < Rational<TestType>(2, 3));
    STATIC_CHECK(Rational<TestType>(4, 5) < Rational<TestType>(5, 4));

    STATIC_CHECK_FALSE(Rational<TestType>() < Rational<TestType>());
    STATIC_CHECK_FALSE(Rational<TestType>(1) < Rational<TestType>());
    STATIC_CHECK_FALSE(Rational<TestType>(2) < Rational<TestType>(1));
    STATIC_CHECK_FALSE(Rational<TestType>(2, 3) < Rational<TestType>(1, 2));
    STATIC_CHECK_FALSE(Rational<TestType>(5, 4) < Rational<TestType>(4, 5));
}

TEMPLATE_TEST_CASE("operator>(const Rational&)", "", std::int8_t, std::int16_t, std::int32_t, std::int64_t)
{
    STATIC_CHECK(Rational<TestType>(1) > Rational<TestType>());
    STATIC_CHECK(Rational<TestType>(2) > Rational<TestType>(1));
    STATIC_CHECK(Rational<TestType>(2, 3) > Rational<TestType>(1, 2));
    STATIC_CHECK(Rational<TestType>(5, 4) > Rational<TestType>(4, 5));

    STATIC_CHECK_FALSE(Rational<TestType>() > Rational<TestType>());
    STATIC_CHECK_FALSE(Rational<TestType>() > Rational<TestType>(1));
    STATIC_CHECK_FALSE(Rational<TestType>(1) > Rational<TestType>(2));
    STATIC_CHECK_FALSE(Rational<TestType>(1, 2) > Rational<TestType>(2, 3));
    STATIC_CHECK_FALSE(Rational<TestType>(4, 5) > Rational<TestType>(5, 4));
}

TEMPLATE_TEST_CASE("std::complex", "", std::int8_t, std::int16_t, std::int32_t, std::int64_t)
{
    constexpr std::complex<Rational<TestType>> value1({ 5, 3 }, { 3, 7 });
    STATIC_CHECK(value1.real() == Rational<TestType>(5, 3));
    STATIC_CHECK(value1.imag() == Rational<TestType>(3, 7));

    constexpr std::complex<Rational<TestType>> value2({ 17, 13 }, { 7, 11 });
    STATIC_CHECK(value2.real() == Rational<TestType>(17, 13));
    STATIC_CHECK(value2.imag() == Rational<TestType>(7, 11));

    constexpr std::complex<Rational<TestType>> value3 = value1 + value2;
    STATIC_CHECK(value3.real() == Rational<TestType>(116, 39));
    STATIC_CHECK(value3.imag() == Rational<TestType>(82, 77));

    constexpr std::complex<Rational<TestType>> value4 = value1 - value2;
    STATIC_CHECK(value4.real() == Rational<TestType>(14, 39));
    STATIC_CHECK(value4.imag() == Rational<TestType>(-16, 77));
}
