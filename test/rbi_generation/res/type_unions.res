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

T1 = T.any(A, B)
T2 = T.any(A, B, C, D)
T3 = T.any(A, B)
T4 = T.any(A, B, C)
T5 = T.any(A, T.any(B, C), D)
T6 = T.any(A, T.any(B, C))
