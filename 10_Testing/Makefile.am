SUBDIRS = src tests

CLEANFILES=*.o *.gcov Makefile Makefile.in README.md *.la *.lo aclocal* autoscan* compile config.* configure configure.scan configure~ depcomp install* libtool ltmain.sh Makefile Makefile.in missing stamp* test-driver

demo:	all
	./src/buf

checklog:	check
	cat tests/*.log

gcov:	check
	$(MAKE) $(MAKEFLAGS) -C src gcov

.PHONY: clean

clean:
	make -C src/ clean
	make -C tests/ clean
	rm -rf ${CLEANFILES}
	rm -rf autom4te.cache