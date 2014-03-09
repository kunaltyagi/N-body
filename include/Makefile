CC      = g++
LDFLAGS =

all: point.h particle.h cell.h system.h
	g++ -c point.h particle.h cell.h system.h
	#simulator clean

simulator: system.o
	$(CC) -o system.o

system.o: include/system.h cell.o particle.o point.o
	$(CC) -c  include/system.h cell.o particle.o point.o

cell.o: include/cell.h particle.o point.o
	$(CC) -c  include/cell.h particle.o point.o

particle.o: include/particle.h point.o
	$(CC) -c  include/particle.h point.o

point.o: include/point.h
	$(CC) -c  include/point.h

.PHONY: clean cleanest

clean:
	rm *.o

cleanest: clean
	rm simulator