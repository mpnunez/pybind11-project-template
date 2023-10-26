#include <pybind11/pybind11.h>

#include "interval.hpp"
#include "intervalset.hpp"

#include <iostream>
#include <memory>

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

    py::class_<Interval>(m, "Interval",
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
      .def(py::init<>())
      .def(py::init([](int x, int y) {
          return std::make_unique<Interval>(x,y);
           }),py::arg("x"), py::arg("y"))
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


    py::class_<IntervalSet>(m, "IntervalSet",
                                 R"pbdoc(
                    Stores a list of ordered disjoint intervals.

                    Attributes
                    -----------
                    intervals : list
                        List of ordered disjoint intervals

                )pbdoc")
      .def(py::init<>())
      .def_property_readonly("total_length",&IntervalSet::get_total_length)
      .def_property_readonly("intervals",[](const IntervalSet& itvls){return itvls.intervals;})
      .def("insert",[](IntervalSet &itvls, const Interval &itvl) {
          itvls.intervals.push_back(itvl);
          })
      .def("insert",[](IntervalSet &itvls, int s, int e) {
          itvls.intervals.emplace_back(s,e);
          })
      .def("sanitize",&IntervalSet::sanitize)
      .def("__and__",&IntervalSet::operator&)
      .def("__sub__",&IntervalSet::operator-)
      .def("__or__",&IntervalSet::operator|)
      .def("__xor__",&IntervalSet::operator^)
      .def("__eq__",&IntervalSet::operator==)
      .def("print",[](const IntervalSet &itvls) {
          for(auto const& itvl: itvls.intervals){
              std::cout << "["+std::to_string(itvl.start)
          + ","+std::to_string(itvl.end)+"]\n";
          }
          })
      ;

    m.attr("__version__") = "1.0.0";

}
