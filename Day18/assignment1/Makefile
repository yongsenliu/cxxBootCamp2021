# Create shared object from normal object
CC = g++
CFLAGS = -g -Wall

SHARED: shape.o
	@echo -- Building shared library $@
	$(CC) $(CFLAGS) --shared shape.o -o shape.so 

NORMAL: shape.cpp shape.h
	@echo -- Generate object file from $@
	$(CC) $(CFLAGS) -c -fPIC shape.cpp shape.h -o shape.o 

clean:
	@echo -- Clean unused files.
	rm *.out *.o
