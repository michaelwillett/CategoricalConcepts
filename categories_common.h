#ifndef __CATEGORIES_COMMON__
#define __CATEGORIES_COMMON__

#include <functional>


namespace Categories {

  struct Unit{};

  template <class F, class A>
  auto evalutated_bind_front(F f, A& a) {
    if constexpr (std::is_invocable_v<F,A&>) {
      return f(a);
    } else {
      return std::bind_front(f, a);
    }
  }

  // TODO: perfect forwardin
  auto id = [](auto& a) { return a; };
}


#endif