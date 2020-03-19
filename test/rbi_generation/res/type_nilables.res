# typed: true

T1 = T.nilable(Integer)
T2 = T.nilable(::Integer)
T3 = T.nilable(T.all(Integer, String))
T4 = T.nilable(T.any(T.nilable(Integer), T.nilable(String), T.nilable(Object)))
T5 = T.nilable([T.nilable(Integer), T.nilable(String)])
