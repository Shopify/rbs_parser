# typed: true

module A
end

module B
end

module C
end

T1 = T.proc.void
T2 = T.proc.params(arg0: A).returns(C)
T3 = T.proc.params(arg0: A, arg1: B).returns(::C)
T4 = T.proc.params(arg0: A, b: B).void
