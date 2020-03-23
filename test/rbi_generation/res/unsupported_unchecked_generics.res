# typed: true

class Foo
  extend T::Sig
  extend T::Generic

  B = type_member()
end

module Bar
  extend T::Sig
  extend T::Generic

  A = type_member(:in)

  B = type_member(:out)
end
