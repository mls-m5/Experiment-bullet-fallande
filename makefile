FLAGS = -std=c++0x
LIBS = -lGL -lGLU -lglut
obj = main.o ship.o vector.o
Target = main

all: $(obj)
	g++ $(obj) -o $(Target) $(LIBS)

run: all
	./$(Target)	


ship.o: ship.h komp.h

main.o: ship.h
