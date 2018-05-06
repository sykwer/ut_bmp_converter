CC := gcc

all: gray

gray: gray.o bitmap.o

clean:
	$(RM) *.o gray
