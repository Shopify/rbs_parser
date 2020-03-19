CXX = g++
BSN = bison
RGL = ragel

%.o: %.cc
	$(CXX) -std=c++17 -c -o $@ $<

src/Parser.hh: src/Parser.cc

src/Parser.cc: src/Parser.ypp
	$(BSN) -o $@ $<

src/Lexer.cc: src/Lexer.rl src/Parser.hh src/Parser.cc
	$(RGL) -C -o $@ $<

test_lexer: src/Lexer.o src/Parser.o test/test_lexer.o
	$(CXX) $^ -o $@

.PHONY:
check_lexer: test_lexer
	echo "Test Lexer"
	./test/test.sh ./test_lexer test/lexer/rbs test/lexer/res

test_parser: src/Lexer.o src/Parser.o test/test_parser.o
	$(CXX) $^ -o $@

.PHONY:
check_parser: test_parser
	echo "Test Parser"
	./test/test.sh ./test_parser test/parser/rbs test/parser/res
