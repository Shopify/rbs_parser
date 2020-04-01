CXX = g++
BSN = bison
RGL = ragel

rbs2rbi: src/Lexer.o src/Parser.o src/main.o
	$(CXX) $^ -o $@

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

.PHONY:
check_rbi: rbs2rbi
	echo "Test RBI generation"
	./test/test.sh ./rbs2rbi test/rbi_generation/rbs test/rbi_generation/res

check_rbi_with_sorbet:
	cd test && ./test_with_sorbet.sh

clone_stdlib:
	git clone https://github.com/ruby/ruby-signature.git tmp
	cp -r tmp/stdlib test/stdlib
	rm -rf tmp

.PHONY:
check_stdlib: rbs2rbi
	cd test && ./test_stdlib.sh stdlib

.PHONY:
check_format:
	./tools/format_cxx.sh

.PHONY:
check: check_lexer check_parser check_rbi check_rbi_with_sorbet check_stdlib check_format check_specs

.PHONY:
gen_specs: rbs2rbi specs/README.src
	specs/build.sh ./rbs2rbi specs/README.src > specs/README.md

.PHONY:
check_specs: rbs2rbi specs/README.src
	test/test_specs.sh

.PHONY:
clean:
	rm -rf src/Lexer.o src/Lexer.cc \
		  src/Parser.o src/Parser.hh src/Parser.cc src/location.hh \
		  src/Main.o rbs2rbi \
		  test/test_lexer.o test_lexer test/test_parser.o test_parser out \
		  out/ tmp/ test/sorbet/stdlib
