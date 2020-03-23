# RBS & RBI comparison


## Declarations

| Construct                             | RBS  | RBI  |
| ------------------------------------- | ---- | ---- |
| class                                 |  ✅  |  ✅  |
| class parent                          |  ✅  |  ✅  |
| class abstract                        |  ❌  |  ✅  |
| class final                           |  ❌  |  ✅  |
| class sealed                          |  ❌  |  ✅  |
| module                                |  ✅  |  ✅  |
| module final                          |  ❌  |  ✅  |
| module self type                      |  ✅  |  ❌  |
| interface                             |  ✅  |  🔶  |
| extension                             |  ✅  |  ❌  |
| struct                                |  ❌  |  ✅  |
| type alias                            |  ✅  |  ✅  |
| constant                              |  ✅  |  ✅  |
| global                                |  ✅  |  ❌  |

### Class declaration

A class is declared thanks to the `class` keyword in both RBS and RBI.

```rbs:class
class Student
end
```

```rbi
class Student
  extend T::Sig
end
```

Class declaration can have a superclass. When you omit superclass, `::Object` is assumed.

```rbs:class_parent
class Student < Person
end
```

```rbi
class Student < Person
  extend T::Sig
end
```

### Module declaration

```rbs:module
module Enumerable
end
```

```rbi
module Enumerable
  extend T::Sig
end
```

Module declaration takes optional self type parameter, which defines a constraint about a class when the module is mixed.

```
interface _Each[A, B]
  def each: { (A) -> void } -> B
end

module Enumerable[A, B] : _Each[A, B]
  def count: () -> Integer
end
```

The Enumerable method above requires each method for enumerating objects.

**Unsupported: This has no equivalent in RBI.**

### Interface declaration

Interface declaration can have parameters but allows only a few of the members.

```rbs:interface
interface _Hashing
  def hash: () -> Integer
  def eql?: (any) -> bool
end
```

```rbi
module Hashing
  extend T::Sig

  sig { returns(Integer) }
  def hash; end

  sig { params(arg0: T.untyped).returns(T::Boolean) }
  def eql?(arg0); end
end
```

There are several limitations which are not described in the grammar.

1. Interface cannot include modules
2. Interface cannot have singleton method definitions

```
interface _Foo
  include Bar                  # Error: cannot include modules
  def self.new: () -> Foo      # Error: cannot include singleton method definitions
end
```

### Extension declaration

Extension is to model open class.

```
extension Kernel (Pathname)
  def Pathname: (String) -> Pathname
end

extension Array[A] (ActiveSupport)
  def to: (Integer) -> Array[A]
  def from: (Integer) -> Array[A]
  def second: () -> A?
  def third: () -> A?
end
```

**Unsupported: This has no equivalent in RBI.**

### Type alias declaration

You can declare an alias of types.

```rbs:type_alias
type subject = Attendee | Speaker
type JSON::t = Integer | TrueClass | FalseClass | String | Hash[Symbol, t] | Array[t]
```

```rbi
Subject = T.type_alias { T.any(Attendee, Speaker) }
JSON::T = T.type_alias { T.any(Integer, TrueClass, FalseClass, String, T::Hash[Symbol, T], T::Array[T]) }
```

### Constant type declaration

You can declare a constant.

```rbs:constant
Person::DefaultEmailAddress: String
```

```rbi
Person::DefaultEmailAddress = String
```

### Global type declaration

You can declare a global variable.

```
$LOAD_PATH: Array[String]
```

**Unsupported: This has no equivalent in RBI.**

## Members

| Construct                             | RBS  | RBI  |
| ------------------------------------- | ---- | ---- |
| ivar                                  |  ✅  |  ❌  |
| method                                |  ✅  |  ✅  |
| method multiple signatures            |  ✅  |  🔶  |
| method self                           |  ✅  |  ✅  |
| method self?                          |  ✅  |  🔶  |
| method super                          |  ✅  |  ❌  |
| method final                          |  ❌  |  ✅  |
| method override                       |  ❌  |  ✅  |
| attr reader                           |  ✅  |  ✅  |
| attr writer                           |  ✅  |  ✅  |
| attr accessor                         |  ✅  |  ✅  |
| attr instance variable                |  ✅  |  ❌  |
| mixin                                 |  ✅  |  ✅  |
| mixin interface                       |  ✅  |  ❌  |
| alias                                 |  ✅  |  🔶  |
| visibility                            |  ✅  |  ❌  |

