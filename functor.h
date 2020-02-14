#include <concepts>

namespace details {

  struct Unit{};

  // test if two classes templated on two different types have 
  // the same outer type.  e.g.:
  //   std::vector<int> and std::vector<Unit> are the same kind
  //   std::vertor<int> and std::set<int> are not the same kind

  template <class...>
  constexpr bool same_kind_impl = false;

  // NOTE: we need classes A and B here for T1 and T2 to be defined
  //       even if we don't care about them.
  template <template <class> class T1, class A, 
            template <class> class T2, class B>
  constexpr bool same_kind_impl<T1<A>,A,T2<B>,B> = 
    std::is_same_v<T1<Unit>,T2<Unit>>;

  template <class T1, class A, class T2, class B>
  concept same_kind = same_kind_impl<T1, A, T2, B>;

}

// class Functor f where
//     fmap :: (a -> b) -> f a -> f b

template <class Functor_A, class A, class B = details::Unit>
concept Functor = requires(Functor_A a, B f(A)) {
  { fmap(f, a) } -> details::same_kind<B, Functor_A, A>;
};