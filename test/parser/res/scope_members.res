1:1-9:3: class Foo
  2:3-2:13: include Foo
  3:3-3:12: extend Bar
  4:3-4:13: prepend Baz
  5:3-5:9: private
  6:3-6:29: def foo
    6:10-6:29: method_type
      6:10-6:29: signature
        6:12-6:15: param: A a
        6:16-6:20: param: B b
        6:26-6:29: void
  7:3-7:8: public
  8:3-8:15: alias: bar foo
11:1-19:3: module Foo
  12:3-12:13: include Foo
  13:3-13:12: extend Bar
  14:3-14:13: prepend Baz
  15:3-15:9: private
  16:3-16:29: def foo
    16:10-16:29: method_type
      16:10-16:29: signature
        16:12-16:15: param: A a
        16:16-16:20: param: B b
        16:26-16:29: void
  17:3-17:8: public
  18:3-18:15: alias: bar foo
21:1-29:3: interface _Foo
  22:3-22:13: include Foo
  23:3-23:12: extend Bar
  24:3-24:13: prepend Baz
  25:3-25:9: private
  26:3-26:29: def foo
    26:10-26:29: method_type
      26:10-26:29: signature
        26:12-26:15: param: A a
        26:16-26:20: param: B b
        26:26-26:29: void
  27:3-27:8: public
  28:3-28:15: alias: bar foo
31:1-39:3: extension (bar) Foo
  32:3-32:13: include Foo
  33:3-33:12: extend Bar
  34:3-34:13: prepend Baz
  35:3-35:9: private
  36:3-36:29: def foo
    36:10-36:29: method_type
      36:10-36:29: signature
        36:12-36:15: param: A a
        36:16-36:20: param: B b
        36:26-36:29: void
  37:3-37:8: public
  38:3-38:15: alias: bar foo
