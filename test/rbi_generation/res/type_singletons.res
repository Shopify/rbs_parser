# typed: true

class A
end

class A::B
end

T1 = T.class_of(A)
T2 = T.class_of(::A)
T3 = T.class_of(A::B)
