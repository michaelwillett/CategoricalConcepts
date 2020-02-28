#include "monad.h"
#include <variant>
#include <type_traits>
#include <functional>


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

template<class A>
struct MaybeD { 
  MaybeD(Just<A> j) : data{j} {};
  MaybeD(Nothing n) : data{n} {};
  std::variant<Just<A>, Nothing> data; 
};

// NOTE: using declaration will NOT work because it does not match Functor on one template
//       type A, but rather two types <Just<A>, Nothing>
// template <class A>
// using MaybeD = std::variant<Just<A>, Nothing>;


template<class F, class A>
auto fmap(F f, Nothing&) {
  using B = decltype(Categories::evalutated_bind_front(f,std::declval<A>()));
  return Nothing{};
}

template<class F, class A>
auto fmap(F f, Just<A> a) {
  using B = decltype(Categories::evalutated_bind_front(f,std::declval<A>()));
  return Just<B>{ Categories::evalutated_bind_front(f, a.value) };
}

template<class F, class A>
auto fmap(F f, MaybeD<A> a) {
  using B = decltype(Categories::evalutated_bind_front(f,std::declval<A>()));
  auto retv = std::visit([f](auto&& x) -> MaybeD<B> {
            using T = std::decay_t<decltype(x)>;
            if constexpr (std::is_same_v<T, Nothing>) return Nothing{};
            else return Just<B>(Categories::evalutated_bind_front(f, x.value));
          }, a.data);
  return retv;
}