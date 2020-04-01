# typed: true

class Foo

  sig { type_parameters(:X).params(arg0: T.type_parameter(:X)).returns(T.type_parameter(:X)) }
  def foo(arg0); end

  sig { type_parameters(:X, :Y).params(arg0: [T.type_parameter(:X)], arg1: T.type_parameter(:Y)).returns([T.type_parameter(:X), T.type_parameter(:Y)]) }
  def bar(arg0, arg1); end
end
