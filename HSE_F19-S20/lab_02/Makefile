.PHONY : all, build, clean

all: build
  
build: obj/str.o obj/test_str.o obj/test.o | obj
	gcc obj/test.o obj/str.o obj/test_str.o -o lab2 -Iinclude -std=c11 -fsanitize=address -Wall -Wextra -Werror

obj/str.o: src/str.c | obj
	gcc src/str.c -c -o obj/str.o -Iinclude -std=c11 -fsanitize=address -Wall -Wextra -Werror

obj/test_str.o: src/test_str.c | obj
	gcc src/test_str.c -c -o obj/test_str.o -Iinclude -std=c11 -fsanitize=address -Wall -Wextra -Werror

obj/test.o: src/test.c | obj
	gcc src/test.c -c -o obj/test.o -Iinclude -std=c11 -fsanitize=address -Wall -Wextra -Werror

obj:
	mkdir obj

clean:
	[ -f lab2 ] && rm lab2; \
	rm -rf obj
