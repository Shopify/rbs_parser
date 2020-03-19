1:1-14:3: class Foo
  2:5-2:12: def foo
  3:5-3:20: def foo
    3:12-3:20: method_type
      3:12-3:20: signature
        3:17-3:20: void
  4:5-4:26: def foo
    4:12-4:26: method_type
      4:12-4:26: signature
        4:14-4:17: param: Bar
        4:23-4:26: void
  5:5-5:30: def foo
    5:12-5:30: method_type
      5:12-5:30: signature
        5:14-5:21: param: Bar bar
        5:27-5:30: void
  6:5-6:38: def foo
    6:12-6:38: method_type
      6:12-6:38: signature
        6:14-6:17: param: Bar
        6:20-6:29: param: ::Baz::Baz
        6:35-6:38: void
  7:5-7:46: def boo
    7:12-7:46: method_type
      7:12-7:46: signature
        7:14-7:21: param: Bar bar
        7:24-7:37: param: ::Baz::Baz baz
        7:43-7:46: void
  8:5-8:19: def foo
    8:12-8:19: method_type
      8:12-8:19: signature
        8:15-8:19: Foo
  9:5-9:27: def foo
    9:12-9:27: method_type
      9:12-9:27: signature
        9:14-9:17: param: Bar
        9:23-9:27: ::Foo
  10:5-10:36: def foo
    10:12-10:36: method_type
      10:12-10:36: signature
        10:14-10:21: param: Bar bar
        10:27-10:36: ::Foo::Bar
  11:5-11:42: def foo
    11:12-11:42: method_type
      11:12-11:42: signature
        11:14-11:17: param: Bar
        11:20-11:29: param: ::Baz::Baz
        11:35-11:42: Foo::Bar
  12:5-12:52: def foo
    12:12-12:20: method_type
      12:12-12:20: signature
        12:17-12:20: void
    12:22-12:52: method_type
      12:22-12:52: signature
        12:24-12:27: param: Bar
        12:30-12:39: param: ::Baz::Baz
        12:45-12:52: Foo::Bar
  13:5-13:72: def foo
    13:12-13:20: method_type
      13:12-13:20: signature
        13:17-13:20: void
    13:22-13:40: method_type
      13:22-13:40: signature
        13:24-13:31: param: Bar bar
        13:37-13:40: void
    13:42-13:72: method_type
      13:42-13:72: signature
        13:44-13:47: param: Bar
        13:50-13:59: param: ::Baz::Baz
        13:65-13:72: Foo::Bar
