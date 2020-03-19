# typed: true

class Type1
  extend T::Sig
  extend T::Generic

  Elem = type_member()
end

class Type2
  extend T::Sig
  extend T::Generic

  A = type_member()

  B = type_member()
end

module Type3
  extend T::Sig
  extend T::Generic

  A = type_member()

  B = type_member()
end

module Type4
  extend T::Sig
  extend T::Generic

  A = type_member(:in)
end

module Type5
  extend T::Sig
  extend T::Generic

  A = type_member()

  B = type_member(:out)
end
