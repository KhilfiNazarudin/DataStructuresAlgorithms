# Only recursive_insertion_sort.cpp is yours to edit.
#
#   make                                     build the program
#   make test                                run every supplied case
#   make run FILE=input_reverse_sorted.txt   run one case
#   make clean                               delete the built files

CXX ?= g++
CXXFLAGS ?= -std=c++23 -Wall

TARGET = recursive_insertion_sort
TEST_TARGET ?= run_tests
TESTDIR ?= tests
SUBMISSION ?= recursive_insertion_sort.cpp

# Listed explicitly rather than globbed, so that a stray backup copy such as
# recursive_insertion_sort_old.cpp cannot break the build.
SHARED_SRCS = import_numbers_from_file.cpp $(SUBMISSION)
MAIN_SRCS = main.cpp $(SHARED_SRCS)
TEST_SRCS = test_runner.cpp $(SHARED_SRCS)
HDRS = import_numbers_from_file.h recursive_insertion_sort.h

.PHONY: all test run clean

all: $(TARGET)

$(TARGET): $(MAIN_SRCS) $(HDRS)
	$(CXX) $(CXXFLAGS) $(MAIN_SRCS) -o $(TARGET)

$(TEST_TARGET): $(TEST_SRCS) $(HDRS)
	$(CXX) $(CXXFLAGS) $(TEST_SRCS) -o $(TEST_TARGET)

test: $(TEST_TARGET)
	./$(TEST_TARGET)

# A bare name is looked up in tests/; a path is used as given. $(wildcard) is a make
# function, so this needs no shell test.
FILEPATH = $(if $(wildcard $(FILE)),$(FILE),$(TESTDIR)/$(FILE))

ifeq ($(FILE),)
run:
	@echo "Name a file, for example: make run FILE=input_reverse_sorted.txt"
else
run: $(TARGET)
	./$(TARGET) $(FILEPATH)
endif

clean:
	$(RM) $(TARGET) $(TEST_TARGET)
