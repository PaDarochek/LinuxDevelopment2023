.POSIX:
CFLAGS  = -std=c99 -Wall -Wextra
if COND_GCOV
CFLAGS  += -O0 -g -fprofile-arcs -ftest-coverage
else
CFLAGS  += -O3 -g3
endif

CLEANFILES=*.o *.gcov Makefile Makefile.in README.md *.la *.lo

lib_LTLIBRARIES = libbuf.la

gcov:
	gcov -o .libs libbuf | egrep -v '[[:digit:]]:[ /][*]'

.PHONY: clean

clean:
	rm -rf ${CLEANFILES}
	rm -rf .deps .libs