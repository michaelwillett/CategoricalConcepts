#include "functor.h"


#include <functional>

#ifndef __APPLICATIVE__
#define __APPLICATIVE__

// class Functor f => Applicative f where
//     (constructor) :: a -> f a
//     liftA         :: f (a -> b) -> f a -> f b
//     liftA2        :: (a -> b -> c) -> f a -> f b -> f c

template <template<class> class F, class A, class B = Unit, class C = Unit>
concept Applicative = 
  Functor<F,A,B> &&
  requires (A a) 
    { { F<A>(a) } -> std::same_as< F<A> >; } &&
  requires (F<A> fa, F<std::function<B(A)>> f) 
    { { liftA(f, fa) } -> std::same_as< F<B> >; } ||
  requires (F<A> fa, F<B> fb, C f(A,B)) 
    {{ liftA2(f, fa, fb) } -> std::same_as< F<C> >; };


template <template<class> class F, class A>
requires (Applicative<F,A>)
inline F<A> pure(A a) { return F<A>(a); };



#endif