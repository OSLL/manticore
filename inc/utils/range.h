#ifndef __RANGE_H__
#define __RANGE_H__

#include <functional>
#include <exception>
#include <string>

namespace manticore { namespace utils {

template <typename ValueType_ = size_t, typename DifferenceType_ = ValueType_>
class Range {
public:
    typedef ValueType_ ValueType;
    typedef DifferenceType_ DifferenceType;

    Range(ValueType const & lower, ValueType const & upper) : lower_(lower), upper_(upper) { }
    Range() : lower_(static_cast<ValueType>(0)), upper_(static_cast<ValueType>(0)) { }

    DifferenceType GetSize() const
    { return upper_ - lower_; }

    ValueType GetLower() const
    { return lower_; }

    ValueType GetUpper() const
    { return upper_; }

private:
    ValueType lower_;
    ValueType upper_;
};

} }

#endif /*__RANGE_H__*/
