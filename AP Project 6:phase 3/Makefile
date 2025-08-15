CXX = g++
CXXFLAGS = -std=c++20 -Wall -pedantic

BUILD_DIR = build
TEMPLATE_DIR = .template
OUT_EXE = UTrello

ifeq ($(OS),Windows_NT)
	LDLIBS += -l Ws2_32
endif

all: $(BUILD_DIR) $(OUT_EXE)

$(OUT_EXE): \
	$(BUILD_DIR)/main.o \
    $(BUILD_DIR)/System.o \
    $(BUILD_DIR)/Functions.o \
    $(BUILD_DIR)/Event.o \
    $(BUILD_DIR)/User.o \
    $(BUILD_DIR)/Date.o \
    $(BUILD_DIR)/handlers.o \
    $(BUILD_DIR)/response.o \
    $(BUILD_DIR)/request.o \
    $(BUILD_DIR)/utilities.o \
    $(BUILD_DIR)/strutils.o \
    $(BUILD_DIR)/server.o \
    $(BUILD_DIR)/route.o \
    $(BUILD_DIR)/template_parser.o
	$(CXX) $(CXXFLAGS) $^ $(LDLIBS) -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/template_parser.o: utils/template_parser.cpp utils/template_parser.hpp utils/request.cpp utils/request.hpp utils/utilities.hpp utils/utilities.cpp utils/strutils.hpp utils/strutils.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/response.o: utils/response.cpp utils/response.hpp utils/include.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/request.o: utils/request.cpp utils/request.hpp utils/include.hpp utils/utilities.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/utilities.o: utils/utilities.cpp utils/utilities.hpp utils/strutils.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/strutils.o: utils/strutils.cpp utils/strutils.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/server.o: server/server.cpp server/server.hpp server/route.hpp utils/utilities.hpp utils/strutils.hpp utils/response.hpp utils/request.hpp utils/include.hpp utils/template_parser.hpp utils/template_parser.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/route.o: server/route.cpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/handlers.o: src/handlers.cpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/main.o: src/main.cpp src/main.hpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/Functions.o: src/Functions.cpp src/Functions.hpp
	$(CXX) -c $< -o $@

$(BUILD_DIR)/Date.o : src/Date.cpp src/Date.hpp
	$(CXX) -c $< -o $@

$(BUILD_DIR)/System.o: src/System.cpp src/System.hpp
	$(CXX) -c $< -o $@

$(BUILD_DIR)/User.o: src/User.cpp src/User.hpp
	$(CXX) -c $< -o $@

$(BUILD_DIR)/Event.o: src/Event.cpp src/Event.hpp
	$(CXX) -c $< -o $@

.PHONY: all clean
clean:
	rm -rf $(BUILD_DIR) $(TEMPLATE_DIR) *.o *.out &> /dev/null
