#include <process/registers.h>
#include <utils/types.h>

#define BOOST_TEST_MODULE test_manticore_registers
#include <boost/test/unit_test.hpp>

#include <algorithm>

using namespace manticore::process;

BOOST_AUTO_TEST_CASE(test_one_byte_integer)
{
    u8 bit1 = 1, bit2 = 2, bit3 = 4, bit4 = 8;
    Register one("bit1", RegisterType::INTEGER, RegisterCapacity::BIT8, reinterpret_cast<char *>(&bit1));
    Register two("bit2", RegisterType::INTEGER, RegisterCapacity::BIT8, reinterpret_cast<char *>(&bit2));
    Register three("bit3", RegisterType::INTEGER, RegisterCapacity::BIT8, reinterpret_cast<char *>(&bit3));
    Register four("bit4", RegisterType::INTEGER, RegisterCapacity::BIT8, reinterpret_cast<char *>(&bit4));

    std::vector<char> one_value(one.GetValue());
    BOOST_CHECK_EQUAL(one.GetName(), "bit1");
    BOOST_CHECK(std::equal(one_value.begin(), one_value.end(), &bit1));

    std::vector<char> two_value(two.GetValue());
    BOOST_CHECK_EQUAL(two.GetName(), "bit2");
    BOOST_CHECK(std::equal(two_value.begin(), two_value.end(), &bit2));

    std::vector<char> three_value(three.GetValue());
    BOOST_CHECK_EQUAL(three.GetName(), "bit3");
    BOOST_CHECK(std::equal(three_value.begin(), three_value.end(), &bit3));

    std::vector<char> four_value(four.GetValue());
    BOOST_CHECK_EQUAL(four.GetName(), "bit4");
    BOOST_CHECK(std::equal(four_value.begin(), four_value.end(), &bit4));
}

BOOST_AUTO_TEST_CASE(test_two_byte_integer)
{
    u16 bit1 = 1, bit2 = 2, bit3 = 4, bit4 = 8;
    Register one("bit1", RegisterType::INTEGER, RegisterCapacity::BIT16, reinterpret_cast<char *>(&bit1));
    Register two("bit2", RegisterType::INTEGER, RegisterCapacity::BIT16, reinterpret_cast<char *>(&bit2));
    Register three("bit3", RegisterType::INTEGER, RegisterCapacity::BIT16, reinterpret_cast<char *>(&bit3));
    Register four("bit4", RegisterType::INTEGER, RegisterCapacity::BIT16, reinterpret_cast<char *>(&bit4));

    std::vector<char> one_value(one.GetValue());
    BOOST_CHECK_EQUAL(one.GetName(), "bit1");
    BOOST_CHECK(std::equal(one_value.begin(), one_value.end(), reinterpret_cast<char *>(&bit1)));

    std::vector<char> two_value(two.GetValue());
    BOOST_CHECK_EQUAL(two.GetName(), "bit2");
    BOOST_CHECK(std::equal(two_value.begin(), two_value.end(), reinterpret_cast<char *>(&bit2)));

    std::vector<char> three_value(three.GetValue());
    BOOST_CHECK_EQUAL(three.GetName(), "bit3");
    BOOST_CHECK(std::equal(three_value.begin(), three_value.end(), reinterpret_cast<char *>(&bit3)));

    std::vector<char> four_value(four.GetValue());
    BOOST_CHECK_EQUAL(four.GetName(), "bit4");
    BOOST_CHECK(std::equal(four_value.begin(), four_value.end(), reinterpret_cast<char *>(&bit4)));
}

BOOST_AUTO_TEST_CASE(test_four_byte_integer)
{
    u32 bit1 = 1, bit2 = 2, bit3 = 4, bit4 = 8;
    Register one("bit1", RegisterType::INTEGER, RegisterCapacity::BIT32, reinterpret_cast<char *>(&bit1));
    Register two("bit2", RegisterType::INTEGER, RegisterCapacity::BIT32, reinterpret_cast<char *>(&bit2));
    Register three("bit3", RegisterType::INTEGER, RegisterCapacity::BIT32, reinterpret_cast<char *>(&bit3));
    Register four("bit4", RegisterType::INTEGER, RegisterCapacity::BIT32, reinterpret_cast<char *>(&bit4));

    std::vector<char> one_value(one.GetValue());
    BOOST_CHECK_EQUAL(one.GetName(), "bit1");
    BOOST_CHECK(std::equal(one_value.begin(), one_value.end(), reinterpret_cast<char *>(&bit1)));

    std::vector<char> two_value(two.GetValue());
    BOOST_CHECK_EQUAL(two.GetName(), "bit2");
    BOOST_CHECK(std::equal(two_value.begin(), two_value.end(), reinterpret_cast<char *>(&bit2)));

    std::vector<char> three_value(three.GetValue());
    BOOST_CHECK_EQUAL(three.GetName(), "bit3");
    BOOST_CHECK(std::equal(three_value.begin(), three_value.end(), reinterpret_cast<char *>(&bit3)));

    std::vector<char> four_value(four.GetValue());
    BOOST_CHECK_EQUAL(four.GetName(), "bit4");
    BOOST_CHECK(std::equal(four_value.begin(), four_value.end(), reinterpret_cast<char *>(&bit4)));
}

BOOST_AUTO_TEST_CASE(test_eight_byte_integer)
{
    u64 bit1 = 1, bit2 = 2, bit3 = 4, bit4 = 8;
    Register one("bit1", RegisterType::INTEGER, RegisterCapacity::BIT64, reinterpret_cast<char *>(&bit1));
    Register two("bit2", RegisterType::INTEGER, RegisterCapacity::BIT64, reinterpret_cast<char *>(&bit2));
    Register three("bit3", RegisterType::INTEGER, RegisterCapacity::BIT64, reinterpret_cast<char *>(&bit3));
    Register four("bit4", RegisterType::INTEGER, RegisterCapacity::BIT64, reinterpret_cast<char *>(&bit4));

    std::vector<char> one_value(one.GetValue());
    BOOST_CHECK_EQUAL(one.GetName(), "bit1");
    BOOST_CHECK(std::equal(one_value.begin(), one_value.end(), reinterpret_cast<char *>(&bit1)));

    std::vector<char> two_value(two.GetValue());
    BOOST_CHECK_EQUAL(two.GetName(), "bit2");
    BOOST_CHECK(std::equal(two_value.begin(), two_value.end(), reinterpret_cast<char *>(&bit2)));

    std::vector<char> three_value(three.GetValue());
    BOOST_CHECK_EQUAL(three.GetName(), "bit3");
    BOOST_CHECK(std::equal(three_value.begin(), three_value.end(), reinterpret_cast<char *>(&bit3)));

    std::vector<char> four_value(four.GetValue());
    BOOST_CHECK_EQUAL(four.GetName(), "bit4");
    BOOST_CHECK(std::equal(four_value.begin(), four_value.end(), reinterpret_cast<char *>(&bit4)));
}
