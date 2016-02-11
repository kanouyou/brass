TARGET = RunAnalysis.exe
CXX    = g++
SRCS   = main.cpp  IThermalEvent.cpp  IThermalHandle.cpp
OBJS   = $(SRCS:.cpp=.o)

CXXLIBS  = `root-config --glibs`
CXXFLAGS = -O3 -Wall `root-config --cflags`

.PHONY: all
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXLIBS) $^ -o $@

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $<

.PHONY: clean
clean:
	$(RM) $(TARGET) $(OBJS)
