#include <utils/typetraits.h>

#include <boost/test/unit_test.hpp>

struct traits_test_struct { };

BOOST_AUTO_TEST_CASE(test_pointer)
{
    BOOST_CHECK_EQUAL(manticore::typetraits::IsPointer<traits_test_struct>::Value, false);
    BOOST_CHECK_EQUAL(manticore::typetraits::IsPointer<traits_test_struct const>::Value, false);
    BOOST_CHECK_EQUAL(manticore::typetraits::IsPointer<traits_test_struct *>::Value, true);
    BOOST_CHECK_EQUAL(manticore::typetraits::IsPointer<traits_test_struct const *>::Value, true);
    BOOST_CHECK_EQUAL(manticore::typetraits::IsPointer<traits_test_struct const * const>::Value, true);
}

BOOST_AUTO_TEST_CASE(test_reference)
{
    BOOST_CHECK_EQUAL(manticore::typetraits::IsReference<traits_test_struct>::Value, false);
    BOOST_CHECK_EQUAL(manticore::typetraits::IsReference<traits_test_struct &>::Value, true);
    BOOST_CHECK_EQUAL(manticore::typetraits::IsReference<traits_test_struct const &>::Value, true);
}
