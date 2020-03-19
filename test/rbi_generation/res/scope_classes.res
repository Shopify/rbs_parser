# typed: true

class Foo
  extend T::Sig
end

class Foo::Bar < Foo
  extend T::Sig
end

class ::Baz < ::Foo::Bar
  extend T::Sig
end
