#ifndef __FUNCTOR_STL__
#define __FUNCTOR_STL__

#include "functor.h"

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

template <class Func, class A, class B = std::invoke_result_t<Func,A&>>
std::vector<B> fmap(Func f, std::vector<A>& a) {
  std::vector<B> b(a.capacity());
  std::transform(a.begin(), a.end(), b.begin(), f);
  return b;
};

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//    LIST
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template <class F, class A, class B = std::invoke_result_t<F,A&>>
std::list<B> fmap(F f, std::list<A>& a) {
  std::list<B> b;
  std::transform(a.begin(), a.end(), b.begin(), f);
  return b;
};


// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//    OPTIONAL
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template <class F, class A, class B = std::invoke_result_t<F,A&>>
std::optional<B> fmap(F f, std::optional<A>& a) {
  if (a.has_value())
    return {f(*a)};
  else
    return { std::nullopt };
};

}


#endif