#ifndef __CASTS_H__
#define __CASTS_H__

#include <string>

namespace manticore { namespace utils {

template <typename SRC, typename DST, bool EXPLICIT>
struct custom_caster {
    SRC &obj_;
    custom_caster(SRC &obj) : obj_(obj) { }
    operator DST() { return static_cast<DST>(obj_); }
};

template <typename SRC>
struct custom_caster<SRC, int, true> {
    SRC &obj_;
    custom_caster(SRC &obj) : obj_(obj) { }
    operator int() { return obj_.ToInt(); }
};

template <typename SRC>
struct custom_caster<SRC, int, false> {
    SRC &obj_;
    custom_caster(SRC &obj) : obj_(obj) { }
    operator int() { return static_cast<int>(obj_); }
};

template <typename SRC>
struct custom_caster<SRC, std::string, true> {
    SRC &obj_;
    custom_caster(SRC &obj) : obj_(obj) { }
    operator std::string() { return obj_.ToString(); }
};

template <typename SRC>
struct custom_caster<SRC, std::string, false> {
    SRC &obj_;
    custom_caster(SRC &obj) : obj_(obj) { }
    operator std::string() { return static_cast<std::string>(obj_); }
};

template <typename DST, typename SRC>
DST explicit_cast(SRC const &obj) {
    return static_cast<DST>(custom_caster<const SRC, DST, true>(obj));
}

template <typename DST, typename SRC>
DST explicit_cast(SRC &obj) {
    return static_cast<DST>(custom_caster<SRC, DST, true>(obj));
}

template <typename DST, typename SRC>
DST implicit_cast(SRC const &obj) {
    return static_cast<DST>(custom_caster<const SRC, DST, false>(obj));
}

template <typename DST, typename SRC>
DST implicit_cast(SRC &obj) {
    return static_cast<DST>(custom_caster<SRC, DST, false>(obj));
}

template <typename SRC>
int case_cast(SRC const &obj) {
    return explicit_cast<int>(obj);
}

template <typename SRC>
int case_cast(SRC &obj) {
    return explicit_cast<int>(obj);
}

template <typename SRC>
std::string string_cast(SRC const &obj) {
    return explicit_cast<std::string>(obj);
}

template <typename SRC>
std::string string_cast(SRC &obj) {
    return explicit_cast<std::string>(obj);
}

} }

#endif /*__CASTS_H__*/
