# typed: true

module Foo
  extend T::Sig
end

module ::Bar
  extend T::Sig
end

module Bar::Baz
  extend T::Sig
end

module ::Bar::Baz
  extend T::Sig
end

module Foo::Bar::Baz
  extend T::Sig
end

module ::Foo::Bar::Baz
  extend T::Sig
end
