# typed: true

module Foo
end

module ::Bar
end

module Bar::Baz
end

module ::Bar::Baz
end

module Foo::Bar::Baz
end

module ::Foo::Bar::Baz
end
