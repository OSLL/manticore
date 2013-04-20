#ifndef __RANGE_H__
#define __RANGE_H__

#include <functional>
#include <exception>
#include <string>

namespace manticore { namespace utils {

template <typename LessType>
struct EqualFromLess : public std::binary_function<typename LessType::first_argument_type,
                                                   typename LessType::second_argument_type,
                                                   typename LessType::result_type> {

    typedef std::binary_function<typename LessType::first_argument_type,
                                 typename LessType::second_argument_type,
                                 typename LessType::result_type> BaseType;

    typedef typename BaseType::first_argument_type LeftType;
    typedef typename BaseType::second_argument_type RightType;
    typedef typename BaseType::result_type ResultType;

    EqualFromLess(LessType const & less) : less_(less) { }
    EqualFromLess() { }

    ResultType operator () (LeftType const & left, RightType const & right) const
    { return !less_(left, right) && !less_(right, left); }

private:
    LessType less_;
};

template <typename ValueType_ = size_t, typename DifferenceType_ = ValueType_, typename LessType = std::less<ValueType_> >
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

    bool ContainsStrict(ValueType const & value) const
    { return less_(value, upper_) && less_(lower_, value); }

    bool ContainsNotStrict(ValueType const & value) const
    { return ContainsStrinct(value) || equal_(lower_, value) || equal_(upper_, value); }

private:
    typedef EqualFromLess<LessType> EqualType;

    ValueType lower_;
    ValueType upper_;

    LessType less_;
    EqualType equal_;
};

} }

#endif /*__RANGE_H__*/
