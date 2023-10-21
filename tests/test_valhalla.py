from valhalla import Interval, IntervalSet
import numpy as np


def test_normalization():
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

def test_union():
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

    expected = IntervalSet()
    expected.intervals = [
        Interval(1,13),
        Interval(15,20),
    ]

    assert iset or iset2 == expected

def test_intersection():
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

    expected = IntervalSet()
    expected.intervals = [
        Interval(3,4),
        Interval(8,9),
        Interval(11,12),
    ]

    assert iset & iset2 == expected

def test_not():
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

    expected = IntervalSet()
    expected.intervals = [
        Interval(1,3),
        Interval(9,11),
        Interval(15,20),
    ]

    assert (iset - iset2) == expected

def test_xor():
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

    expected = IntervalSet()
    expected.intervals = [
        Interval(1,3),
        Interval(4,8),
        Interval(9,11),
        Interval(15,20),
    ]

    assert (iset ^ iset2) == expected