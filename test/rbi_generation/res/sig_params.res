# typed: true

class Foo

  def methodA; end

  sig { void }
  def methodB; end

  sig { params(arg0: T.nilable(Integer)).void }
  def methodC(arg0 = nil); end

  sig { params(_: Integer).void }
  def methodD(_); end

  sig { params(arg0: T.nilable(Integer)).void }
  def methodE(arg0 = nil); end

  sig { params(a: Integer).void }
  def methodF(a); end

  sig { params(arg0: ::Integer, arg1: ::String).void }
  def methodG(arg0, arg1); end

  sig { params(arg0: ::Integer, arg1: T.nilable(::String)).void }
  def methodH(arg0, arg1 = nil); end

  sig { params(a: Integer, b: String).void }
  def methodI(a, b); end

  sig { params(arg0: T.nilable(String)).void }
  def methodJ(arg0 = nil); end

  sig { params(a: T.nilable(String)).void }
  def methodK(a = nil); end

  sig { params(a: Integer, b: T.nilable(String)).void }
  def methodL(a, b = nil); end

  sig { params(arg0: String).void }
  def methodM(arg0); end

  sig { params(a: String).void }
  def methodN(a); end

  sig { params(arg0: String, arg1: Integer).void }
  def methodO(arg0, arg1); end

  sig { params(a: Integer, b: String).void }
  def methodP(a, b); end

  sig { params(a: String).void }
  def methodQ(a); end

  sig { params(a: Integer, b: String).void }
  def methodR(a, b); end

  sig { params(a: Integer, b: String).void }
  def methodS(a, b); end

  sig { params(a: Integer, b: String).void }
  def methodT(a, b); end

  sig { params(a: Integer, b: String).void }
  def methodU(a, b); end

  sig { params(a: T.nilable(Integer), b: T.nilable(String)).void }
  def methodZ(a, b); end

  sig { params(a: Integer, b: String).void }
  def methodW(a, b); end
end
