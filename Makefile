CC := gcc -g

all: gray thermo posterize gradient gradient_binary

gray: gray.o bitmap.o

thermo: thermo.o bitmap.o

posterize: posterize.o bitmap.o

gradient: gradient_main.o bitmap.o

gradient_binary: gradient_binary.o gradient.o bitmap.o

clean:
	$(RM) *.o gray thermo posterize gradient gradient_binary
