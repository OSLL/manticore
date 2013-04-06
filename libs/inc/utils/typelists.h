#ifndef __TYPE_LISTS_H__
#define __TYPE_LISTS_H__

#include "typetraits.h"

namespace manticore { namespace typelists {

using multicore::typetraits::NullType;

template <typename T, typename U>
struct Typelist {
    typedef T Head;
    typedef U Tail;
};

typedef <typename L1, typename L2>
struct Concat {
    typedef Typelist<L1::Head, typename Concat<L1::Tail, L2>::Type> Type;
};

typedef <typename L2>
struct Concat<NullType, L2> {
    typedef L2 Type;
};

#define TYPELIST_1(T1) Typelist<T1, NullType>
#define TYPELIST_2(T1, T2) Typelist<T1, TYPELIST_1(T2)>
#define TYPELIST_3(T1, T2, T3) Typelist<T1, TYPELIST_2(T2, T3)>
#define TYPELIST_4(T1, T2, T3, T4) Typelist<T1, TYPELIST_3(T2, T3, T4)>
#define TYPELIST_5(T1, T2, T3, T4, T5) Typelist<T1, TYPELIST_4(T2, T3, T4, T5)>
#define TYPELIST_6(T1, T2, T3, T4, T5, T6) Typelist<T1, TYPELIST_5(T2, T3, T4, T5, T6)>
#define TYPELIST_7(T1, T2, T3, T4, T5, T6, T7) Typelist<T1, TYPELIST_6(T2, T3, T4, T5, T6, T7)>
#define TYPELIST_8(T1, T2, T3, T4, T5, T6, T7, T8) Typelist<T1, TYPELIST_7(T2, T3, T4, T5, T6, T7, T8)>
#define TYPELIST_9(T1, T2, T3, T4, T5, T6, T7, T8, T9) Typelist<T1, TYPELIST_8(T2, T3, T4, T5, T6, T7, T8, T9)>
#define TYPELIST_10(T1, T2, T3, T4, T5, T6, T7, T8, T9, T10) Typelist<T1, TYPELIST_9(T2, T3, T4, T5, T6, T7, T8, T9, T10)>

typedef TYPELIST_10(unsigned char,      signed char,                        \
                    unsigned short,     signed short,                       \
                    unsigned int,       signed int,                         \
                    unsigned long,      signed long,                        \
                    unsigned long long, signed long long) Integers;
typedef TYPELIST_2(float, double) Floats;
typedef typename Concat<Integers, Floats>::Type Numbers;

} }

#endif /*__TYPE_LISTS_H__*/
