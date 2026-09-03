CXX ?= g++
CXXFLAGS ?= -std=c++23 -Wall
TARGET ?= insertion_sort

SRCS = $(wildcard *.cpp)
OBJS = $(SRCS:.cpp=.o)
DEPS = $(wildcard *.h)

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

%.o: %.cpp $(DEPS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	@if [ -z "$(FILE)" ]; then \
		echo "Error: Please specify a file name with FILE=<filename>"; \
		exit 1; \
	fi
	./$(TARGET) $(FILE)

clean:
	rm -f $(TARGET) $(OBJS)
