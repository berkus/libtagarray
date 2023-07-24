#include "tagarray.hpp"
#include <pybind11/pybind11.h>

using namespace tagarray;
namespace py = pybind11;

PYBIND11_MODULE(tagarray, m) {
  py::class_<Record>(m, "Record", py::buffer_protocol())
      .def(py::init([](py::buffer b, int32_t type,
                       const std::string &comment = std::string("")) {
        py::buffer_info info = b.request();
        if (info.ndim > TA_DIMENSIONS_LENGTH)
          throw std::runtime_error("Too many dimensions");
        int64_t data_length = info.itemsize;
        for (const auto &dim_size : info.shape)
          data_length *= dim_size;
        Dimensions dims{0};
        for (int32_t i = 0; i < static_cast<int32_t>(d.size()); i++) {
          if (i < static_cast<int32_t>(info.shape.size())) {
            dims[i] = static_cast<int64_t>(info.shape[i]);
          } else {
            dims[i] = 1;
          }
        }
        return new Record(type, static_cast<int32_t>(info.ndim),
                          static_cast<uint8_t *>(info.ptr), data_length, dims,
                          comment);
      }))
      .def("get_type_id", &Record::get_type_id)
      .def("get_n_dimensions", &Record::get_n_dimensions)
      .def("get_dimensions", &Record::get_dimensions)
      .def("get_comment", &Record::get_comment)
      .def("update_comment",
           py::overload_cast<const std::string &>(&Record::update_comment))
      .def("get_data_lenght", &Record::get_data_length)
      .def("get_data", &Record::get_data)
      .def("set_data",
           [](Record &rec, py::buffer b) {
             py::buffer_info info = b.request();
             if (info.ndim > TA_DIMENSIONS_LENGTH)
               throw std::runtime_error("Too many dimensions");
             int64_t data_length = info.itemsize;
             for (const auto &dim_size : info.shape)
               data_length *= dim_size;
             Dimensions dims{0};
             for (int32_t i = 0; i < static_cast<int32_t>(d.size()); i++) {
               if (i < static_cast<int32_t>(info.shape.size())) {
                 dims[i] = static_cast<int64_t>(info.shape[i]);
               } else {
                 dims[i] = 1;
               }
             }
             rec.set_data(static_cast<uint8_t *>(info.ptr), data_length, dims);
           })
      .def("free_data", &Record::free_data)
      .def("set_shape",
           py::overload_cast<const std::array<int64_t, TA_DIMENSIONS_LENGTH> &>(
               &Record::set_shape))
      .def("is_allocated", &Record::is_allocated)
      .def("get_info", &Record::get_info)
      .def("dump", &Record::dump);
}
