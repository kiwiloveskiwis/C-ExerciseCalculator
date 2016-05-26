appname := cpp-calculator

CXX := clang++
CXXFLAGS := -std=c++14 -Wall -g -c
LFLAGS := -std=c++14 -Wall -g
OBJS := Operator.o Calculator.o main.o

all: $(appname)

$(appname): $(OBJS)
	$(CXX) $(LDFLAGS) -o $(appname) $(OBJS)

unit-test: unit-test.o Calculator.o Operator.o
	$(CXX) $(LDFLAGS) -o unit-test unit-test.o Calculator.o Operator.o
	./unit-test

Operator.o: Operator.cpp Operator.hpp utils.hpp
	$(CXX) $(CXXFLAGS) Operator.cpp

Calculator.o: Calculator.cpp Calculator.hpp Operator.hpp utils.hpp
	$(CXX) $(CXXFLAGS) Calculator.cpp

main.o: main.cpp Calculator.hpp Operator.hpp utils.hpp
	$(CXX) $(CXXFLAGS) main.cpp

unit-test.o: unit-test.cpp Calculator.hpp Operator.hpp utils.hpp
	$(CXX) $(CXXFLAGS) unit-test.cpp

clean:
	rm -f *.o $(appname) unit-test

