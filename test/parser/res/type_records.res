1:1-3:1: const: T1 = record
  2:3-2:18: :name => Integer

3:1-9:1: const: T2 = record
  6:3-6:18: "name" => String
  7:3-7:15: 10 => Integer
  8:3-8:14: name => String

9:1-17:1: const: T3 = record
  12:3-16:3: :name => record
    13:5-15:5: "name" => record
      14:7-14:18: name => String

