CC=g++
WFLAGS=-std=c++17 
OBJECTS=$(SOURCES:.cpp=.o)
GCOVFLAGS=--coverage
HTML_CREATE=lcov --no-external -t a.out -o rep.info -c -d .; genhtml -o report rep.info
OS=$(shell uname)
ifeq ($(OS), Linux)
	TESTFLAGS= -lgtest -pthread
else
	TESTFLAGS= -lgtest
endif

all: clean test

clean:
	rm -rf *.o *.g* *.out report *.a *.info

test: clean
	$(CC) tests.cpp *test.cpp $(TESTFLAGS) $(WFLAGS)
	./a.out

leaks: test
	leaks --atExit -- ./a.out

gcov_report: clean
	$(CC) tests.cpp *test.cpp $(TESTFLAGS) $(WFLAGS) $(GCOVFLAGS)
	./a.out
	$(HTML_CREATE)

style:
	cp ../materials/linters/CPPLINT.cfg ./
	python3 ../materials/linters/cpplint.py --extensions=cpp *.cpp *.h
	rm CPPLINT.cfg
