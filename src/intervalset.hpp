#include "interval.hpp"

#include <vector>

struct IntervalSet {
    std::vector<Interval> intervals;

    int IntervalSet::get_total_length() const;
    void IntervalSet::sanitize();
    IntervalSet operator&(const Inverval& other) const{
    IntervalSet operator-(const IntervalSet& other) const;
    IntervalSet operator|(const IntervalSet& other) const;
    IntervalSet operator^(const IntervalSet& other) const;
    bool operator==(const Interval& other) const;
};