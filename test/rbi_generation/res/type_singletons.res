# typed: true

class A
  extend T::Sig
end

class A::B
  extend T::Sig
end

T1 = T.class_of(A)
T2 = T.class_of(::A)
T3 = T.class_of(A::B)
