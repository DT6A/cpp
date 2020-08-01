all: build
  
build: bin alg io util
	gcc src/main.c bin/alg.o bin/io.o bin/util.o -o lab1 -Iinclude -Wall -Wextra -Werror

alg: bin src/algorithm.c
	gcc src/algorithm.c -c -o bin/alg.o -Iinclude -Wall -Wextra -Werror

io: bin src/io.c
	gcc src/io.c -c -o bin/io.o -Iinclude -Wall -Wextra -Werror

util: bin src/util.c 
	gcc src/util.c -c -o bin/util.o -Iinclude -Wall -Wextra -Werror

bin:
	mkdir bin

clean: bin
	[ -f lab1 ] && rm lab1; \
	rm -R bin 
