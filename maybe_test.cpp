#include "maybe.h"
#include "monad_stl.h"

#include <iostream>
 

static_assert(Functor<std::optional,int>, "optional is not functor");
static_assert(Functor<MaybeD,int>, "MaybeD is not functor");

template <class A>
auto foo(Maybe<A> auto a) { 
  if constexpr (IsNothing<decltype(a)>) 
    return Nothing{};
  else 
    return Just<int>{a.value+2};
};

MaybeD<int> NegativeOnly(int x) {
  if (x<0) return Just<int>{x};
  else     return Nothing{};
}

void baz(Maybe<int> auto m) {};

int main() {
  Maybe<int> auto j5 = Just{5};
  Maybe<int> auto no_int = Nothing{};
  auto unknown = NegativeOnly(-5);
  // Maybe<int> auto unknown2 = NegativeOnly(-1);

  auto add = [] (auto& a, auto& b) { return a + b; };
  auto sum = add << j5 << j5;
  auto sum2 = add << NegativeOnly(-5) << NegativeOnly(-5);

  auto sumn = fmap(add, unknown);
  Maybe<int> auto add2b = foo<int>(no_int);
  Maybe<int> auto add25 = foo<int>(j5);

  baz(j5);

  // if ( !IsNothing<decltype(sum)> ) std::cout << "sum succeeded " << sum << std::endl;
  // else std::cout << "sum failed" << std::endl;

  if ( !std::holds_alternative<Nothing>(sum2.data)  ) 
    std::cout << "sum succeeded " << std::endl;
  else std::cout << "sum failed" << std::endl;
}
