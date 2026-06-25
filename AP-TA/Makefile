CXX = g++ -g -std=c++20
FILES = build/main.o build/table.o build/command.o
EXE = DadeNegar

all: build $(EXE)

$(EXE): $(FILES)
	$(CXX) $^ -o $@ 

build:
	mkdir -p build

build/main.o: src/main.cpp src/main.hpp | build
	$(CXX) -c $< -o $@

build/table.o: src/table.cpp src/table.hpp | build
	$(CXX) -c $< -o $@

build/command.o: src/command.cpp src/command.hpp | build
	$(CXX) -c $< -o $@

.PHONY: all clean help

clean:
	rm -f $(FILES) $(EXE)

help:
	@echo Called for help?