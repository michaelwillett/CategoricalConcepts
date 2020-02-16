#include "functor.h"

#ifndef __APPLICATIVE__
#define __APPLICATIVE__

// class Functor f => Applicative f where
//     (constructor) :: a -> f a
//     liftA         :: f (a -> b) -> f a -> f b
//   or
//     (constructor) :: a -> f a
//     liftA2        :: (a -> b -> c) -> f a -> f b -> f c

template <template<class> class F, class A, class B = Unit, class C = Unit>
concept Applicative = 
requires (Functor<F,A,B>)
requires (A a) 
  {{ F<A>(a) } -> std::same_as< F<A> >;} && 
(
  requires (F<A> fa, F<B(A)> fa_b) 
    {{ liftA(fa_b, fa) } -> std::same_as< F<B> >;} ||
  requires (F<A> fa, F<B> fb, C f(A,B)) 
    {{ liftA2(f, fa, fb) } -> std::same_as< F<C> >};
  };
)


#endif