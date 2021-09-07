exec = bfi
sources = $(wildcard src/*.c)
objects = $(sources:.c=.o)
flags = -g -Wall -lm -ldl -fpic -rdynamic


$(exec): $(objects)
	gcc $(objects) $(flags) -o $(exec)

libbfi.a: $(objects)
	ar rcs $@ $^

%.o: %.c include/%.h
	gcc -c $(flags) $< -o $@

install:
	make
	make libbfi.a
	mkdir -p /usr/local/include/bfi
	cp -r ./src/include/* /usr/local/include/bfi/.
	cp ./libbfi.a /usr/local/lib/.
	cp ./bfi.out /usr/local/bin/bfi

clean:
	-rm *.out
	-rm *.o
	-rm *.a
	-rm src/*.o
	-rm bfi

lint:
	clang-tidy src/*.c src/include/*.h
