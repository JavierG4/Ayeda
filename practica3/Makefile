#
#AUTORES :Javier González Brito .

CXX = g++						           # The C++ compiler command
CXXFLAGS = -std=c++17 -Wall	 	 # The C++ compiler options (C++14, preserve debug symbols and warn all)
LDFLAGS =						           # The linker options (if any)

# The all target builds all of the programs handled by the makefile.
all: Programa

Programa: Programa.o 
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Indicate that the all and clean targets do not
# correspond to actual files.
.PHONY: all clean

# The following rule is effectively built into make and
# therefore need not be explicitly specified: 
Programa.o: p01_single_grandes_main.cc p01_single_grandes.cc
#
	$(CXX) $(CXXFLAGS) -c $<

# The clean target removes all of the executable files
# and object files produced by the build process
# We can use it for additional housekeeping purposes
clean :
	rm -f *.o Programa doc
	rm -rf *~ basura b i
	rm -rf a.out
	find . -name '*~' -exec rm {} \;
	find . -name basura -exec rm {} \;

push :
	git add .
	git commit -m mejora
	git push

pull:
	git pull
	
actu:
	git pull
	git add .
	git commit -m actualización
	git push
program:
	g++ -g -o Celula main.cc position.cc estado.cc celula.cc 