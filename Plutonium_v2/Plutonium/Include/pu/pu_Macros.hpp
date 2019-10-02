
#pragma once

#include <memory>

// Defines a static function (::New(...)) as a constructor for smart ptrs, also defines a custom type (::Ref) to simplify it
#define PU_SMART_CTOR(_type) \
using Ref = std::shared_ptr<_type>; \
template<typename ...Args> \
static Ref New(Args &&...CtorArgs) \
{ \
    return std::move(std::make_shared<_type>(std::forward<Args>(CtorArgs)...)); \
} \
template<typename T> \
std::shared_ptr< \
    typename std::enable_if<(!std::is_same<_type,T>::value) \
                            &&(std::is_base_of<_type,T>::value),T>::type \
> \
static Conv(std::shared_ptr<_type> ptr){ \
    return std::static_pointer_cast<T>(ptr); \
}
