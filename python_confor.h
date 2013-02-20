#include <boost/python.hpp>
#include <string>
using namespace boost::python;

struct thing {
    std::string msg;
    void set(const std::string &msg);
    std::string getMsg();
}; 

BOOST_PYTHON_MODULE(testpy) {
    class_<thing>("thing")
        .def("set", &thing::set)
        .def("getMsg", &thing::getMsg);

}

