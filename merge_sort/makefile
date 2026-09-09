# Only merge_sort.cpp is yours to edit.
#
#   make                                  build the program
#   make run FILE=test_reverse.txt        run a test from tests/
#   make run FILE=path/to/input.txt       run a test at an explicit path
#   make clean                            delete the built program

CXX ?= g++
CXXFLAGS ?= -std=c++23 -Wall

TARGET = merge_sort
TESTDIR ?= tests
SUBMISSION ?= merge_sort.cpp

# Source files are listed explicitly so that a backup .cpp file in this folder
# cannot accidentally be compiled as part of the program.
SRCS = main.cpp import_numbers_from_file.cpp $(SUBMISSION)
HDRS = import_numbers_from_file.h merge_sort.h

.PHONY: all run clean

all: $(TARGET)

$(TARGET): $(SRCS) $(HDRS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)

# A bare name is looked up in tests/; an existing path is used as given.
FILEPATH = $(if $(wildcard $(FILE)),$(FILE),$(TESTDIR)/$(FILE))

ifeq ($(FILE),)
run:
	@echo "Name a file, for example: make run FILE=test_reverse.txt"
else
run: $(TARGET)
	./$(TARGET) $(FILEPATH)
endif

clean:
	$(RM) $(TARGET)
