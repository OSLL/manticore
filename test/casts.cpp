#include <utils/casts.h>

#define BOOST_TEST_MODULE test_manticore
#include <boost/test/unit_test.hpp>

struct casts_test_struct {
    int ival_;
    std::string sval_;

    casts_test_struct(int i, std::string const &s) : ival_(i), sval_(s) {}
    int ToInt() { return ival_; }
    std::string ToString() { return sval_; }
};

struct casts_test_struct_const {
    int const ival_;
    std::string const sval_;

    casts_test_struct_const(int i, std::string const &s) : ival_(i), sval_(s) {}
    int ToInt() const { return ival_; }
    std::string ToString() const { return sval_; }
};

BOOST_AUTO_TEST_CASE(test_simple_casts)
{
    casts_test_struct one(1, "1"), two(2, "2"), three(3, "3");
    BOOST_CHECK_EQUAL(manticore::utils::case_cast(one), 1);
    BOOST_CHECK_EQUAL(manticore::utils::string_cast(one), "1");
    BOOST_CHECK_EQUAL(manticore::utils::case_cast(two), 2);
    BOOST_CHECK_EQUAL(manticore::utils::string_cast(two), "2");
    BOOST_CHECK_EQUAL(manticore::utils::case_cast(three), 3);
    BOOST_CHECK_EQUAL(manticore::utils::string_cast(three), "3");
}

BOOST_AUTO_TEST_CASE(test_const_casts)
{
    const casts_test_struct_const one(1, "1"), two(2, "2"), three(3, "3");
    BOOST_CHECK_EQUAL(manticore::utils::case_cast(one), 1);
    BOOST_CHECK_EQUAL(manticore::utils::string_cast(one), "1");
    BOOST_CHECK_EQUAL(manticore::utils::case_cast(two), 2);
    BOOST_CHECK_EQUAL(manticore::utils::string_cast(two), "2");
    BOOST_CHECK_EQUAL(manticore::utils::case_cast(three), 3);
    BOOST_CHECK_EQUAL(manticore::utils::string_cast(three), "3");
}
