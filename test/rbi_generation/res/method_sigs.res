# typed: true

module A
end

module B
end

module C
end

module D
end

class Foo

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
