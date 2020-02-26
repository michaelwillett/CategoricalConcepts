#include "monad.h"
#include <variant>
#include <type_traits>


template <class A>
struct Just { A value; };

// template <class A = Categories::Unit> 
struct Nothing {};

template <class...>  constexpr bool IsNothing = false;
template <>          constexpr bool IsNothing<Nothing> = true;

template <class...>  constexpr bool IsJust = false;
template <class A>   constexpr bool IsJust<Just<A>> = true;
template <class A>   constexpr bool IsJust<Just<A>, A> = true;



// NOTE: cannot deduce if first type is template... need to check
template <class M, class A> 
concept Maybe = IsNothing<M> || IsJust<M,A>;

template<class F, class A>
auto fmap(F f, Nothing) {
  using B = decltype(Categories::evalutated_bind_front(f,std::declval<A>()));
  return Nothing{};
}

template<class F, class A>
auto fmap(F f, Just<A> a) {
  using B = decltype(Categories::evalutated_bind_front(f,std::declval<A>()));
  return Just<B>{ Categories::evalutated_bind_front(f, a.value) };
}
