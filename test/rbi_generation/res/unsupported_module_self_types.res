# typed: true

module Foo
  extend T::Sig
end

module Foo::Bar
  extend T::Sig
end

module Baz
  extend T::Sig
  extend T::Generic

  A = type_member()

  B = type_member()
end
