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
  using B = decltype(Categories::evalutated_bind_front(*f,*a));
  return (f.has_value() && a.has_value()) 
            ? std::optional<B>{Categories::evalutated_bind_front(*f,*a)}
            : std::nullopt;
}

template <class F, class A, class B>
std::optional<auto> liftA2(F f, std::optional<A>& a, std::optional<B>& b) {

  using C = decltype(Categories::evalutated_bind_front(*f,*a,*b));
  return 
    (a.has_value() && b.has_value()) 
      ? std::optional<C>{Categories::evalutated_bind_front(*f,*a,*b)}
      : std::nullopt;
}

}

#endif