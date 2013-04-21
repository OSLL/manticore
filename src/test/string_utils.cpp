#include <utils/string_utils.h>
#include <utils/types.h>

#define BOOST_TEST_MODULE test_manticore_string_utils
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(test_stringify)
{
    int pid = 213;
    std::string test("process 213 doesn't exists or isn't stopped");
    BOOST_CHECK_EQUAL(test, manticore::utils::stringify("process ", pid, " doesn't exists or isn't stopped"));
}

BOOST_AUTO_TEST_CASE(test_to_hex)
{
    u8 value = 255;
    std::string converted(manticore::utils::format_hex(&value, &value + 1));
    std::ostringstream stream;
    stream << std::hex << static_cast<int>(value);
    BOOST_CHECK_EQUAL(converted, stream.str());
}

BOOST_AUTO_TEST_CASE(test_string_vector)
{
    std::string str("value");
    std::vector<char> vec(manticore::utils::from_string(str));
    BOOST_CHECK_EQUAL(str.size(), vec.size());
    BOOST_CHECK(std::equal(str.data(), str.data() + str.size(), vec.begin()));
}

BOOST_AUTO_TEST_CASE(test_vector_string)
{
    std::vector<char> vec = { 'v', 'a', 'l', 'u', 'e' };
    std::string str(manticore::utils::from_vector(vec));
    BOOST_CHECK_EQUAL(str.size(), vec.size());
    BOOST_CHECK(std::equal(str.data(), str.data() + str.size(), vec.begin()));
}
