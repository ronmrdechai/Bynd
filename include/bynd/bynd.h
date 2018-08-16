#pragma once

#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <pybind11/stl.h>

namespace bynd {

bool register_wrapper_func(void (*func)(pybind11::module& m));

} // namespace bynd

#define _BYND_WRAPPERS_I(ns)\
    static void ns##_bynd(pybind11::module& m);\
    static bool register_wrapper_func_##ns =\
        ::bynd::register_wrapper_func(ns##_bynd);\
   static void ns##_bynd(py::module& m)
#define _BYND_WRAPPERS(ns) _BYND_WRAPPERS_I(ns)
#define bynd_wrappers _BYND_WRAPPERS(CONCAT(n, __COUNTER__))

#define bynd_constant(var)\
    m.attr(#var) = var

#ifdef BYND_CXX_17
#define bynd_submodule(name, doc)\
    if (auto m_##name = m.def_submodule(#name, doc); true)\
        if (auto& m = m_##name; true)
#endif
