CXX = clang++
CXXFLAGS =-std=c++11 -Wall
PROG = AVL.cpp

TARGETS = prog
LDFLAGS=
OBJ = $(SOURCES:.cpp=.o)

all: prog

prog: $(PROG)
	$(CXX) $(CXXFLAGS) -o  prog $(PROG)

clean:
	rm -f *.o ${TARGETS} 
     
