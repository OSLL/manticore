#include <utils/casts.h>
#include <sstream>

#define BOOST_TEST_MODULE test_manticore_casts
#include <boost/test/unit_test.hpp>

struct casts_test_struct {
    std::string sval_;

    casts_test_struct(std::string const &s) : sval_(s) {}
    std::string ToString() { return sval_; }
};

struct casts_test_struct_const {
    std::string const sval_;

    casts_test_struct_const(std::string const &s) : sval_(s) {}
    std::string ToString() const { return sval_; }
};

BOOST_AUTO_TEST_CASE(test_simple_casts)
{
    casts_test_struct one("1"), two("2"), three("3");
    BOOST_CHECK_EQUAL(manticore::utils::string_cast(one), "1");
    BOOST_CHECK_EQUAL(manticore::utils::string_cast(two), "2");
    BOOST_CHECK_EQUAL(manticore::utils::string_cast(three), "3");
}

BOOST_AUTO_TEST_CASE(test_const_casts)
{
    const casts_test_struct_const one("1"), two("2"), three("3");
    BOOST_CHECK_EQUAL(manticore::utils::string_cast(one), "1");
    BOOST_CHECK_EQUAL(manticore::utils::string_cast(two), "2");
    BOOST_CHECK_EQUAL(manticore::utils::string_cast(three), "3");
}

BOOST_AUTO_TEST_CASE(test_simple_pointer_casts)
{
    casts_test_struct one("1"), two("2"), three("3");
    BOOST_CHECK_EQUAL(manticore::utils::string_cast(&one), "1");
    BOOST_CHECK_EQUAL(manticore::utils::string_cast(&two), "2");
    BOOST_CHECK_EQUAL(manticore::utils::string_cast(&three), "3");
}

BOOST_AUTO_TEST_CASE(test_const_pointer_casts)
{
    const casts_test_struct_const one("1"), two("2"), three("3");
    BOOST_CHECK_EQUAL(manticore::utils::string_cast(&one), "1");
    BOOST_CHECK_EQUAL(manticore::utils::string_cast(&two), "2");
    BOOST_CHECK_EQUAL(manticore::utils::string_cast(&three), "3");
}
