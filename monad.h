#include <concepts>
#include <optional>

#ifndef __MONAD__
#define __MONAD__

// class Monad m where
//   bindM         :: m a -> (a -> m b) -> m b
//   bindM         :: m a ->  m b       -> m b
//   (constructor) ::   a               -> m a

template <template<class> class M, class A, class B = Unit>
concept Monad = requires(M<A> m_a, M<B> m_b, A a, M<B> f(A)) {
  { bindM(m_a, f) }   -> std::same_as< M<B> >;
  { bindM(m_a, m_b) } -> std::same_as< M<B> >;
  { M<A>(a) }         -> std::same_as< M<A> >;
};

// operator for left-associative infix bindM
template <class F, template<class> class M, class A>
requires (Monad<M,A>)
inline auto operator->*(M<A> a, F f) { return bindM(a,f); };

#endif
