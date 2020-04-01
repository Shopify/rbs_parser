# typed: true

module A
end

module B
end

module C
end

module D
end

T1 = T.any(A, B)
T2 = T.any(A, B, C, D)
T3 = T.any(A, B)
T4 = T.any(A, B, C)
T5 = T.any(A, T.any(B, C), D)
T6 = T.any(A, T.any(B, C))
