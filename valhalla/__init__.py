from typing import List
import numpy as np

class Interval:
    def __init__(self):
        self.min = 1
        self.max = -1

    @property
    def empty(self):
        return self.min > self.max

class IntervalSet:
    def __init__(self):
        self.intervals = []

    def __and__(self,other):
        return IntervalSet()

    def __sub__(self,other):
        return IntervalSet()

    def __or__(self,other):
        return IntervalSet()

    def __xor__(self,other):
        return IntervalSet()