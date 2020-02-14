#include "functor.h"
#include "monad.h"
#include <algorithm>

#include <vector>
#include <list>
#include <optional>


// I am unsure why, but the implementations need to be in the std namespace,
// otherwise the compiler fails to find them.
namespace std {

// fmap for vectors
// NOTE: we change the template types from A and B, and instead capture the 
//       function as its own type F so that we can us type deduction from the
//       argument list
template <class Func, class A, class B = std::invoke_result_t<Func,A&>>
std::vector<B> fmap(Func f, std::vector<A>& a) {
  std::vector<B> b(a.capacity());
  std::transform(a.begin(), a.end(), b.begin(), f);
  return b;
};

template <class F, class A, class B = std::invoke_result_t<F,A&>>
std::list<B> fmap(F f, std::list<A>& a) {
  std::list<B> b;
  std::transform(a.begin(), a.end(), b.begin(), f);
  return b;
};

template <class F, class A, class B = std::invoke_result_t<F,A&>>
std::optional<B> fmap(F f, std::optional<A>& a) {
  return { a.has_value() ? f(*a) : std::nullopt };
};

}