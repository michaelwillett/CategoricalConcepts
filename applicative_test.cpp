#include "applicative_stl.h"

#include <string>
#include <tuple>
#include <sstream>
#include <iostream>

#include <functional>
 

auto make_tuple = [](auto a, auto b, auto c) {
  using A = decltype(a);
  using B = decltype(b);
  using C = decltype(c);

  return std::tuple<A,B,C>(a,b,c);
};

auto add = [](int a, int b) { return a+b; };
auto add2 = [](int a) { return a+2; };

int main() {

  auto add2p = pure<std::optional, decltype(add2)>(add2);
  auto addp = pure<std::optional, decltype(add)>(add);
  auto c = pure<std::optional, int>(8);
  auto d = pure<std::optional, int>(7);
  // auto b = std::optional<decltype(a)>(a);

  // auto a = pure<std::optional,int>(5);

  auto bf = std::bind_front(add, 1);
  auto bf2 = std::bind_front(bf, 2);

  std::cout << bf2() << "\n" ;

  auto x = liftA(add2p, c);
  auto y = liftA(addp, c);
  auto z = liftA(y, d);

  

  if(x.has_value()) {
    std::cout << "x still valid " << *x << "\n" ;
  } else {
    std::cout << "x is null\n";
  }
    
  if(z.has_value()) {
    std::cout << "y still valid " << *z << "\n" ;
  } else {
    std::cout << "y is null\n";
  }

  using F = decltype(make_tuple);
  auto tuplize = pure<std::optional, F>(make_tuple);

  std::optional<std::string> s{ "hello" };
  std::optional<float> p{ 3.14 };
  auto full_tuple = liftA(liftA(liftA(tuplize, c), s), p);

  if(full_tuple.has_value()) {
    std::cout << "tuple " << std::get<0>(*full_tuple);
    std::cout << ", "     << std::get<1>(*full_tuple);
    std::cout << ", "     << std::get<2>(*full_tuple) << "\n";
  } else {
  std::cout << "tuple is null\n";
  }
}