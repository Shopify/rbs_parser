# typed: true

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
