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
