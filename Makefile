CC := gcc

all: gray thermo posterize

gray: gray.o bitmap.o

thermo: thermo.o bitmap.o

posterize: posterize.o bitmap.o

clean:
	$(RM) *.o gray thermo posterize
