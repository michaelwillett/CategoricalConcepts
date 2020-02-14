#include "functional_stl.h"

#include <string>
#include <set>
#include <sstream>
#include <iostream>


template <class T>
concept Incramentible = requires(T& t) { 
  { ++t } -> std::same_as<T&>; 
};

// Test template type deduction and validity with static asserts
template <class...>
constexpr bool incremeting_container = false;

template <template<Incramentible> class F, Incramentible A>
constexpr bool incremeting_container<F<A>> = true;

static_assert(incremeting_container<std::vector<int>>,"");
static_assert(!incremeting_container<std::vector<std::string>>,"");

template <class...>
constexpr bool incremeting_functor = false;

template <template<Incramentible> class F, Incramentible A>
requires (Functor<F<A>,A>)
constexpr bool incremeting_functor<F<A>> = true;

static_assert(incremeting_functor<std::vector<int>>,"");
static_assert(!incremeting_functor<std::set<int>>,"");
static_assert(!incremeting_functor<std::vector<std::string>>,"");


// Test different syntax for requiring functors

template <template<Incramentible> class F, Incramentible A>
requires (Functor<F<A>,A>)
auto incr(F<A>& a) {
  return fmap([](auto& x) { return ++x; }, a);
};

void foo(Incramentible auto) {}

template <class A>
void bar(Functor<A> auto) {}

// testing fmap with different A and B types
template <template<class> class F, class A>
requires (Functor<F<A>,A>)
F<std::string> emph(F<A>& a) {
  return fmap(
    [](const auto& x) { 
      std::ostringstream os;
      os << "__" << x << "__";
      return os.str(); 
    }, a);
}

int main() {

  foo(6);
  // foo(details::Unit{});  // Unit is not Incrementable


  std::vector<int>          xs = {1,5,9};
  Functor<int> auto         is = incr(xs);
  Functor<std::string> auto es = emph(xs);

  std::list<int>            ys = {};
  Functor<int> auto         ss = incr(ys);

  // template type is required here since gcc cannot deduce the
  // type embedded inside the functor
  bar<int>(is);

  // while `is` and `ss` are both Functors on int, 
  // we cannot assign one to the other since their
  // concrete instances are different types (vector and list)
  // is = ss;


  for(auto x : xs) { std::cout << x << '\n'; }
  for(auto i : is) { std::cout << i << '\n'; }
  for(auto e : es) { std::cout << e << '\n'; }
}