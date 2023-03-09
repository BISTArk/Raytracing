CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11

SRCS = main.cc
OBJS = $(SRCS:.cc=.o)
INCLUDE = include
TARGET = builds/myprogram
OUTPUT = outputs/image.ppm

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) -I $(INCLUDE) $(CXXFLAGS) $^ -o $@
	$(TARGET) > $(OUTPUT)

clean:
	rm -f $(OBJS) $(TARGET)