#include <pybind11/pybind11.h>

int add(int a, int b) { return a + b; }

int plus(int a,int b) {return a*b;}

PYBIND11_MODULE(vocabulary_learning, m) {
    m.def("add", &add, "Add two numbers");
    m.def("plus",&plus,"plus to num");
}