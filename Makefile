CC      = g++
LDFLAGS =

all: simulator clean

simulator: system.o
	$(CC) -o system.o

system.o: system.h cell.o particle.o point.o
	$(CC) -c  system.h cell.o particle.o point.o

cell.o: cell.h particle.o point.o
	$(CC) -c  cell.h particle.o point.o

particle.o: particle.h point.o
	$(CC) -c  particle.h point.o

point.o: point.h
	$(CC) -c  point.h

.PHONY: clean cleanest

clean:
	rm *.o

cleanest: clean
	rm simulator