# typed: true

module Foo
  sig { params(a: Integer, b: String).void }
  def foo(a, b); end

  alias bar foo
end

class Bar
  include Foo

  sig { returns(Foo) }
  attr_accessor :foo

  sig { params(foo: Foo).void }
  attr_writer :foo

  sig { returns(Foo) }
  attr_reader :foo
end
