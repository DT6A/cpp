.PHONY : all, clean

all: lab3
  
lab3: obj/clist.o obj/main.o | obj
	gcc obj/main.o obj/clist.o -o lab3 -Iinclude -std=c11 -fsanitize=address -Wall -Wextra -Werror -lflite_cmu_us_kal -lflite_usenglish -lflite_cmulex -lflite -lm

obj/clist.o: src/clist.c include/clist.h | obj
	gcc src/clist.c -c -o obj/clist.o -Iinclude -std=c11 -fsanitize=address -Wall -Wextra -Werror

obj/main.o: src/main.c include/clist.h | obj
	gcc src/main.c -c -o obj/main.o -Iinclude -std=c11 -fsanitize=address -Wall -Wextra -Werror -I/usr/include/flite/ 

obj:
	mkdir obj

clean:
	[ -f lab3 ] && rm lab3; \
	rm -rf obj
