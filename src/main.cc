#include "Driver.hh"
#include "Lexer.hh"
#include "PrintRBI.hh"

using namespace rbs_parser;

int main(int argc, char const *argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: rbs_parser file.rbs..." << std::endl;
        exit(1);
    }
    for (int arg = 1; arg < argc; ++arg) {
        File file(argv[arg]);
        Driver driver(&file);
        try {
            Lexer lexer(file.source());
            Parser parser(driver, lexer);
            parser.parse();

            PrintRBI visitor(std::cout);
            file.acceptVisitor(&visitor);
        } catch (FileNotFoundException e) {
            std::cerr << "Error: file `" << file.filename << "` not found." << std::endl;
            continue;
        }
    }

    return 0;
}
