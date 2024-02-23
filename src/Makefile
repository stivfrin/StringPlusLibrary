LIB := s21_string
CC := gcc -Wall -Werror -Wextra #-std=c11
CC1 := $(CC)
LFLAGS := -lcheck -lm -lpthread

BROWSER := open
ifeq ($(shell uname -s), Linux)
	BROWSER := firefox
	LFLAGS := ${LFLAGS} -lsubunit
endif

all: $(LIB).a

$(LIB).o:
	$(CC1) -c s21_*.c

$(LIB).a: $(LIB).o
	ar rcs $(LIB).a *.o
	ranlib $(LIB).a
	rm *.o

test.o:
	cd tests/build && \
	$(CC) -c ../s21_*.c

test: clean $(LIB).a test.o
	cp $(LIB).a tests/build
	cd tests/build && \
	$(CC1) ../full_test.c *.o ../../$(LIB).a -o test $(LFLAGS)
	./tests/build/test

gcov_report: add_coverage test
	lcov -t "test" -o test.info -c -d .
	genhtml -o report test.info
	$(BROWSER) report/index.html

add_coverage:
	$(eval CC1 += --coverage)

clean_src:
	rm -rf *o
	rm -rf $(LIB).a

clean_build:
	rm -rf tests/build/*.o
	rm -rf tests/build/$(LIB).a
	rm -rf tests/build/test

clean_report:
	rm -rf *.gc*
	rm -rf tests/build/*.gc*
	rm -rf report
	rm -rf test.info

checks:
	clang-format -n *.c *.h
	clang-format -style="{BasedOnStyle: Google}" -i *.c
	clang-format -style="{BasedOnStyle: Google}" -i *.h
	cppcheck enable=all missingIncludeSystem *.c

clean: clean_src clean_build clean_report