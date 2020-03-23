1:1-6:3: class Foo
  2:3-2:13: include Bar
  3:3-3:12: extend Bar
  4:3-4:16: prepend Bar[A]
  5:3-5:15: prepend ::Bar
8:1-12:3: module Foo
  9:3-9:15: include ::Bar
  10:3-10:20: extend ::Bar[A, B]
  11:3-11:15: prepend ::Bar
14:1-19:3: interface _Foo
  15:3-15:26: include ::Bar::baz[A, B]
  16:3-16:19: extend ::Bar::baz
  17:3-17:20: prepend ::Bar::baz
  18:3-18:18: prepend Bar::baz
21:1-25:3: extension (bar) Foo
  22:3-22:18: include Bar::baz
  23:3-23:17: extend Bar::Baz
  24:3-24:18: prepend Bar::baz
