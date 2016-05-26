appname := cpp-calculator

CXX := clang++
CXXFLAGS := -std=c++14 -Wall -g -c
LFLAGS := -std=c++14 -Wall -g
OBJS := Operator.o Calculator.o main.o

all: $(appname)

$(appname): $(OBJS)
	$(CXX) $(LDFLAGS) -o $(appname) $(OBJS)

Operator.o: Operator.cpp Operator.hpp utils.hpp
	$(CXX) $(CXXFLAGS) Operator.cpp

Calculator.o: Calculator.cpp Calculator.hpp Operator.hpp utils.hpp
	$(CXX) $(CXXFLAGS) Calculator.cpp

main.o: main.cpp Calculator.hpp Operator.hpp utils.hpp
	$(CXX) $(CXXFLAGS) main.cpp

clean:
	rm -f *.o $(appname)

