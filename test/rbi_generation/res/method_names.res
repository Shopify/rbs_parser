# typed: true

class Foo
  extend T::Sig

  sig { void }
  def foo; end

  sig { void }
  def foo=; end

  sig { void }
  def foo?; end

  sig { void }
  def foo!; end

  sig { void }
  def bar; end

  sig { void }
  def ===; end

  sig { void }
  def ==; end

  sig { void }
  def =~; end

  sig { void }
  def !~; end

  sig { void }
  def !=; end

  sig { void }
  def >=; end

  sig { void }
  def <<; end

  sig { void }
  def <=>; end

  sig { void }
  def <=; end

  sig { void }
  def >>; end

  sig { void }
  def >; end

  sig { void }
  def ~; end

  sig { void }
  def +@; end

  sig { void }
  def +; end

  sig { void }
  def []=; end

  sig { void }
  def []; end

  sig { void }
  def -@; end

  sig { void }
  def -; end

  sig { void }
  def /; end

  sig { void }
  def `; end

  sig { void }
  def %; end
end
