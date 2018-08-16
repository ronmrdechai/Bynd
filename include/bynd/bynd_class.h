#pragma once

#include <memory>

#include <bynd/pp/paren_overload.h>
#include <bynd/pp/sequence_transform.h>

namespace bynd {

template <typename T>
struct pointer_holder {
    pointer_holder(T* ptr) : ptr(ptr) {}
    T* get() const { return ptr; }
    T* ptr;
};

} // namespace bynd

PYBIND11_DECLARE_HOLDER_TYPE(T, bynd::pointer_holder<T>, true);

#define _BYND_CLASS_COMMON(cls, ...)\
    __PP_SEQUENCE_TRANSFORM(_BYND_CLASS_DISPATCH, cls, __VA_ARGS__)
#define _BYND_CLASS_BASIC(cls, ...)\
    _BYND_DEFINE_CLASS(cls)\
    _BYND_CLASS_COMMON(cls, __VA_ARGS__)
#define _BYND_CLASS_EXT(args, ...)\
    _BYND_DEFINE_SUBCLASS(__PP_PAIR_FIRST(args), __PP_PAIR_SECOND(args))\
    _BYND_CLASS_COMMON(__PP_PAIR_FIRST(args), __VA_ARGS__)
#define _BYND_CLASS_OVERLOAD(cls)\
    __PP_PAREN_OVERLOAD(cls, _BYND_CLASS_EXT, _BYND_CLASS_BASIC)

#define bynd_fields(...)\
    (_BYND_CLASS_FIELDS, __VA_ARGS__)
#define bynd_rw_fields(...)\
    (_BYND_CLASS_RW_FIELDS, __VA_ARGS__)
#define bynd_static_fields(...)\
    (_BYND_CLASS_STATIC_FIELDS, __VA_ARGS__)
#define bynd_properties(...)\
    (_BYND_CLASS_PROPERTIES, __VA_ARGS__)
#define bynd_rw_properties(...)\
    (_BYND_CLASS_RW_PROPERTIES, __VA_ARGS__)
#define bynd_methods(...)\
    (_BYND_CLASS_METHODS, __VA_ARGS__)
#define bynd_template_methods(...)\
    (_BYND_CLASS_TEMPLATE_METHODS, __VA_ARGS__)
#define bynd_static_methods(...)\
    (_BYND_CLASS_STATIC_METHODS, __VA_ARGS__)
#define bynd_static_template_methods(...)\
    (_BYND_CLASS_STATIC_TEMPLATE_METHODS, __VA_ARGS__)
#define bynd_constructors(...)\
    (_BYND_CLASS_CONSTRUCTORS, __VA_ARGS__)
#define bynd_empty(...)\
    (_BYND_CLASS_EMPTY __VA_ARGS__)

#define bynd_class(cls, ...) _BYND_CLASS_OVERLOAD(cls)(cls, __VA_ARGS__)
#define bynd_unique(cls) cls, std::unique_ptr<cls>
#define bynd_shared(cls) cls, std::shared_ptr<cls>
#define bynd_pointer(cls) cls, bynd::pointer_holder<cls>
