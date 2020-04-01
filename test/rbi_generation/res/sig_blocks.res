# typed: true

class Foo

  sig { params(_blk: T.proc.void).void }
  def foo1(_blk); end

  sig { params(_blk: T.nilable(T.proc.returns(::Foo))).void }
  def foo2(_blk); end

  sig { params(_blk: T.proc.params(arg0: String, arg1: Integer).returns(Foo)).void }
  def foo3(_blk); end

  sig { params(_blk: T.nilable(T.proc.params(a: String, b: Integer).void)).void }
  def foo4(_blk); end

  sig { params(_blk: T.proc.returns(T.nilable(String))).returns(T.nilable(Foo)) }
  def foo5(_blk); end

  sig { params(_blk: T.proc.params(a: Foo, b: Foo).returns(T.nilable(Foo))).returns(T.nilable(Integer)) }
  def foo6(_blk); end
end
