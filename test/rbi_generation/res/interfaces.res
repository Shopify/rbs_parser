# typed: true

module ::A

  sig { returns(Integer) }
  def a; end
end

module B

  include A
end

module B::C

  sig { returns(Integer) }
  def c; end
end

module D

  include ::A

  include B::C
end

module E
  extend T::Generic

  A = type_member()

  B = type_member()

  sig { params(_blk: T.proc.params(arg0: A).void).returns(B) }
  def e(_blk); end
end

module F
  extend T::Generic

  A = type_member()

  B = type_member()

  include E

  sig { returns(Integer) }
  def f; end
end
