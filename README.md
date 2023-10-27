# cmake_example for pybind11

Sample project from 10/26/23 TD Programmer's Day at Intel

For any questions, please file an issue on Github or contact Marcel Nunez at marcel.nunez@intel.com.

Links
- [Youtube Tutorial](https://www.youtube.com/watch?v=H2wOlriHGmM&ab_channel=FacileTutorials)
- [pybind11 documentation](https://pybind11.readthedocs.io/en/stable/basics.html)
- [Cmake template repository](https://github.com/pybind/cmake_example)
- [pybind11 repository](https://github.com/pybind/pybind11)
- [googletest repository](https://github.com/google/googletest)

Clone with the `--recurse-submodules` flag to clone dependencies.

## Running C++ unit tests

```
cmake -B build
cd build
make
./cboopyb_unit_tests
```

## Running python unit tests

Create and activate a python virtual environment with python version >=3.7.

```
python setup.py install
pip install pytest
python -m pytest -s tests
```
