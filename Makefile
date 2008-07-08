CFLAGS=-g -Wall -ansi
CXXFLAGS=$(CFLAGS)
LDFLAGS=
LDLIBS=-llua -ldl
OBJECTS=main.o LuaObj.o Test.o

all: main

main: $(OBJECTS)
	g++ $(LDFLAGS) -o main $(OBJECTS) $(LDLIBS)

clean:
	rm -f *.o

distclean: clean
	rm main

.PHONY: all clean distclean
