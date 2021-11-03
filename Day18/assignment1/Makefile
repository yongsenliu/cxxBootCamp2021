CXX = g++

libshape.so: shape.o
	@echo -- Building shared library $@
	$(CXX) --shared shape.o 

shape.o: shape.cpp shape.h
	@echo -- Generate object file
	$(CXX) -c -fPIC shape.h shape.cpp

