// #include <concepts>

// class Semigroup m where
//   mappend :: m -> m -> m

// class Semigroup m => Monoid m where
//   mempty :: m


// template <class M>
// concept Semigroup = requires(M a, M b) {
//   { mappend(a,b) } -> std::same_as< M >;
// };

// template <class M>
// concept Monoid = 
//   requires { Semigroup<M>; } &&
//   requires { mempty<Semigroup<M>>(); };



// TODO: not sure how te define mempty with a separate context from
//       the semigroup, maybe Monoids would be better as a struct?
