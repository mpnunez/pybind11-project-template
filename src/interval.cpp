#include "interval.cpp"

Interval::Interval(int s, int e): start(e), end(e) {}

int Interval::get_length() const{
    return std::max(0,end-start);
}

bool Interval::operator<(const Interval& other) const{
    return start < other.start;
}

bool Interval::overlaps(const Interval& other, bool include_ends) const{
    if(include_ends)
        return (start <= other.end) and (end >= other.start);
    return (start < other.end) and (end > other.start);
}

Interval Interval::merge(const Invterval& other) const{
    return Interval(
        std::min(start,other.start),
        std::max(end,other.end)
    );
}


Interval Interval::intersect(const Interval& other) const{
    return Interval(
        std::max(start,other.start),
        std::min(end,other.end)
    );
}

bool Interval::operator==(const Interval& other) const{
    return (start == other.start) and (end == other.end);
}

