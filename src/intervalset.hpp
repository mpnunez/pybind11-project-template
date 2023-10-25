#pragma once

#include "interval.hpp"

#include <vector>

struct IntervalSet {

    IntervalSet() = default;
    std::vector<Interval> intervals;

    int get_total_length() const;
    void sanitize();
    IntervalSet operator&(const IntervalSet& other) const;
    IntervalSet operator-(const IntervalSet& other) const;
    IntervalSet operator|(const IntervalSet& other) const;
    IntervalSet operator^(const IntervalSet& other) const;
    bool operator==(const IntervalSet& other) const;
};