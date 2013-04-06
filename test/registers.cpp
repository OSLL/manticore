#include <process/registers.h>
#include <utils/types.h>

#include <boost/test/unit_test.hpp>

#include <algorithm>

BOOST_AUTO_TEST_CASE(test_one_byte_integer)
{
    u8 bit1 = 1, bit2 = 2, bit3 = 4, bit4 = 8;
    manticore::process::I8Register one("bit1", &bit1);
    manticore::process::I8Register two("bit2", &bit2);
    manticore::process::I8Register three("bit3", &bit3);
    manticore::process::I8Register four("bit4", &bit4);

    std::vector<u8> one_value(one.GetValue());
    BOOST_CHECK_EQUAL(one.GetName(), "bit1");
    BOOST_CHECK(std::equal(one_value.begin(), one_value.end(), &bit1));

    std::vector<u8> two_value(two.GetValue());
    BOOST_CHECK_EQUAL(two.GetName(), "bit2");
    BOOST_CHECK(std::equal(two_value.begin(), two_value.end(), &bit2));

    std::vector<u8> three_value(three.GetValue());
    BOOST_CHECK_EQUAL(three.GetName(), "bit3");
    BOOST_CHECK(std::equal(three_value.begin(), three_value.end(), &bit3));

    std::vector<u8> four_value(four.GetValue());
    BOOST_CHECK_EQUAL(four.GetName(), "bit4");
    BOOST_CHECK(std::equal(four_value.begin(), four_value.end(), &bit4));
}

BOOST_AUTO_TEST_CASE(test_two_byte_integer)
{
    u16 bit1 = 1, bit2 = 2, bit3 = 4, bit4 = 8;
    manticore::process::I16Register one("bit1", reinterpret_cast<u8*>(&bit1));
    manticore::process::I16Register two("bit2", reinterpret_cast<u8*>(&bit2));
    manticore::process::I16Register three("bit3", reinterpret_cast<u8*>(&bit3));
    manticore::process::I16Register four("bit4", reinterpret_cast<u8*>(&bit4));

    std::vector<u8> one_value(one.GetValue());
    BOOST_CHECK_EQUAL(one.GetName(), "bit1");
    BOOST_CHECK(std::equal(one_value.begin(), one_value.end(), reinterpret_cast<u8*>(&bit1)));

    std::vector<u8> two_value(two.GetValue());
    BOOST_CHECK_EQUAL(two.GetName(), "bit2");
    BOOST_CHECK(std::equal(two_value.begin(), two_value.end(), reinterpret_cast<u8*>(&bit2)));

    std::vector<u8> three_value(three.GetValue());
    BOOST_CHECK_EQUAL(three.GetName(), "bit3");
    BOOST_CHECK(std::equal(three_value.begin(), three_value.end(), reinterpret_cast<u8*>(&bit3)));

    std::vector<u8> four_value(four.GetValue());
    BOOST_CHECK_EQUAL(four.GetName(), "bit4");
    BOOST_CHECK(std::equal(four_value.begin(), four_value.end(), reinterpret_cast<u8*>(&bit4)));
}

BOOST_AUTO_TEST_CASE(test_four_byte_integer)
{
    u32 bit1 = 1, bit2 = 2, bit3 = 4, bit4 = 8;
    manticore::process::I32Register one("bit1", reinterpret_cast<u8*>(&bit1));
    manticore::process::I32Register two("bit2", reinterpret_cast<u8*>(&bit2));
    manticore::process::I32Register three("bit3", reinterpret_cast<u8*>(&bit3));
    manticore::process::I32Register four("bit4", reinterpret_cast<u8*>(&bit4));

    std::vector<u8> one_value(one.GetValue());
    BOOST_CHECK_EQUAL(one.GetName(), "bit1");
    BOOST_CHECK(std::equal(one_value.begin(), one_value.end(), reinterpret_cast<u8*>(&bit1)));

    std::vector<u8> two_value(two.GetValue());
    BOOST_CHECK_EQUAL(two.GetName(), "bit2");
    BOOST_CHECK(std::equal(two_value.begin(), two_value.end(), reinterpret_cast<u8*>(&bit2)));

    std::vector<u8> three_value(three.GetValue());
    BOOST_CHECK_EQUAL(three.GetName(), "bit3");
    BOOST_CHECK(std::equal(three_value.begin(), three_value.end(), reinterpret_cast<u8*>(&bit3)));

    std::vector<u8> four_value(four.GetValue());
    BOOST_CHECK_EQUAL(four.GetName(), "bit4");
    BOOST_CHECK(std::equal(four_value.begin(), four_value.end(), reinterpret_cast<u8*>(&bit4)));
}

BOOST_AUTO_TEST_CASE(test_eight_byte_integer)
{
    u64 bit1 = 1, bit2 = 2, bit3 = 4, bit4 = 8;
    manticore::process::I64Register one("bit1", reinterpret_cast<u8*>(&bit1));
    manticore::process::I64Register two("bit2", reinterpret_cast<u8*>(&bit2));
    manticore::process::I64Register three("bit3", reinterpret_cast<u8*>(&bit3));
    manticore::process::I64Register four("bit4", reinterpret_cast<u8*>(&bit4));

    std::vector<u8> one_value(one.GetValue());
    BOOST_CHECK_EQUAL(one.GetName(), "bit1");
    BOOST_CHECK(std::equal(one_value.begin(), one_value.end(), reinterpret_cast<u8*>(&bit1)));

    std::vector<u8> two_value(two.GetValue());
    BOOST_CHECK_EQUAL(two.GetName(), "bit2");
    BOOST_CHECK(std::equal(two_value.begin(), two_value.end(), reinterpret_cast<u8*>(&bit2)));

    std::vector<u8> three_value(three.GetValue());
    BOOST_CHECK_EQUAL(three.GetName(), "bit3");
    BOOST_CHECK(std::equal(three_value.begin(), three_value.end(), reinterpret_cast<u8*>(&bit3)));

    std::vector<u8> four_value(four.GetValue());
    BOOST_CHECK_EQUAL(four.GetName(), "bit4");
    BOOST_CHECK(std::equal(four_value.begin(), four_value.end(), reinterpret_cast<u8*>(&bit4)));
}
