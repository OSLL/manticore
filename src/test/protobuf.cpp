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
    RegisterPtr one = std::make_shared<Register>( "bit1",
                                                  RegisterType::INTEGER,
                                                  RegisterCapacity::BIT8,
                                                  &bit1 );

    std::ostringstream strout(std::ios::binary | std::ios::out);
    strout << one;

    std::istringstream strin(strout.str(), std::ios::binary | std::ios::in);
    RegisterPtr one_copy;
    strin >> one_copy;

    BOOST_CHECK(*one == *one_copy);
}

BOOST_AUTO_TEST_CASE(test_two_protobuf)
{
    u16 bit1 = 1;
    RegisterPtr one = std::make_shared<Register>( "bit1",
                                                  RegisterType::INTEGER,
                                                  RegisterCapacity::BIT16,
                                                  reinterpret_cast<u8*>(&bit1) );

    std::ostringstream strout(std::ios::binary | std::ios::out);
    strout << one;

    std::istringstream strin(strout.str(), std::ios::binary | std::ios::in);
    RegisterPtr one_copy;
    strin >> one_copy;

    BOOST_CHECK(*one == *one_copy);
}

BOOST_AUTO_TEST_CASE(test_four_protobuf)
{
    u32 bit1 = 1;
    RegisterPtr one = std::make_shared<Register>( "bit1",
                                                  RegisterType::INTEGER,
                                                  RegisterCapacity::BIT32,
                                                  reinterpret_cast<u8*>(&bit1) );

    std::ostringstream strout(std::ios::binary | std::ios::out);
    strout << one;

    std::istringstream strin(strout.str(), std::ios::binary | std::ios::in);
    RegisterPtr one_copy;
    strin >> one_copy;

    BOOST_CHECK(*one == *one_copy);
}

BOOST_AUTO_TEST_CASE(test_eight_protobuf)
{
    u64 bit1 = 1;
    RegisterPtr one = std::make_shared<Register>( "bit1",
                                                  RegisterType::INTEGER,
                                                  RegisterCapacity::BIT64,
                                                  reinterpret_cast<u8*>(&bit1) );

    std::ostringstream strout(std::ios::binary | std::ios::out);
    strout << one;

    std::istringstream strin(strout.str(), std::ios::binary | std::ios::in);
    RegisterPtr one_copy;
    strin >> one_copy;

    BOOST_CHECK(*one == *one_copy);
}

BOOST_AUTO_TEST_CASE(test_vector_protobuf)
{
    u8 bit1 = 1; u16 bit2 = 2; u32 bit3 = 4; u64 bit4 = 8;
    RegisterPtr one = std::make_shared<Register>( "bit1",
                                                  RegisterType::INTEGER,
                                                  RegisterCapacity::BIT8,
                                                  &bit1 );
    RegisterPtr two = std::make_shared<Register>( "bit2",
                                                  RegisterType::INTEGER,
                                                  RegisterCapacity::BIT16,
                                                  reinterpret_cast<u8*>(&bit2) );
    RegisterPtr three = std::make_shared<Register>( "bit3",
                                                    RegisterType::INTEGER,
                                                    RegisterCapacity::BIT32,
                                                    reinterpret_cast<u8*>(&bit3) );
    RegisterPtr four = std::make_shared<Register>( "bit4",
                                                   RegisterType::INTEGER,
                                                   RegisterCapacity::BIT64,
                                                   reinterpret_cast<u8*>(&bit4) );

    std::vector<RegisterPtr> registers = { one, two, three, four };
    std::ostringstream strout(std::ios::binary | std::ios::out);
    strout << registers;

    std::vector<RegisterPtr> registers_copy;
    std::istringstream strin(strout.str(), std::ios::binary | std::ios::in);
    strin >> registers_copy;

    BOOST_CHECK(registers.size() == registers_copy.size());
    for (auto sit = registers.begin(), tit = registers_copy.begin(); sit != registers.end(); ++sit, ++tit) {
        BOOST_CHECK(*(*sit) == *(*tit));
    }
}
