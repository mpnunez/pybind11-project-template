from typing import List
import numpy as np
from itertools import chain

class Interval:
    """
    start < end
    """
    def __init__(self,start=None,end=None):
        self.start = start if start else 0
        self.end = end if end else 0

    @property
    def length(self):
        return min(0,self.end-self.start)

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

class IntervalSet:
    """
    Collection of disjoint invervals
    """
    def __init__(self):
        self.intervals = []

    @property
    def total_length(self):
        return sum(i.length for i in self.intervals)

    def sanitize(self):
        """
        Remove overlaps
        """
        disjoint_intervals = []
        current_interval = None
        for i in sorted(self.intervals):
            if current_interval is None:
                current_interval = i
                continue
            
            if i.overlaps(current_interval):
                current_interval = i.merge(current_interval)
            else:
                disjoint_intervals.append(current_interval)
                current_interval = i

        if current_interval is not None:
            disjoint_intervals.append(current_interval)

        self.intervals = disjoint_intervals

    def __and__(self,other):
        return IntervalSet()

    def __sub__(self,other):
        return IntervalSet()

    def __or__(self,other):
        ret = IntervalSet()
        ret.intervals = self.intervals + other.intervals
        ret.sanitize()
        return ret

    def __xor__(self,other):
        return IntervalSet()

    def __eq__(self,other):
        return self.intervals == other.intervals