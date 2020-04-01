# typed: true

class Type1
  extend T::Generic

  Elem = type_member()
end

class Type2
  extend T::Generic

  A = type_member()

  B = type_member()
end

module Type3
  extend T::Generic

  A = type_member()

  B = type_member()
end

module Type4
  extend T::Generic

  A = type_member(:in)
end

module Type5
  extend T::Generic

  A = type_member()

  B = type_member(:out)
end

class Type6
  extend T::Generic

  A = type_member(:in)
end

class Type7
  extend T::Generic

  A = type_member()

  B = type_member(:out)
end
