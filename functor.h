#ifndef __FUNCTOR__
#define __FUNCTOR__

#include "categories_common.h"
#include <concepts>

static_assert(__cpp_concepts >= 201907, "concepts not supported in this gcc version");

// class Functor f where
//     fmap :: (a -> b) -> f a -> f b

template <template<class> class F, class A, class B = Categories::Unit>
concept Functor = requires(B f(A), F<A> a) {
  { fmap(f, a) } -> std::same_as< F<B> >;
};

template <template<class> class F, class A, class G>
requires (Functor<F,A>)
inline auto operator<<(G g, F<A> fa) -> F<auto> { return fmap(g, fa); };

#endif