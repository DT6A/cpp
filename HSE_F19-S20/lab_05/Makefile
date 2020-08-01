.PHONY : all, clean

all: lab_05
  
lab_05: obj/clist.o obj/main.o obj/point.o | obj
	gcc obj/main.o obj/clist.o obj/point.o -o lab_05 -Iinclude -std=c11 -fsanitize=address -Wall -Wextra -Werror

obj/clist.o: src/clist.c include/clist.h | obj
	gcc src/clist.c -c -o obj/clist.o -Iinclude -std=c11 -fsanitize=address -Wall -Wextra -Werror

obj/main.o: src/main.c include/point_list.h | obj
	gcc src/main.c -c -o obj/main.o -Iinclude -std=c11 -fsanitize=address -Wall -Wextra -Werror

obj/point.o: src/point_list.c include/clist.h include/point_list.h | obj
	gcc src/point_list.c -c -o obj/point.o -Iinclude -std=c11 -fsanitize=address -Wall -Wextra -Werror

obj:
	mkdir obj

clean:
	[ -f lab_05 ] && rm lab_05; \
	rm -rf obj
