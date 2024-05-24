# ID: 207192246
# Email: ShayNamir@gmail.com

CXX=g++
CXXFLAGS=-std=c++11 -Werror -Wsign-conversion
VALGRIND_FLAGS=-v --leak-check=full --show-leak-kinds=all  --error-exitcode=99

SOURCESDEMO=Graph.cpp Algorithms.cpp 
SOURCESTEST=Graph.cpp Algorithms.cpp TestCounter.cpp Test.cpp
OBJECTSDEMO=$(subst .cpp,.o,$(SOURCESDEMO))
OBJECTSTEST=$(subst .cpp,.o,$(SOURCESTEST))

.PHONY: all run demo test tidy valgrind clean

all: demo test

run: demo
	./$^

demo: Demo.o $(OBJECTSDEMO)
	$(CXX) $(CXXFLAGS) $^ -o demo

test: TestCounter.o Test.o $(OBJECTSTEST)
	$(CXX) $(CXXFLAGS) $^ -o test

tidy:
	g++-tidy $(SOURCES) -checks=bugprone-,g++-analyzer-,cppcoreguidelines-,performance-,portability-,readability-,-cppcoreguidelines-pro-bounds-pointer-arithmetic,-cppcoreguidelines-owning-memory --warnings-as-errors=-* --

valgrind: demo test
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./demo 2>&1 | { egrep "lost| at " || true; }
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./test 2>&1 | { egrep "lost| at " || true; }

%.o: %.cpp
	$(CXX) $(CXXFLAGS) --compile $< -o $@

clean:
	rm -f *.o demo test