#ifndef __FUNCTOR__
#define __FUNCTOR__

#include "categories_common.h"
#include <concepts>

static_assert(__cpp_concepts >= 201907, "concepts not supported in this gcc version");

// class Functor f where
//     fmap :: (a -> b) -> f a -> f b

template <template<class> class F, class A, class B = Unit>
concept Functor = requires(F<A> a, B f(A)) {
  { fmap(f, a) } -> std::same_as< F<B> >;
};

#endif