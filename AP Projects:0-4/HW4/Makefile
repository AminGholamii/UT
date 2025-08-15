CXX = g++ -g -std=c++17

FILES = build/main.o build/functions.o build/classes.o
EXE = UTGhalam

all: $(EXE)

$(EXE): $(FILES)
	$(CXX) $^ -o $@

build/main.o: src/main.cpp src/main.hpp
	$(CXX) -c $< -o $@

build/functions.o: src/functions.cpp src/functions.hpp
	$(CXX) -c $< -o $@

build/classes.o: src/classes.cpp src/classes.hpp
	$(CXX) -c $< -o $@

.PHONY: all clean help

clean:
	rm -f $(FILES) $(EXE)

help:
	@echo Called For Help!
