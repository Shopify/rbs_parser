# typed: true

module A
end

module B
end

module C
end

module D
end

module E
end

class Foo
  extend T::Generic

  U = type_member()
end

class Bar
  extend T::Generic

  U = type_member()

  V = type_member()
end

T1 = Foo[Integer]
T2 = Foo[T.nilable(String)]
T3 = ::Bar[Integer, String]
T4 = ::Foo[T.any(Integer, String)]
T5 = ::Foo[T.all(Integer, String)]
T6 = Bar[Bar[Integer, String], Object]
T7 = Foo[Integer, Bar[String, Object], D]
T8 = Foo[Integer, T.nilable(Bar[Object, BasicObject])]
T9 = T.nilable(Foo[Integer, Bar[Object, BasicObject]])
