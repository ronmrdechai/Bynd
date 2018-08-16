# Bynd - A PyBind11 wrapper generator library.

_Bynd_ is a library which defines a DSL-like syntax for generating
[PyBind11](https://github.com/pybind/pybind11) Python bindings for C and C++.

## Usage

To use _Bynd_, create a C++ file which includes the classes you want to wrap.
All bindings sit in a `bynd_wrappers` block. For more information of the various
directives, see the [directives section](directives).

```c++
#include <project/human.h>
#include <project/child.h>

using Human = project::human;
using Child = project::child;

bynd_wrappers {
    bynd_class(Human,
        bynd_constructors( (std::string, unsigned int) ),
        bynd_fields(name, age, height, weight),
        bynd_methods(eat, sleep, grow)
    );

    bynd_class((Child, Human),
        bynd_methods(play)
    );
}
```

_Bynd_ configures the compiler and builds the bindings using _CMake_. To build a
_Bynd_ module, do the following:

```cmake
include(Bynd)

add_bynd_module(project
    DESCRIPTION "This is a C++ project wrapped to Python"    
    SOURCES project_bindings.cc project_other_bindings.cc
    LIBRARIES ${Boost_LIBRARIES}
)
```

This will create a `project.so` file in the current _CMake_ binary directory
which can be imported to Python.

## Directives

TBD
