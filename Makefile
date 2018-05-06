CC := gcc

all: gray thermo

gray: gray.o bitmap.o

thermo: thermo.o bitmap.o

clean:
	$(RM) *.o gray thermo
