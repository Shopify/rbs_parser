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

class Foo
  extend T::Sig

  sig { params(arg0: A, arg1: B).returns(C) }
  sig { void }
  def foo(arg0, arg1); end

  sig { params(arg0: A, arg1: B).returns(C) }
  sig { params(arg0: C).returns(D) }
  sig { void }
  def bar(arg0, arg1); end

  sig { params(arg0: A, arg1: B).returns(C) }
  sig { params(arg0: C).returns(D) }
  def baz(arg0, arg1); end
end
