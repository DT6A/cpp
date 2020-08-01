.PHONY : all, clean

all: lab_11

lab_11: obj/bin_man.o obj/employees.o obj/main.o | obj
	g++ obj/main.o obj/employees.o obj/bin_man.o -o lab_11 -Iinclude -fsanitize=address -Wall -Wextra -Werror

obj/main.o: src/main.cpp include/employees.h | obj
	g++ src/main.cpp -c -o obj/main.o -Iinclude -fsanitize=address -Wall -Wextra -Werror

obj/employees.o: src/employees.cpp include/employees.h include/bin_manip.h | obj
	g++ src/employees.cpp -c -o obj/employees.o -Iinclude -fsanitize=address -Wall -Wextra -Werror

obj/bin_man.o: src/bin_manip.cpp include/bin_manip.h | obj
	g++ src/bin_manip.cpp -c -o obj/bin_man.o -Iinclude -fsanitize=address -Wall -Wextra -Werror

obj:
	mkdir obj

clean:
	[ -f lab_11 ] && rm lab_11; \
	rm -rf obj
