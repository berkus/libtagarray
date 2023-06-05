#include "tagarray.hpp"
#include <pybind11/pybind11.h>

using namespace tagarray;
namespace py = pybind11;

PYBIND11_MODULE(tagarray, m) {

  py::class_<Record>(m, "Record")
      //.def(py::init<...>())
      .def("get_type_id", &Record::get_type_id)
      .def("get_n_dimensions", &Record::get_n_dimensions)
      .def("get_status", &Record::get_status)
      .def("get_dimensions", &Record::get_dimensions)
      .def("get_options", &Record::get_options)
      .def("get_comment", &Record::get_comment)
      .def("update_comment", py::overload_cast<const std::string &>(&Record::update_comment))
      .def("get_data_lenght", &Record::get_data_length)
      .def("get_data", &Record::get_data)
      //.def("set_data", py::overload_cast<const int8_t *&, const int64_t, const std::array<int64_t, TA_DIMENSIONS_LENGTH> &>(&Record::set_data))
      .def("free_data", &Record::free_data)
      .def("set_shape", py::overload_cast<const std::array<int64_t, TA_DIMENSIONS_LENGTH> &>(&Record::set_shape))
      .def("set_option", &Record::set_option)
      .def("set_options", py::overload_cast<const std::array<int64_t, TA_OPTIONS_LENGTH> &>(&Record::set_options))
      .def("get_info", &Record::get_info)
      .def("dump", &Record::dump);

  py::class_<Container>(m, "Container")
      .def(py::init<>())
      .def(py::init<const std::string &>())
      .def("get_version", &Container::get_version)
      .def("get_status", &Container::get_status)
      .def("get_comment", &Container::get_comment)
      .def("update_comment", py::overload_cast<const std::string &>(&Container::update_comment))
      .def("add_record", py::overload_cast<const std::string &, Record &>(&Container::add_record))
      .def("has_record", py::overload_cast<const std::string &>(&Container::has_record))
      .def("has_records", &Container::has_records)
      .def("remove_record", py::overload_cast<const std::string &>(&Container::remove_record))
      .def("get_record", py::overload_cast<const std::string &>(&Container::get_record))
      .def("save", py::overload_cast<const std::string &>(&Container::save))
      .def("load", py::overload_cast<const std::string &>(&Container::load))
      .def("dump", &Container::dump);
}
