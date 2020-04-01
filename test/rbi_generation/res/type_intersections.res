# typed: true

module A
end

module B
end

module C
end

module D
end

T1 = T.all(A, B)
T2 = T.all(A, B, C)
T3 = T.all(A, B, C)
T4 = T.all(A, T.all(B, C), D)
T5 = T.all(A, T.all(B, C))
