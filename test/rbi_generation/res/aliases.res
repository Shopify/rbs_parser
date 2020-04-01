# typed: true

class TestFoo
  sig { params(arg0: Foo2, arg1: Foo::Baz2).returns(Bar2) }
  def foo(arg0, arg1); end
end

module Foo
end

module Foo::Bar
end

FOO = T.type_alias { Integer }
Foo::Baz = T.type_alias { Foo }
::Bar = T.type_alias { ::Foo::Bar }
Foo2 = T.type_alias { Integer }
Foo::Baz2 = T.type_alias { Foo }
::Bar2 = T.type_alias { ::Foo::Bar }
