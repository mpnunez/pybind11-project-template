from valhalla import Interval, IntervalSet
import numpy as np


def test_val2():
    iset = IntervalSet()
    iset.intervals = [
        Interval(0,10),
        Interval(5,15),
        Interval(10,20),
        Interval(15,25),
    ]
    iset.sanitize()

    iset2 = IntervalSet()
    iset2.intervals = [
        Interval(0,25),
    ]

    assert iset == iset2