### Ivar definition

An instance variable definition consists of the name of an instance variable and its type.

```
class Student
  @name: String
  @year: Integer
end
```

**Unsupported: This has no equivalent in RBI.**

### Method definition

Method definition has several syntax variations.

You can write `self.` or `self?.` before the name of the method to specify the kind of method: instance, singleton, or both instance and singleton.

```rbs:method
class Foo
  def to_s: () -> String                        # Defines a instance method
  def self.new: () -> AnObject                  # Defines singleton method
  def self?.sqrt: (Numeric) -> Numeric          # self? is for `module_function`
end
```

```rbi
class Foo
  extend T::Sig

  sig { returns(String) }
  def to_s; end

  sig { returns(AnObject) }
  def self.new; end

  sig { params(arg0: Numeric).returns(Numeric) }
  def self.sqrt(arg0); end
end
```

A parameter can be a type or a pair of type and variable name. Variable name can be used for documentation.

```rbs:method_params
class Foo
  # Two required positional `Integer` parameters, and returns `String`
  def f1: (Integer, Integer) -> String

  # Two optional parameters `size` and `name`.
  # `name` is a optional parameter with optional type so that developer can omit, pass a string, or pass `nil`.
  def f2: (?Integer size, ?String? name) -> String

  # Method type with a rest parameter
  def f3: (Integer, *Integer) -> void

  # `size` is a required keyword, with variable name of `sz`.
  # `name` is a optional keyword.
  # `created_at` is a optional keyword, and the value can be `nil`.
  def f4: (size: Integer sz, ?name: String, ?created_at: Time?) -> void
end
```

```rbi
class Foo
  extend T::Sig

  sig { params(arg0: Integer, arg1: Integer).returns(String) }
  def f1(arg0, arg1); end

  sig { params(size: T.nilable(Integer), name: T.nilable(String)).returns(String) }
  def f2(size, name); end

  sig { params(arg0: Integer, arg1: Integer).void }
  def f3(arg0, arg1); end

  sig { params(size: Integer, name: String, created_at: T.nilable(Time)).void }
  def f4(size, name, created_at); end
end
```

The method type can be connected with `|`s to define an overloaded method.

```rbs:methods
class Foo
  def +: (Float) -> Float
       | (Integer) -> Integer
       | (Numeric) -> Numeric
end
```

```rbi
class Foo
  extend T::Sig

  sig { params(arg0: Float).returns(Float) }
  sig { params(arg0: Integer).returns(Integer) }
  sig { params(arg0: Numeric).returns(Numeric) }
  def +(arg0); end
end
```

You need extra parentheses on return type to avoid ambiguity.

```rbs:method_returns
class Foo
  def +: (Float | Integer) -> (Float | Integer)
       | (Numeric) -> Numeric
end
```

```rbi
class Foo
  extend T::Sig

  sig { params(arg0: T.any(Float, Integer)).returns(T.any(Float, Integer)) }
  sig { params(arg0: Numeric).returns(Numeric) }
  def +(arg0); end
end
```

Method types can end with super which means the methods from existing definitions. This is useful to define an extension, which adds a new variation to the existing method preserving the original behavior.

**Unsupported: This has no equivalent in RBI.**

### Attribute definition

Attribute definitions help to define methods and instance variables based on the convention of `attr_reader`, `attr_writer` and `attr_accessor` methods in Ruby.

```rbs:attr
class Student
  attr_reader name: String
  attr_writer age: Integer
  attr_accessor last_login: Date
end
```

```rbi
class Student
  extend T::Sig

  sig { returns(String) }
  attr_reader :name

  sig { params(age: Integer).void }
  attr_writer :age

  sig { returns(Date) }
  attr_accessor :last_login
end
```

