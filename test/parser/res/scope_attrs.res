1:1-11:3: class Foo
  2:3-2:23: attr_reader: foo1: Foo
  3:3-3:26: attr_reader: foo2: Foo
  4:3-4:31: attr_reader: foo3 (@ivar): Foo
  5:3-5:23: attr_writer: foo4: Foo
  6:3-6:26: attr_writer: foo5: Foo
  7:3-7:31: attr_writer: foo6 (@ivar): Foo
  8:3-8:25: attr_accessor: foo7: Foo
  9:3-9:28: attr_accessor: foo8: Foo
  10:3-10:33: attr_accessor: foo9 (@ivar): Foo
13:1-17:3: module Foo
  14:3-14:22: attr_reader: foo: Foo
  15:3-15:22: attr_writer: bar: Foo
  16:3-16:24: attr_accessor: baz: Foo
19:1-23:3: interface _Foo
  20:3-20:22: attr_reader: foo: Foo
  21:3-21:22: attr_writer: bar: Foo
  22:3-22:24: attr_accessor: baz: Foo
25:1-29:3: extension (bar) Foo
  26:3-26:22: attr_reader: foo: Foo
  27:3-27:22: attr_writer: bar: Foo
  28:3-28:24: attr_accessor: baz: Foo
