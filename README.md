# RBS parser

`rbs_parser` provides an API and a command line tool to parse [Ruby RBS signatures](https://github.com/ruby/ruby-signature)
and translate them to [Sorbet's RBI format](https://sorbet.org/docs/rbi).

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

To translate a single file:

```sh
$ rbs2rbi file.rbs
```

RBI is output to `stdout`, parsing errors and RBI translation errors to `stderr`.

## Running the tests

```sh
$ make check
```

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

    virtual void visit(TypeBool *type) { print("T::Boolean"); }

    virtual void visit(TypeNil *type) { print("NilClass"); }

	// ...
}
```

## Contributing

Bug reports and pull requests are welcome on GitHub at https://github.com/Shopify/rbs_parser.
This project is intended to be a safe, welcoming space for collaboration, and contributors
are expected to adhere to the [Contributor Covenant](CODE_OF_CONDUCT.md) code of conduct.

## License

The gem is available as open source under the terms of the [MIT License](LICENSE.md).
