#include "../src/Driver.hh"
#include "../src/Lexer.hh"
#include "../src/PrintAST.hh"

using namespace rbs_parser;

int main(int argc, char const *argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: test_parser file.rbs" << std::endl;
        exit(1);
    }

    File file(argv[1]);
    Driver driver(&file);
    Lexer lexer(file.source());
    Parser parser(driver, lexer);

    try {
        parser.parse();
    } catch (ParseError &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    PrintAST visitor(std::cout);
    file.acceptVisitor(&visitor);

    return 0;
}
