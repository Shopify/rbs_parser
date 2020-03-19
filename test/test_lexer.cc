#include "../src/File.hh"
#include "../src/Lexer.hh"

using namespace rbs_parser;

int main(int argc, char const *argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: test_lexer file.rbs" << std::endl;
        exit(1);
    }

    File file(argv[1]);
    Lexer lex = Lexer(file.source());
    Parser::token_type type;

    do {
        Parser::semantic_type val;
        Parser::location_type loc;
        type = lex.lex(&val, &loc);

        if (type == Parser::token::tEOF) {
            break;
        }

        if (type == Parser::token::tERROR) {
            std::cerr << loc.begin.line << ":" << loc.begin.column << "-";
            std::cerr << loc.end.line << ":" << loc.end.column;
            std::cerr << ": Syntax error: unexpected token `" << *val.string << "`" << std::endl;
            return 1;
        }

        std::cout << loc.begin.line << ":" << loc.begin.column << "-";
        std::cout << loc.end.line << ":" << loc.end.column;
        std::cout << ": " << *val.string << std::endl;

    } while (type != Parser::token::tEOF);

    return 0;
}
