#include <concepts>

// class Semigroup m where
//   (<>) :: m -> m -> m

//   -- defining sconcat is unnecessary, it has a default implementation
//   sconcat :: NonEmpty m -> m
//   sconcat = ...

//   -- defining stimes is unnecessary, it has a default implementation
//   stimes :: Integral a => a -> m -> m
//   stimes = ...

// infixr 6 <>

// class Semigroup m => Monoid m where
//   mempty :: m

//   -- defining mappend is unnecessary, it copies from Semigroup
//   mappend :: m -> m -> m
//   mappend = (<>)

//   -- defining mconcat is optional, since it has the following default:
//   mconcat :: [m] -> m
//   mconcat = foldr mappend mempty