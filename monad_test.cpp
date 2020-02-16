#include "monad_stl.h"

#include <string>
#include <sstream>
#include <iostream>
 

auto safe_invert = [](const auto& a) {
  using A = std::decay_t<decltype(a)>;
  std::cout << "inv( " << a << " )\n";
  return 
    (a == A(0)) 
      ? std::nullopt 
      : std::optional<A>(1/a);
};

auto decrement = [](const auto& a) -> 
std::optional<std::decay_t<decltype(a)>> {
  std::cout << "dec( " << a << " )\n";
  return {a-1};
};

// if you prefer to use templated classes, you cannot use
// specify templated 
template<class T>
std::optional<T> decrementT(const T& a) {
  std::cout << "dec( " << a << " )\n";
  return {a-1};
};

template <template<class> class T, class A>
requires (Monad<T,A>)
T<A> monad_test(T<A> x) {
  return {
    x ->* safe_invert
      ->* safe_invert
      ->* decrementT<float>
      ->* safe_invert
      ->* safe_invert
      ->* decrement
      ->* safe_invert
      ->* safe_invert
      ->* decrement
      ->* safe_invert
      ->* safe_invert
      ->* decrement
      ->* safe_invert
      ->* safe_invert
  };
}

int main() {
  std::optional<float> x(2.f);
  auto y = monad_test(x);

  // bad bind, lambda does not return an optioal type
  // bindM(x, [](auto& x) { return ++x; } );

  if(x.has_value()) {
    std::cout << "x still valid\n";
  } else {
    std::cout << "x is null\n";
  }


  if(y.has_value()) {
    std::cout << "sequence successful\n";
  } else {
    std::cout << "sequence failed\n";
  }
}