You can specify the name of instance variable using (`@some_name`) syntax and also omit the instance variable definition by specifying `()`.

```
class Student
  attr_writer name (@raw_name) : String
  attr_accessor friends (): Array[Person]
end
```

### Mixin (`include`), Mixin (`extend`), Mixin (`prepend`)

You can define mixins between class and modules.

```rbs:mixin
class Foo
  include Kernel
  include Enumerable[String, void]
  extend ActiveSupport::Concern
end
```

[[rbi::mixin]]

You can also include or extend an interface.

```rbs:mixin_interface
class Foo
  include _Hashing
  extend _LikeString
end
```

```rbi
class Foo
  extend T::Sig

  include Hashing

  extend LikeString
end
```

### Alias

You can define an alias between methods.

```rbs:alias
class Student
  def name: -> String
  alias first_name name      # `#first_name` has the same type with `name`
end
```

```rbi
class Student
  extend T::Sig

  sig { returns(String) }
  def name; end

  alias first_name name
end
```

### `public`, `private`

`public` and `private` allows specifying the visibility of methods.

These work only as statements, not per-method specifier.

**Unsupported: This has no equivalent in RBI.**

## Types

| Construct                             | RBS  | RBI  |
| ------------------------------------- | ---- | ---- |
| class instance                        |  ✅  |  ✅  |
| class singleton                       |  ✅  |  ✅  |
| interface                             |  ✅  |  🔶  |
| alias                                 |  ✅  |  🔶  |
| literal                               |  ✅  |  🔶  |
| union                                 |  ✅  |  ✅  |
| intersection                          |  ✅  |  ✅  |
| optional                              |  ✅  |  ✅  |
| record                                |  ✅  |  ✅  |
| tuple                                 |  ✅  |  ✅  |
| enum                                  |  ❌  |  ✅  |
| type parameters                       |  ✅  |  ✅  |
| type parameters bound                 |  ❌  |  ✅  |
| type parameters variance              |  ✅  |  ✅  |
| type parameters unchecked             |  ✅  |  ❌  |
| method type parameters                |  ✅  |  ✅  |
| proc                                  |  ✅  |  ✅  |
| attached class                        |  ❌  |  ✅  |
| base types                            |  ✅  |  🔶  |

### Class instance type

Class instance type denotes an instance of a class.

```rbs:type_instance
T1: Integer
T2: ::Integer
T3: Hash[Symbol, String]
```

```rbi
T1 = Integer
T2 = ::Integer
T3 = T::Hash[Symbol, String]
```

### Class singleton type

Class singleton type denotes the type of a singleton object of a class.

```rbs:type_singleton
T1: singleton(String)
T2: singleton(::Hash)      # Class singleton type cannot be parametrized.
```

```rbi
T1 = T.class_of(String)
T2 = T.class_of(::Hash)
```

### Interface type

Interface type denotes type of a value which can be a subtype of the interface.

```rbs:type_interface
T1: _ToS                          # _ToS interface
T2: ::MyApp::_Each[String]        # Interface name with namespace and type application
```

```rbi
T1 = ToS
T2 = ::MyApp::Each[String]
```

### Alias type

Alias type denotes an alias declared with alias declaration.

The name of type aliases starts with lowercase [a-z].

```rbs:ref_alias
T1: name
T2: ::JSON::t                    # Alias name with namespace
```

```rbi
T1 = Name
T2 = ::JSON::T
```

### Literal type

Literal type denotes a type with only one value of the literal.

```rbs:type_literals
T1: 123                         # Integer
T2: "hello world"               # A string
T3: :to_s                       # A symbol
T4: true                        # true or false
```

Literals are translated to their class names in RBI:

```rbi
T1 = Integer
T2 = String
T3 = Symbol
T4 = T::Boolean
```

### Union type

Union type denotes a type of one of the given types.

```rbs:type_unions
T1: Integer | String           # Integer or String
T2: Array[Integer | String]    # Array of Integer or String
```

```rbi
T1 = T.any(Integer, String)
T2 = T::Array[T.any(Integer, String)]
```

### Intersection type

Intersection type denotes a type of all of the given types.

```rbs:type_inters
T1: Integer & String           # Integer and String
```

Note that & has higher precedence than | that Integer & String | Symbol is (Integer & String) | Symbol.

```rbi
T1 = T.all(Integer, String)
```

### Optional type

Optional type denotes a type of value or nil.

```rbs:type_optionals
T1: Integer?
T2: Array[Integer?]
```

```rbi
T1 = T.nilable(Integer)
T2 = T::Array[T.nilable(Integer)]
```

### Record type

Records are Hash objects, fixed set of keys, and heterogeneous.

```rbs:records
T1: { id: Integer, name: String }     # Hash object like `{ id: 31, name: String }`
```

```rbi
T1 = { id: Integer, name: String }
```

### Tuple type

Tuples are Array objects, fixed size and heterogeneous.

```rbs:type_tuples
T1: [ ]                               # Empty like `[]`
T2: [String]                          # Single string like `["hi"]`
T3: [Integer, Integer]                # Pair of integers like `[1, 2]`
T4: [Symbol, Integer, Integer]        # Tuple of Symbol, Integer, and Integer like `[:pair, 30, 22]`
```

```rbi
T1 = []
T2 = [String]
T3 = [Integer, Integer]
T4 = [Symbol, Integer, Integer]
```

Empty tuple or 1-tuple sound strange, but RBS allows these types.

### Type variable

```rbs:type_var
T1: U
T2: T
T3: S
T4: Elem
```

```rbi
T1 = U
T2 = T
T3 = S
T4 = Elem
```

Type variables cannot be distinguished from class instance types. They are scoped in class/module/interface declaration or generic method types.

```rbs:generics
class Ref[T]              # Object is scoped in the class declaration.
  def map: [X] { (T) -> X } -> Ref[X]   # X is a type variable scoped in the method type.
