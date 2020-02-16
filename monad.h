#include "unit.h"
#include <concepts>

#ifndef __MONAD__
#define __MONAD__

// class Monad m where
//   (constructor) ::   a               -> m a
//   bindM         :: m a -> (a -> m b) -> m b
//   bindM         :: m a ->  m b       -> m b

template <template<class> class M, class A, class B = Unit>
concept Monad = 
requires(A a) 
  { { M<A>(a) } -> std::same_as< M<A> >; } && 
requires(M<A> ma, M<B> f(A)) 
  { { bindM(ma, f) } -> std::same_as< M<B> >; } && 
requires(M<A> ma, M<B> mb) 
  { { bindM(ma, mb) } -> std::same_as< M<B> >; };

// operator for left-associative infix bindM
template <class F, template<class> class M, class A>
requires (Monad<M,A>)
inline auto operator->*(M<A> a, F f) { return bindM(a,f); };

#endif
