CXX = g++ -g -std=c++20
FILES = build/main.o build/Functions.o build/Date.o build/System.o build/User.o build/Event.o
EXE = UTrello

all: build $(EXE)

$(EXE): $(FILES)
	$(CXX) $^ -o $@ 

build:
	mkdir -p build

build/main.o: src/main.cpp src/main.hpp | build
	$(CXX) -c $< -o $@

build/Functions.o: src/Functions.cpp src/Functions.hpp | build
	$(CXX) -c $< -o $@

build/Date.o : src/Date.cpp src/Date.hpp | build
	$(CXX) -c $< -o $@

build/System.o: src/System.cpp src/System.hpp | build
	$(CXX) -c $< -o $@

build/User.o: src/User.cpp src/User.hpp | build
	$(CXX) -c $< -o $@

build/Event.o: src/Event.cpp src/Event.hpp | build
	$(CXX) -c $< -o $@


.PHONY: all clean help

clean:
	rm -f $(FILES) $(EXE)

help:
	@echo Called For Help!