end
```

```rbi
class Ref
  extend T::Sig
  extend T::Generic

  T = type_member()

  sig { type_parameters(:X).params(_blk: T.proc.params(arg0: T).returns(T.type_parameter(:X))).returns(Ref[T.type_parameter(:X)]) }
  def map(_blk); end
end
```

Variance can be applied to type variables:

```rbs:generic_variance
module Edge[in X, out Y]
end

class Ref[in X]
end
```

```rbi
module Edge
  extend T::Sig
  extend T::Generic

  X = type_member(:in)

  Y = type_member(:out)
end

class Ref
  extend T::Sig
  extend T::Generic

  X = type_member(:in)
end
```

RBS also allows type variables to be declared as unchecked:

```
class Ref[unchecked in X]
end
```

**Unsupported: This has no equivalent in RBI.**

### Proc type

Proc type denots type of procedures, Proc instances.

```rbs:type_procs
T1: ^(Integer) -> String                  # A procedure with an `Integer` parameter and returns `String`
T2: ^(?String, size: Integer) -> bool     # A procedure with `String` optional parameter, `size` keyword of `Integer`, and returns `bool`
```

```rbi
T1 = T.proc.params(arg0: Integer).returns(String)
T2 = T.proc.params(arg0: T.nilable(String), size: Integer).returns(T::Boolean)
```

### Base types

```rbs:type_base
T1: self		# denotes the type of receiver. The type is used to model the open recursion via self.
T2: instance	# denotes the type of instance of the class.
T3: class		# denotes the type of the singleton of the `self` class.
T4: bool		# denotes an abstract type for truth value.
T5: untyped		# is for a type without type checking.
T6: nil			# is for nil.
T7: top			# is a supertype of all of the types.
T8: bot			# is a subtype of all of the types.
T9: void		# is a supertype of all of the types.
```

```rbi
T1 = T.self_type
T2 = T.untyped
T3 = T.class_of(T.self_type)
T4 = T::Boolean
T5 = T.untyped
T6 = NilClass
T7 = T.untyped
T8 = T.untyped
T9 = void
```
