.PHONY : all, clean

all: hw_01
  
hw_01: obj/bmp.o obj/main.o obj/stego.o | obj
	gcc obj/main.o obj/bmp.o obj/stego.o -o hw_01 -Iinclude -std=c11 -fsanitize=address -Wall -Wextra -Werror

obj/bmp.o: src/bmp.c include/bmp.h | obj
	gcc src/bmp.c -c -o obj/bmp.o -Iinclude -std=c11 -fsanitize=address -Wall -Wextra -Werror

obj/stego.o: src/stego.c include/stego.h | obj
	gcc src/stego.c -c -o obj/stego.o -Iinclude -std=c11 -fsanitize=address -Wall -Wextra -Werror

obj/main.o: src/main.c include/bmp.h include/stego.h | obj
	gcc src/main.c -c -o obj/main.o -Iinclude -std=c11 -fsanitize=address -Wall -Wextra -Werror

obj:
	mkdir obj

clean:
	[ -f hw_01 ] && rm hw_01; \
	rm -rf obj
