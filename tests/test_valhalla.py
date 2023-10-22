from valhalla import Interval, IntervalSet
import numpy as np

iset = IntervalSet()
iset.intervals = [
    Interval(1,4),
    Interval(8,12),
    Interval(15,20),
]

iset2 = IntervalSet()
iset2.intervals = [
    Interval(3,9),
    Interval(11,12),
]

def test_normalization():
    iset3 = IntervalSet()
    iset3.intervals = [
        Interval(0,10),
        Interval(5,15),
        Interval(10,20),
        Interval(15,25),
    ]
    iset3.sanitize()

    iset4 = IntervalSet()
    iset4.intervals = [
        Interval(0,25),
    ]

    assert iset3 == iset4

def test_union():
    
    expected = IntervalSet()
    expected.intervals = [
        Interval(1,12),
        Interval(15,20),
    ]

    ans = iset | iset2
    assert (iset | iset2) == expected

def test_intersection():

    expected = IntervalSet()
    expected.intervals = [
        Interval(3,4),
        Interval(8,9),
        Interval(11,12),
    ]

    assert iset & iset2 == expected

def test_not():
    

    expected = IntervalSet()
    expected.intervals = [
        Interval(1,3),
        Interval(9,11),
        Interval(15,20),
    ]

    ans = iset - iset2
    assert ans == expected

def test_not2():
    

    expected = IntervalSet()
    expected.intervals = [
        Interval(4,8),
    ]

    ans = iset2 - iset
    assert ans == expected

def test_xor():

    expected = IntervalSet()
    expected.intervals = [
        Interval(1,3),
        Interval(4,8),
        Interval(9,11),
        Interval(15,20),
    ]

    ans = (iset ^ iset2)
    assert ans == expected