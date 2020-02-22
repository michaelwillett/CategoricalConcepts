#ifndef __APPLICATIVE_STL__
#define __APPLICATIVE_STL__

#include "functor_stl.h"
#include "applicative.h"

namespace std {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//    OPTIONAL
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template <class F, class A>
std::optional<auto> applyA(std::optional<F> f, std::optional<A>& a) {
    using B = decltype(detail::evalutated_bind_front(*f,*a));
    return (f.has_value() && a.has_value()) 
              ? std::optional<B>{detail::evalutated_bind_front(*f,*a)}
              : std::nullopt;
}

template <class F, class A, class B, class C = std::invoke_result_t<F,A&,B&>>
std::optional<C> liftA2(F f, std::optional<A>& a, std::optional<B>& b) {
  return 
    (a.has_value() && b.has_value()) 
      ? f(*a,*b) 
      : std::nullopt;
}

}

#endif