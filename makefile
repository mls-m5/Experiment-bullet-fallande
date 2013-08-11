DEBUG = -d -g
CXXFLAGS = -std=c++0x `pkg-config --cflags bullet` ${DEBUG}
LFLAGS = ${DEBUG}
LIBS = -d -lGL -lGLU -lglut `pkg-config --libs bullet`
obj = main.o ship.o vector.o unit.o physics.o box.o
Target = main

all: $(obj)
	g++ ${LFLAGS} $(obj) -o $(Target) $(LIBS)

clean:
	rm *.o

run: all
	./$(Target)

ship.o: ship.h komp.h unit.h

main.o: ship.h physics.h box.h

physics.o: box.h
