#include "applicative_stl.h"

#include <string>
#include <tuple>
#include <sstream>
#include <iostream>
 

auto make_tuple = [](auto a, auto b, auto c) {
  using A = decltype(a);
  using B = decltype(b);
  using C = decltype(c);

  return std::tuple<A,B,C>(a,b,c);
};

auto add = [](int a, int b) { return a+b; };
auto add2 = [](int a) { return a+2; };

int main() {

  auto add2p = pureA<std::optional, decltype(add2)>(add2);
  auto addp = pureA<std::optional, decltype(add)>(add);
  auto c = pureA<std::optional, int>(8);
  std::optional<int> d = std::nullopt;


  auto x = applyA(add2p, c);
  auto y = addp << c << d;


  if(x.has_value()) {
    std::cout << "x still valid " << *x << "\n" ;
  } else {
    std::cout << "x is null\n";
  }
    
  if(y.has_value()) {
    std::cout << "y still valid " << *y << "\n" ;
  } else {
    std::cout << "y is null\n";
  }

  std::optional<std::string> s{ "hello" };
  std::optional<float> p{ 3.14 };
  
  auto full_tuple = make_tuple << c << s << p;

  if(full_tuple.has_value()) {
    std::cout << "tuple " << std::get<0>(*full_tuple);
    std::cout << ", "     << std::get<1>(*full_tuple);
    std::cout << ", "     << std::get<2>(*full_tuple) << "\n";
  } else {
  std::cout << "tuple is null\n";
  }
}