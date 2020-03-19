# typed: true

class Foo
  extend T::Sig

  sig { void }
  def foo; end

  sig { void }
  def self.foo; end

  sig { void }
  def self.bar; end
end
