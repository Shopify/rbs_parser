# RBS parser (deprecated)

> ⚠️ This repository is no longer maintained.

`rbs_parser` provides an API and a command line tool to parse [Ruby RBS signatures](https://github.com/ruby/ruby-signature)
and translate them to [Sorbet's RBI format](https://sorbet.org/docs/rbi).

See [the comparison of supported features](./specs/README.md) by both specifications and what `rbs2rbi` is able to translate.

## Compilation

Compile the `rbs2rbi` translator:

```
$ make
```

Requirements:

* `bison` 3.4
* `ragel` 6.10
* `clang` 11.0

## Usage

Given the following RBS file:

```ruby
# calculator.rbs

class Calculator
  def sum: (Integer, Integer) -> Integer
end
```

Translate it to RBI with `rbs2rbi`:

```sh
$ rbs2rbi calculator.rbs
```

RBI is output to `stdout`, parsing errors and RBI translation errors to `stderr`:

```ruby
# typed: true

class Calculator
  extend T::Sig

  sig { params(arg0: Integer, arg1: Integer).returns(Integer) }
  def sum(arg0, arg1); end
end
```

## What's supported?

Take a look at [our comparison of RBS and RBI](specs/README.md).

| Declarations                          | RBS  | RBI  |
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

| Members                               | RBS  | RBI  |
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

| Types                                 | RBS  | RBI  |
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
| instance type                         |  ✅  |  ✅  |
| base types                            |  ✅  |  🔶  |

## Writing your own translator

Create a subclass of `Visitor` or `PrintVisitor`:

```c++
#include "File.hh"
#include "PrintVisitor.hh"

class PrintMyFormat : public PrintVisitor {
public:
    PrintMyFormat(std::ostream &output) : PrintVisitor(output){};

    virtual void visit(File *file) {
        for (auto *decl : file->decls) {
            enterVisit(decl);
        }
    }

    virtual void visit(TypeBool *type) { print("Bool"); }

    virtual void visit(TypeNil *type) { print("Nil"); }

	// ...
}
```

## Running the tests

```sh
$ make check
```

## Contributing

Bug reports and pull requests are welcome on GitHub at https://github.com/Shopify/rbs_parser.
This project is intended to be a safe, welcoming space for collaboration, and contributors
are expected to adhere to the [Contributor Covenant](CODE_OF_CONDUCT.md) code of conduct.

## License

The gem is available as open source under the terms of the [MIT License](LICENSE.md).
