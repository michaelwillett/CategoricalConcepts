#ifndef __MONAD_STL__
#define __MONAD_STL__

#include "monad.h"

#include <algorithm>
#include <vector>
#include <list>
#include <optional>


namespace std {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//    OPTIONAL
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  
namespace detail {
  template <class...>
  constexpr bool is_optional = false;

  template <class A>
  constexpr bool is_optional<std::optional<A>> = true;
}


template <class A, class B>
std::optional<B> bindM(std::optional<A>& a, std::optional<B> b) {
  return { a.has_value() ? b : std::nullopt };
}

template <class F, class A, class B = std::invoke_result_t<F,const A&>>
requires ( detail::is_optional<B> )
B bindM(std::optional<A>& a, F f) {
  return a.has_value() ? f(*a) : std::nullopt;
};

}

#endif