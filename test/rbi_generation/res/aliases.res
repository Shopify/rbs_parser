# typed: true

class TestFoo
  extend T::Sig

  sig { params(arg0: Foo2, arg1: Foo::Baz2).returns(Bar2) }
  def foo(arg0, arg1); end
end

module Foo
  extend T::Sig
end

module Foo::Bar
  extend T::Sig
end

FOO = T.type_alias { Integer }
Foo::Baz = T.type_alias { Foo }
::Bar = T.type_alias { ::Foo::Bar }
Foo2 = T.type_alias { Integer }
Foo::Baz2 = T.type_alias { Foo }
::Bar2 = T.type_alias { ::Foo::Bar }
