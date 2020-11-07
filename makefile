CXX = g++

UTIL = basicArithmeticFunctions.cpp util.cpp basicArithmeticFunctions.h util.h
UTILCOMPILE = basicArithmeticFunctions.cpp util.cpp

mathLib: mathMain.o
	g++ mathMain.o -o mathLib

mathMain.o: mathMain.cpp $(wildcard UnitTests/*.cpp) $(wildcard UnitTests/*.h)
	g++ $< -o mathMain

Algebra/%.o: %.cpp $(wildcard Algebra/*.h)
	g++ $< -c $@

Automata/%.o: %.cpp $(wildcard Automata/*.h)
	g++ $< -c $@

Binary/%.o: %.cpp $(wildcard Binary/*.h)
	g++ $< -c $@

Fractions/%.o: %.cpp $(wildcard Fractions/*.h)
	g++ $< -c $@

Geometry/%.o: %.cpp $(wildcard Geometry/*.h)
	g++ $< -c $@

Graphs/%.o: %.cpp $(wildcard Graphs/*.h)
	g++ $< -c $@

HashTables/%.o: %.cpp $(wildcard HashTables/*.h)
	g++ $< -c $@

Regex/%.o: %.cpp $(wildcard Regex/*.h)
	g++ $< -c $@

Sets/%.o: %.cpp $(wildcard Sets/*.h)
	g++ $< -c $@

Trees/%.o: %.cpp $(wildcard Trees/*.h)
	g++ $< -c $@

UnitTests/automataUnitTest.o: UnitTests/automataUnitTest.cpp UnitTests/automataUnitTest.h $(wildcard Automata/*.h) $(wildcard Automata/*.cpp)
	g++ automataUnitTest.cpp $(wildcard Automata/*.cpp) -c $@

UnitTests/eqParserUnitTest.o: UnitTests/eqParserUnitTest.cpp UnitTests/eqParserUnitTest.h $(wildcard Algebra/*.h) $(wildcard Algebra/*.cpp)
	g++ eqParserUnitTest.cpp $(wildcard Algebra/*.cpp) -c $@

UnitTests/fractionUnitTest.o: UnitTests/fractionUnitTest.cpp UnitTests/fractionUnitTest.h $(wildcard Fractions/*.h) $(wildcard Fractions/*.cpp)
	g++ fractionUnitTest.cpp $(wildcard Fractions/*.cpp) -c $@

UnitTests/setUnitTest.o: UnitTests/setUnitTest.cpp UnitTests/setUnitTest.h $(wildcard Sets/*.h) $(wildcard Sets/*.cpp)
	g++ setUnitTest.cpp $(wildcard Sets/*.cpp) -c $@

UnitTests/treeUnitTest.o: UnitTests/treeUnitTest.cpp UnitTests/treeUnitTest.h $(wildcard Trees/*/*.h) $(wildcard Trees/*/*.cpp)
	g++ treeUnitTest.cpp $(wildcard Trees/*/*.cpp) -c $@

clean:
	rm *.o mathLib