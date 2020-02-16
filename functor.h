#include "unit.h"
#include <concepts>

#ifndef __FUNCTOR__
#define __FUNCTOR__

// class Functor f where
//     fmap :: (a -> b) -> f a -> f b

template <template<class> class F, class A, class B = Unit>
concept Functor = requires(F<A> a, B f(A)) {
  { fmap(f, a) } -> std::same_as< F<B> >;
};

#endif