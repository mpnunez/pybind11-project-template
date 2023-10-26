from typing import List


class Interval:
    """
    start < end
    """
    def __init__(self,start=None,end=None):
        self.start = start if start else 0
        self.end = end if end else 0

    @property
    def length(self):
        return max(0,self.end-self.start)

    def __lt__(self,other):
        return self.start < other.start

    def overlaps(self,other,include_ends=True) -> bool:
        if include_ends:
            return (self.start <= other.end) and (self.end >= other.start)
        return (self.start < other.end) and (self.end > other.start)

    def merge(self,other):
        """
        Merge intervals assuming they overlap
        """

        return Interval(min(self.start,other.start),
            max(self.end,other.end))

    def intersect(self,other):
        return Interval(max(self.start,other.start),
            min(self.end,other.end))

    def __eq__(self,other):
        return (self.start == other.start) and (self.end == other.end)

    def __str__(self):
        return "[{},{}]".format(self.start,self.end)