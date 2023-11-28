TESTS_ENVIRONMENT = CK_VERBOSITY=$(CK_VERBOSITY)
TESTS = tests
check_PROGRAMS = tests

CLEANFILES=*.o *.gcov Makefile Makefile.in README.md *.la *.lo tests *.log *.trs tests.c

.ts.c:
	checkmk $< > $@

AM_CFLAGS = -I$(top_builddir)/src @CHECK_CFLAGS@
LDADD = $(top_builddir)/src/libbuf.la @CHECK_LIBS@

.PHONY: clean

clean:
	rm -rf ${CLEANFILES}
	rm -rf .deps .libs