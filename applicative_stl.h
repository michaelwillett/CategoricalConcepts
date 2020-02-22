#ifndef __APPLICATIVE_STL__
#define __APPLICATIVE_STL__

#include "applicative.h"
#include "functor_stl.h" // applicative requires Funtor for all types


static_assert(__cpp_concepts >= 201907, "concepts not supported in this version");

namespace std {

namespace detail {
  template <class F, class A>
  auto bind_front_eval(F f, A& a) {
    if constexpr (std::is_invocable_v<F,A&>) {
      return f(a);
    } else {
      return std::bind_front(f, a);
    }
  }
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//    OPTIONAL
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template <class F, class A>
std::optional<auto> liftA(std::optional<F> f, std::optional<A>& a) {
    using B = decltype(detail::bind_front_eval(*f,*a));
    return (f.has_value() && a.has_value()) 
              ? std::optional<B>{detail::bind_front_eval(*f,*a)}
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