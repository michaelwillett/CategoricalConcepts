#include <concepts>

// class Monad m where
//   bind    :: m a -> (a -> m b) -> m b
//   bind    :: m a ->  m b       -> m b
//   returnM ::   a               -> m a

template <class M_A, class A, class M_B = details::Unit>
concept Monad = requires(M_A m_a, A a, M_B f(A)) {
  // { bind(m_a, f) } -> details::same_kind<M_B,M_A,A>;
  // { bind(m_a) } -> details::same_kind<M_B,M_A,A>;
  { returnM(a) } -> std::same_as<M_A>;
};
