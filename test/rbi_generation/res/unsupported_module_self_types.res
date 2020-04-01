# typed: true

module Foo
end

module Foo::Bar
end

module Baz
  extend T::Generic

  A = type_member()

  B = type_member()
end
