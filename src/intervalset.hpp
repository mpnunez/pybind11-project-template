#pragma once

#include "interval.hpp"

#include <vector>

struct IntervalSet {

    IntervalSet();
    std::vector<Interval> intervals;

    void insert(int,int);
    int get_total_length() const;
    void sanitize();
    IntervalSet operator&(const IntervalSet& other) const;
    IntervalSet operator-(const IntervalSet& other) const;
    IntervalSet operator|(const IntervalSet& other) const;
    IntervalSet operator^(const IntervalSet& other) const;
    bool operator==(const IntervalSet& other) const;
};