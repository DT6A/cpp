.PHONY : all, clean

all: lab_04
  
lab_04: obj/merge.o obj/main.o | obj
	gcc obj/merge.o obj/main.o -o lab_04 -Iinclude -std=c11 -fsanitize=address -Wall -Wextra -Werror

obj/merge.o: src/mergesort.c include/mergesort.h | obj
	gcc src/mergesort.c -c -o obj/merge.o -Iinclude -std=c11 -fsanitize=address -Wall -Wextra -Werror

obj/main.o: src/main.c include/mergesort.h | obj
	gcc src/main.c -c -o obj/main.o -Iinclude -std=c11 -fsanitize=address -Wall -Wextra -Werror

obj:
	mkdir obj

clean:
	[ -f lab_04 ] && rm lab_04; \
	rm -rf obj
