CXXFLAGS =	-O2 -g -Wall -fmessage-length=0

OBJS =		Solver.o

LIBS =

TARGET =	Solver

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
