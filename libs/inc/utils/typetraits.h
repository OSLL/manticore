#ifndef __TYPE_TRAITS_H__
#define __TYPE_TRAITS_H__

namespace manticore { namespace typetraits {

template <int value> struct IntToType { enum { Value = value }; };
typedef char true_type;
struct false_type { true_type dummy[2]; };
struct NullType {};

namespace detail {

    template <typename U>
    struct PointerTrait {
        enum { Value = false };
        typedef NullType PointeeType;
    };

    template <typename U>
    struct PointerTrait<U*> {
        enum { Value = true };
        typedef U PointeeType;
    };

    template <typename U>
    struct PointerTrait<U* const> {
        enum { Value = true };
        typedef U PointeeType;
    };


    template <typename U>
    struct ReferenceTrait {
        enum { Value = false };
        typedef NullType ReferencedType;
    };

    template <typename U>
    struct ReferenceTrait<U&> {
        enum { Value = true };
        typedef U ReferencedType;
    };

}

template <typename T>
struct IsPointer {
    enum { Value = detail::PointerTrait<T>::Value };
    typedef typename detail::PointerTrait<T>::PointeeType PointeeType;
};

template <typename T>
struct IsReference {
    enum { Value = detail::ReferenceTrait<T>::Value };
    typedef typename detail::ReferenceTrait<T>::ReferencedType RefereeType;
};

} }

#endif /*__TYPE_TRAITS_H__*/
