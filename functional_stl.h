#ifndef __FUNCTIONAL_STL__
#define __FUNCTIONAL_STL__

#include "functor.h"
#include "monad.h"

#include <algorithm>
#include <vector>
#include <list>
#include <optional>


// I am unsure why, but the implementations need to be in the std namespace,
// otherwise the compiler fails to find them.
namespace std {

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//    VECTOR
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

// functor
template <class Func, class A, class B = std::invoke_result_t<Func,A&>>
std::vector<B> fmap(Func f, std::vector<A>& a) {
  std::vector<B> b(a.capacity());
  std::transform(a.begin(), a.end(), b.begin(), f);
  return b;
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//    LIST
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

// functor
template <class F, class A, class B = std::invoke_result_t<F,A&>>
std::list<B> fmap(F f, std::list<A>& a) {
  std::list<B> b;
  std::transform(a.begin(), a.end(), b.begin(), f);
  return b;
};


// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//    OPTIONAL
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

// Functor
template <class F, class A, class B = std::invoke_result_t<F,A&>>
std::optional<B> fmap(F f, std::optional<A>& a) {
  if (a.has_value())
    return {f(*a)};
  else
    return { std::nullopt };
};


template <class A, class B>
std::optional<B> bindM(std::optional<A>& a, std::optional<B> b) {
  return { a.has_value() ? b : std::nullopt };
}


namespace detail {
  template <class...>
  constexpr bool is_optional = false;

  template <class A>
  constexpr bool is_optional<std::optional<A>> = true;
}

template <class F, class A, class B = std::invoke_result_t<F,const A&>>
requires ( detail::is_optional<B> )
B bindM(std::optional<A>& a, F f) {
  return a.has_value() ? f(*a) : std::nullopt;
};


}


#endif