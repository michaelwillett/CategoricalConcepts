#include "maybe.h"

#include <iostream>
 

template <class A>
auto foo(Maybe<A> auto a) { 
  if constexpr (IsNothing<decltype(a)>) 
    return Nothing{};
  else 
    return Just<int>{a.value+2};
};

template <Maybe<int> R>
R NegativeOnly(int x) {
  if (x<0) return Just<int>{x};
  else     return Nothing{};
}

void baz(Maybe<int> auto m) {};

int main() {
  Maybe<int> auto j5 = Just{5};
  Maybe<int> auto no_int = Nothing{};
  Maybe<int> auto unknown = NegativeOnly(5);
  // Maybe<int> auto unknown2 = NegativeOnly(-1);

  auto add = [] (auto& a, auto& b) { return a + b; };
  auto sum = add << j5 << j5;
  Maybe<int> auto add2b = foo<int>(no_int);
  Maybe<int> auto add25 = foo<int>(j5);

  baz(j5);

  if ( !IsNothing<decltype(sum)> ) std::cout << "sum succeeded" << std::endl;
  else std::cout << "sum failed" << std::endl;
}
