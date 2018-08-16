# Bynd - A PyBind11 wrapper generator library.

_Bynd_ is a library which defines a DSL-like syntax for generating [PyBind11](https://github.com/pybind/pybind11)
Python) bindings for C and C++.

```c++
#include <project/human.h>
#include <project/child.h>

using Person = project::human.h;
using Child = project::child.h;

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
