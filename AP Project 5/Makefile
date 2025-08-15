CXX = g++ -g -std=c++20

FILES = build/main.o build/ReadInputFile.o build/GraphicsEngine.o build/MapSystem.o build/RightPanel.o build/Ballons.o build/Towers.o build/toppanel.o
EXE = TD
LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

all: $(EXE)

$(EXE): $(FILES)
	$(CXX) $^ -o $@ $(LIBS)

build/main.o: src/main.cpp src/main.hpp 
	$(CXX) -c $< -o $@
   
build/ReadInputFile.o: src/ReadInputFile.cpp src/ReadInputFile.hpp
	$(CXX) -c $< -o $@

build/GraphicsEngine.o: src/GraphicsEngine.cpp src/GraphicsEngine.hpp
	$(CXX) -c $< -o $@

build/MapSystem.o: src/MapSystem.cpp src/MapSystem.hpp 
	$(CXX) -c $< -o $@

build/RightPanel.o: src/RightPanel.cpp src/RightPanel.hpp 
	$(CXX) -c $< -o $@

build/Ballons.o: src/Ballons.cpp src/Ballons.hpp
	$(CXX) -c $< -o $@

build/Towers.o: src/Towers.cpp src/Towers.hpp
	$(CXX) -c $< -o $@

build/toppanel.o: src/toppanel.cpp src/toppanel.hpp
	$(CXX) -c $< -o $@

.PHONY: all clean help

clean:
	rm -f $(FILES) $(EXE)

help:
	@echo Called For Help!
