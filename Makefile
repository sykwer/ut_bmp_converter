CC := gcc -g

all: gray thermo posterize gradient

gray: gray.o bitmap.o

thermo: thermo.o bitmap.o

posterize: posterize.o bitmap.o

gradient: gradient_main.o bitmap.o

clean:
	$(RM) *.o gray thermo posterize gradient
