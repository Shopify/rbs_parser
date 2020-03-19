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

T1 = [A]
T2 = [A, B]
T3 = [A, B, C]
T4 = [[A, B], C]
T5 = [A, [B, C], D]
T6 = [A, [B, C]]
