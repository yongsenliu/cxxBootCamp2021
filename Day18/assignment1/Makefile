CC = g++
# Create shared object from normal object
SHARED: shape.o
	@echo -- Building shared library $@
	$(CC) --shared shape.o -o shape.so 

NORMAL: shape.cpp shape.h
	@echo -- Generate object file from $@
	$(CC) -c -fPIC shape.cpp shape.h -o shape.o 

clean:
	@echo -- Clean unused files.
	rm *.out *.o