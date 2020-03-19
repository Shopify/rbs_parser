# typed: true

module A
  extend T::Sig
end

module B
  extend T::Sig
end

module C
  extend T::Sig
end

module D
  extend T::Sig
end

T1 = T.all(A, B)
T2 = T.all(A, B, C)
T3 = T.all(A, B, C)
T4 = T.all(A, T.all(B, C), D)
T5 = T.all(A, T.all(B, C))
