# typed: true

class Foo
  sig { void }
  def a; end

  sig { returns(Foo) }
  def b; end

  sig { returns(::Foo::Bar) }
  def c; end

  sig { returns(T.nilable(Foo)) }
  def d; end

  sig { returns(T.untyped) }
  def e; end

  sig { returns(T.any(A, B)) }
  def f; end

  sig { returns([A, B]) }
  def g; end
end

module Foo::Bar
end

module A
end

module B
end
