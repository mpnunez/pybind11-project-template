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

    def __str__(self):
        return "[{},{}]".format(self.start,self.end)

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
        ret = IntervalSet()
        i = 0
        j = 0
        while (i<len(self.intervals)) and (j<len(other.intervals)):
            if self.intervals[i].overlaps(other.intervals[j],include_ends=False):
                ret.intervals.append(self.intervals[i].intersect(other.intervals[j]))
            
            if self.intervals[i] < other.intervals[j]:
                i += 1
            else:
                j += 1
        
        return ret

    def __sub__(self,other):
        ret =  IntervalSet()

        j = 0
        for itvl in self.intervals:

            # AND with -> add to ret.intervals
            # Keep doing this until you run out of other.intervals
            # or they're > and don't overlap current interval

            left = itvl.start
            right = itvl.end
            while( (left < right) and (j<len(other.intervals)) and not (other.intervals[j].start>=itvl.end) ):
                # If no overlap, other is too far back. Incrememt it
                if other.intervals[j].end <= left:
                    j += 1
                    continue

                # There is definitely overlap here
                if left < other.intervals[j].start:
                    ret.intervals.append(Interval(left,other.intervals[j].start))
                    left = other.intervals[j].end
                else:
                    left = other.intervals[j].end
                    j += 1
                
                

            if left < right:
                ret.intervals.append(Interval(left,right))

        return ret
                

    def __or__(self,other):
        ret = IntervalSet()
        i = 0
        j = 0
        current_interval = None
        while (i < len(self.intervals)) or (j < len(other.intervals)):
            # Pick the next interval to be the min from the two interval sets
            # incrememnt counter for the one that was picked
            if i == len(self.intervals):
                next_interval = other.intervals[j]
                j += 1
            elif j == len(other.intervals):
                next_interval = self.intervals[i]
                i += 1
            else:
                if self.intervals[i] < other.intervals[j]:
                    next_interval = self.intervals[i]
                    i += 1
                else:
                    next_interval = other.intervals[j]
                    j += 1

            # Handle first interval
            if current_interval is None:
                current_interval = next_interval
                continue

            # Test if current_interval overlaps next_interval
            # then merge them and continue
            if current_interval.overlaps(next_interval):
                current_interval = current_interval.merge(next_interval)

            # If no overlap, add current_interval to
            # the running list and set current_interval to next_interval
            else:
                ret.intervals.append(current_interval)
                current_interval = next_interval

        if current_interval is not None:
            ret.intervals.append(current_interval)

        return ret

    def __xor__(self,other):
        return (self - other) | (other - self)

    def __eq__(self,other):
        return self.intervals == other.intervals

    def print(self):
        for i in self.intervals:
            print(i)