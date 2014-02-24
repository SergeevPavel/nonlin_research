CXXFLAGS =	-O2 -g -Wall -fmessage-length=0

OBJS =		Exemple.o

LIBS =

TARGET =	Exemple

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
