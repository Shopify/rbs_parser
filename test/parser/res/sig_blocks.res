1:1-8:3: class Foo
  2:3-2:36: def foo
    2:10-2:36: method_type
      2:10-2:36: signature
        2:33-2:36: void
      2:15-2:28: block
        2:17-2:26: signature
          2:23-2:26: void
  3:3-3:38: def foo
    3:10-3:38: method_type
      3:10-3:38: signature
        3:35-3:38: void
      3:15-3:28: block optional
        3:18-3:28: signature
          3:24-3:28: ::Foo
  4:3-4:39: def foo
    4:10-4:39: method_type
      4:10-4:39: signature
        4:36-4:39: void
      4:15-4:31: block
        4:17-4:29: signature
          4:17-4:18: param: A
          4:19-4:21: param: B
          4:25-4:29: Foo
  5:3-5:45: def foo
    5:10-5:45: method_type
      5:10-5:45: signature
        5:42-5:45: void
      5:15-5:35: block optional
        5:18-5:35: signature
          5:18-5:21: param: A a
          5:22-5:26: param: B b
          5:32-5:35: void
  6:3-6:32: def foo
    6:10-6:32: method_type
      6:10-6:32: signature
        6:26-6:32: Elem?
      6:15-6:23: block
        6:17-6:21: signature
          6:18-6:21: A?
  7:3-7:55: def foo
    7:10-7:55: method_type
      7:10-7:55: signature
        7:49-7:55: Elem?
      7:15-7:46: block
        7:17-7:44: signature
          7:17-7:23: param: Elem a
          7:24-7:31: param: Elem b
          7:35-7:44: Integer?
