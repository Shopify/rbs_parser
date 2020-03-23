# typed: true

module ::A
  extend T::Sig

  sig { returns(Integer) }
  def a; end
end

module B
  extend T::Sig

  include A
end

module B::C
  extend T::Sig

  sig { returns(Integer) }
  def c; end
end

module D
  extend T::Sig

  include ::A

  include B::C
end

module E
  extend T::Sig
  extend T::Generic

  A = type_member()

  B = type_member()

  sig { params(_blk: T.proc.params(arg0: A).void).returns(B) }
  def e(_blk); end
end

module F
  extend T::Sig
  extend T::Generic

  A = type_member()

  B = type_member()

  include E

  sig { returns(Integer) }
  def f; end
end
