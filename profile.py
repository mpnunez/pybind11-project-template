import pyboo
import boopyb
import timeit

def main(mod):

    # For some reason,
    # pybind11 is slower in creation
    # but faster in operations
    A = mod.IntervalSet()
    B = mod.IntervalSet()
    for i in range(10000):
        A.insert(5*i,5*i+3)
        B.insert(5*i+2,5*i+5)

    # Perform boolean operations
    for i in range(100):
        A | B
        A - B
        A & B
        A ^ B

if __name__ == "__main__":
    # start_time = timeit.default_timer()
    # main(pyboo)
    # elapsed = timeit.default_timer() - start_time
    # print(f"Pure-python elapsed time (s): {elapsed}")

    start_time = timeit.default_timer()
    main(boopyb)
    elapsed = timeit.default_timer() - start_time
    print(f"pybind11 elapsed time (s): {elapsed}")
