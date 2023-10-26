from boopyb import Interval, IntervalSet
import numpy as np

iset = IntervalSet()
iset.insert(Interval(1,4))
iset.insert(Interval(8,12))
iset.insert(Interval(15,20))

iset2 = IntervalSet()
iset2.insert(Interval(3,9))
iset2.insert(Interval(11,12))

def test_normalization():
    iset3 = IntervalSet()
    iset3.insert(Interval(0,10))
    iset3.insert(Interval(5,15))
    iset3.insert(Interval(10,20))
    iset3.insert(Interval(15,25))
    iset3.sanitize()

    iset4 = IntervalSet()
    iset4.insert(Interval(0,25))

    assert iset3 == iset4

def test_union():
    
    expected = IntervalSet()
    expected.insert(Interval(1,12))
    expected.insert(Interval(15,20))

    ans = iset | iset2
    assert (iset | iset2) == expected

def test_intersection():

    expected = IntervalSet()
    expected.insert(Interval(3,4))
    expected.insert(Interval(8,9))
    expected.insert(Interval(11,12))

    assert iset & iset2 == expected

def test_not():
    

    expected = IntervalSet()
    expected.insert(Interval(1,3))
    expected.insert(Interval(9,11))
    expected.insert(Interval(15,20))

    ans = iset - iset2
    assert ans == expected

def test_not2():
    

    expected = IntervalSet()
    expected.insert(Interval(4,8))

    ans = iset2 - iset
    assert ans == expected

def test_xor():

    expected = IntervalSet()
    expected.insert(Interval(1,3))
    expected.insert(Interval(4,8))
    expected.insert(Interval(9,11))
    expected.insert(Interval(15,20))

    ans = (iset ^ iset2)
    assert ans == expected