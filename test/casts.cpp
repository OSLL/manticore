#include <utils/casts.h>
#include <sstream>

#define BOOST_TEST_MODULE test_manticore_casts
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

struct implicit_struct_cast {
    int ival_;

    implicit_struct_cast(int i) : ival_(i) {}
    operator int() { return ival_; }
    operator std::string() {
        std::stringstream buffer;
        buffer << ival_;
        return buffer.str();
    }
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

BOOST_AUTO_TEST_CASE(test_simple_pointer_casts)
{
    casts_test_struct one(1, "1"), two(2, "2"), three(3, "3");
    BOOST_CHECK_EQUAL(manticore::utils::case_cast(&one), 1);
    BOOST_CHECK_EQUAL(manticore::utils::string_cast(&one), "1");
    BOOST_CHECK_EQUAL(manticore::utils::case_cast(&two), 2);
    BOOST_CHECK_EQUAL(manticore::utils::string_cast(&two), "2");
    BOOST_CHECK_EQUAL(manticore::utils::case_cast(&three), 3);
    BOOST_CHECK_EQUAL(manticore::utils::string_cast(&three), "3");
}

BOOST_AUTO_TEST_CASE(test_const_pointer_casts)
{
    const casts_test_struct_const one(1, "1"), two(2, "2"), three(3, "3");
    BOOST_CHECK_EQUAL(manticore::utils::case_cast(&one), 1);
    BOOST_CHECK_EQUAL(manticore::utils::string_cast(&one), "1");
    BOOST_CHECK_EQUAL(manticore::utils::case_cast(&two), 2);
    BOOST_CHECK_EQUAL(manticore::utils::string_cast(&two), "2");
    BOOST_CHECK_EQUAL(manticore::utils::case_cast(&three), 3);
    BOOST_CHECK_EQUAL(manticore::utils::string_cast(&three), "3");
}

BOOST_AUTO_TEST_CASE(test_implicit_casts)
{
    implicit_struct_cast one(1), two(2), three(3);
    BOOST_CHECK_EQUAL(manticore::utils::case_cast(one), 1);
    BOOST_CHECK_EQUAL(manticore::utils::string_cast(one), "1");
    BOOST_CHECK_EQUAL(manticore::utils::case_cast(two), 2);
    BOOST_CHECK_EQUAL(manticore::utils::string_cast(two), "2");
    BOOST_CHECK_EQUAL(manticore::utils::case_cast(three), 3);
    BOOST_CHECK_EQUAL(manticore::utils::string_cast(three), "3");
}

BOOST_AUTO_TEST_CASE(test_fundamental_casts)
{
    BOOST_CHECK_EQUAL(manticore::utils::case_cast(0.5f), 0);
    BOOST_CHECK_EQUAL(manticore::utils::case_cast(0.5L), 0);
    BOOST_CHECK_EQUAL(manticore::utils::case_cast(1.5f), 1);
    BOOST_CHECK_EQUAL(manticore::utils::case_cast(1.5L), 1);
    BOOST_CHECK_EQUAL(manticore::utils::case_cast(5u), 5);
    BOOST_CHECK_EQUAL(manticore::utils::case_cast(5l), 5);
    BOOST_CHECK_EQUAL(manticore::utils::case_cast(5), 5);

    BOOST_CHECK_EQUAL(manticore::utils::string_cast(5u), "5");
    BOOST_CHECK_EQUAL(manticore::utils::string_cast(5l), "5");
    BOOST_CHECK_EQUAL(manticore::utils::string_cast(5), "5");

    /* this may fails */
    BOOST_CHECK_EQUAL(manticore::utils::string_cast(0.5f), "0.5");
    BOOST_CHECK_EQUAL(manticore::utils::string_cast(0.5L), "0.5");
    BOOST_CHECK_EQUAL(manticore::utils::string_cast(1.5f), "1.5");
    BOOST_CHECK_EQUAL(manticore::utils::string_cast(1.5L), "1.5");
}
