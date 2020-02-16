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
requires (Functor<F,A>)
constexpr bool incremeting_functor<F<A>> = true;

// static_assert(incremeting_functor<std::vector<int>>,"");
static_assert(!incremeting_functor<std::set<int>>,"");
static_assert(!incremeting_functor<std::vector<std::string>>,"");

// Test different syntax for requiring functors

template <template<Incramentible> class F, Incramentible A>
requires (Functor<F,A>)
F<A> incr(F<A>& a) {
  return fmap([](auto& x) { return ++x; }, a);
};

template <template<Incramentible> class F, Incramentible A>
requires (Functor<F,A>)
F<A> operator ++(F<A>& a) { return incr(a); }

void foo(Incramentible auto) {}

// testing fmap with different A and B types
template <template<class> class F, class A>
requires (Functor<F,A>)
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
  std::vector<int>          is = ++xs;
  std::vector<std::string>  es = emph(xs);

  std::list<int>            ys = {};
  std::list<int>            ss = incr(ys);

  std::optional<float>      maybe = 3.4f;
  std::optional<float>      nothing = std::nullopt;


  if ((++maybe).has_value()) { 
    std::cout << *maybe << '\n'; 
  } else {
    std::cout << "no value" << '\n'; 
  }


  std::cout << "--- safe increment of nothing: " << '\n'; 
  std::cout << *nothing << " -> "; 
  ++nothing;
  std::cout << *nothing << "\n---\n"; 


  // if we don't use the fmap to wrap the increment funtion call,
  // we see that std::optional uses the default constructor, then calls
  // operator++() anyway.
  std::cout << "--- unsafe increment of nothing: " << '\n'; 
  std::cout << *nothing << " -> "; 
  ++(*nothing);
  std::cout << *nothing << "\n---\n"; 

  // while `is` and `ss` are both Functors on int, 
  // we cannot assign one to the other since their
  // concrete instances are different types (vector and list)
  // is = ss;


  for(auto x : xs) { std::cout << x << '\n'; }
  for(auto i : is) { std::cout << i << '\n'; }
  for(auto e : es) { std::cout << e << '\n'; }
}