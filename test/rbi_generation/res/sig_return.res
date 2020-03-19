# typed: true

class Foo
  extend T::Sig

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
  extend T::Sig
end

module A
  extend T::Sig
end

module B
  extend T::Sig
end
