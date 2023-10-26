#include <pybind11/pybind11.h>

#include "interval.hpp"
#include "intervalset.hpp"

int add(int i, int j) {
    return i + j;
}

namespace py = pybind11;

PYBIND11_MODULE(boopyb, m) {
    m.doc() = R"pbdoc(
        Pybind11 example plugin
        -----------------------

        .. currentmodule:: boopyb

        .. autosummary::
           :toctree: _generate

           Interval
           IntervalSet
    )pbdoc";

    py::class_<Interval>(m, "Geometry",
                                 R"pbdoc(
                    Stores an interval with integral endpoints.
                    The interval always has a positive length.

                    Attributes
                    -----------
                    start : int
                        Start of the interval
                    end : int
                        End of the interval
                    length : int
                        end - start

                )pbdoc")
      .def_property_readonly("start",
                             [](Interval &itvl) { return itvl.start; })
      .def_property_readonly("end",
                             [](Interval &itvl) { return itvl.end; })
      .def_property_readonly("length",&Interval::get_length)
      .def("__lt__",&Interval::operator<)
      .def("overlaps",&Interval::overlaps)
      .def("merge",&Interval::merge)
      .def("intersect",&Interval::intersect)
      .def("__eq__",&Interval::operator==)
      .def(" __str__",[](Interval &itvl) {
          return "["+std::to_string(itvl.start)
          + ","+std::to_string(itvl.end)+"]";
          })
      ;

    m.attr("__version__") = "1.0.0";

}
