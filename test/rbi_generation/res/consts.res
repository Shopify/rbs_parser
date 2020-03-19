# typed: true

module Foo
  extend T::Sig
end

module Foo::Bar
  extend T::Sig
end

FOO = Foo
::BAR = Foo
Foo::FOO = ::Foo
::Foo::Bar::FOO = Foo::Bar
