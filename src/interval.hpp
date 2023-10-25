#pragma once

struct Interval {
    int start = 0;
    int end = 0;


    Interval() = default;
    Interval(int, int);

    int get_length() const;
    bool operator<(const Interval& other) const;
    bool overlaps(const Interval& other, bool) const;
    Interval merge(const Interval& other) const;
    Interval intersect(const Interval& other) const;
    bool operator==(const Interval& other) const;
    bool operator!=(const Interval& other) const;

};