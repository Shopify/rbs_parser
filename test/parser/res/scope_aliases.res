1:1-6:3: class Foo
  2:3-2:15: alias: foo bar
  3:3-3:25: alias: self.foo self.bar
  4:3-4:13: alias: + bar
  5:3-5:17: alias: `foo` bar
8:1-12:3: module Foo
  9:3-9:15: alias: foo bar
  10:3-10:13: alias: bar +
  11:3-11:17: alias: foo `bar`
14:1-18:3: interface _Foo
  15:3-15:15: alias: foo bar
  16:3-16:11: alias: + -
  17:3-17:19: alias: `foo` `bar`
20:1-23:3: extension (bar) Foo
  21:3-21:15: alias: foo bar
  22:3-22:25: alias: self.foo self.bar
