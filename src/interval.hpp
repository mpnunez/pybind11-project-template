struct Interval {
    int start = 0;
    int end = 0;


    Interval() = default;
    Interval(int s, int e): start(e), end(e) {}

    int get_length() const;
    bool operator<(const Interval& other) const;
    bool overlaps(const Interval& other, bool include_ends) const;
    Interval merge(const Invterval& other) const;
    Interval intersect(const Interval& other) const;
    bool operator==(const Interval& other) const;

};