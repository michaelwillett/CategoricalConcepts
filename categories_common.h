#ifndef __CATEGORIES_COMMON__
#define __CATEGORIES_COMMON__

#include <functional>


namespace Categories {

  struct Unit{};

  // TODO: use parameter packs and recursion to allow multiple front parameters?
  // TODO: perfect forwarding
  template <class F, class A>
  auto evalutated_bind_front(F f, A a) {
    if constexpr (std::is_invocable_v<F,A>) {
      return f(a);
    } else {
      return std::bind_front(f, a);
    }
  }

  // TODO: perfect forwarding
  auto identity = [](auto& a) { return a; };
}


#endif