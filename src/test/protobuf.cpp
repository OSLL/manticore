#include <process/serialize.h>
#include <process/registers.h>

#define BOOST_TEST_MODULE test_manticore_protobuf
#include <boost/test/unit_test.hpp>

#include <algorithm>
#include <sstream>
#include <vector>

using namespace manticore::serialize;
using namespace manticore::process;

BOOST_AUTO_TEST_CASE(test_one_protobuf)
{
    u8 bit1 = 1;
    RegisterConstPtr one = std::make_shared<const Register>( "bit1",
                                                             RegisterType::INTEGER,
                                                             RegisterCapacity::BIT8,
                                                             reinterpret_cast<char *>(&bit1) );

    std::ostringstream strout(std::ios::binary | std::ios::out);
    strout << one;

    std::istringstream strin(strout.str(), std::ios::binary | std::ios::in);
    RegisterConstPtr one_copy;
    strin >> one_copy;

    BOOST_CHECK(*one == *one_copy);
}

BOOST_AUTO_TEST_CASE(test_two_protobuf)
{
    u16 bit1 = 1;
    RegisterConstPtr one = std::make_shared<const Register>( "bit1",
                                                             RegisterType::INTEGER,
                                                             RegisterCapacity::BIT16,
                                                             reinterpret_cast<char *>(&bit1) );

    std::ostringstream strout(std::ios::binary | std::ios::out);
    strout << one;

    std::istringstream strin(strout.str(), std::ios::binary | std::ios::in);
    RegisterConstPtr one_copy;
    strin >> one_copy;

    BOOST_CHECK(*one == *one_copy);
}

BOOST_AUTO_TEST_CASE(test_four_protobuf)
{
    u32 bit1 = 1;
    RegisterConstPtr one = std::make_shared<const Register>( "bit1",
                                                             RegisterType::INTEGER,
                                                             RegisterCapacity::BIT32,
                                                             reinterpret_cast<char *>(&bit1) );

    std::ostringstream strout(std::ios::binary | std::ios::out);
    strout << one;

    std::istringstream strin(strout.str(), std::ios::binary | std::ios::in);
    RegisterConstPtr one_copy;
    strin >> one_copy;

    BOOST_CHECK(*one == *one_copy);
}

BOOST_AUTO_TEST_CASE(test_eight_protobuf)
{
    u64 bit1 = 1;
    RegisterConstPtr one = std::make_shared<const Register>( "bit1",
                                                             RegisterType::INTEGER,
                                                             RegisterCapacity::BIT64,
                                                             reinterpret_cast<char *>(&bit1) );

    std::ostringstream strout(std::ios::binary | std::ios::out);
    strout << one;

    std::istringstream strin(strout.str(), std::ios::binary | std::ios::in);
    RegisterConstPtr one_copy;
    strin >> one_copy;

    BOOST_CHECK(*one == *one_copy);
}

BOOST_AUTO_TEST_CASE(test_vector_protobuf)
{
    u8 bit1 = 1; u16 bit2 = 2; u32 bit3 = 4; u64 bit4 = 8;
    RegisterConstPtr one = std::make_shared<const Register>( "bit1",
                                                             RegisterType::INTEGER,
                                                             RegisterCapacity::BIT8,
                                                             reinterpret_cast<char *>(&bit1) );
    RegisterConstPtr two = std::make_shared<const Register>( "bit2",
                                                             RegisterType::INTEGER,
                                                             RegisterCapacity::BIT16,
                                                             reinterpret_cast<char *>(&bit2) );
    RegisterConstPtr three = std::make_shared<const Register>( "bit3",
                                                               RegisterType::INTEGER,
                                                               RegisterCapacity::BIT32,
                                                               reinterpret_cast<char *>(&bit3) );
    RegisterConstPtr four = std::make_shared<const Register>( "bit4",
                                                              RegisterType::INTEGER,
                                                              RegisterCapacity::BIT64,
                                                              reinterpret_cast<char *>(&bit4) );

    std::vector<RegisterConstPtr> registers = { one, two, three, four };
    std::ostringstream strout(std::ios::binary | std::ios::out);
    strout << registers;

    std::vector<RegisterConstPtr> registers_copy;
    std::istringstream strin(strout.str(), std::ios::binary | std::ios::in);
    strin >> registers_copy;

    BOOST_CHECK(registers.size() == registers_copy.size());
    for (auto sit = registers.begin(), tit = registers_copy.begin(); sit != registers.end(); ++sit, ++tit) {
        BOOST_CHECK(*(*sit) == *(*tit));
    }
}
