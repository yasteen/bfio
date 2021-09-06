exec = bfcc
sources = $(wildcard src/*.c)
objects = $(sources:.c=.o)
flags = -g -Wall -lm -ldl -fpic -rdynamic


$(exec): $(objects)
	gcc $(objects) $(flags) -o $(exec)

libbfcc.a: $(objects)
	ar rcs $@ $^

%.o: %.c include/%.h
	gcc -c $(flags) $< -o $@

install:
	make
	make libbfcc.a
	mkdir -p /usr/local/include/bfcc
	cp -r ./src/include/* /usr/local/include/bfcc/.
	cp ./libbfcc.a /usr/local/lib/.
	cp ./bfcc.out /usr/local/bin/bfcc

clean:
	-rm *.out
	-rm *.o
	-rm *.a
	-rm src/*.o

lint:
	clang-tidy src/*.c src/include/*.h
