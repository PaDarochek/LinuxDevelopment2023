bin_PROGRAMS=rhasher
rhasher_SOURCES=rhasher.c
rhasher_LDADD=$(LIBREADLINE)
TESTS=test_MD5.sh test_md5.sh test_SHA1.sh test_sha1.sh test_TTH.sh test_tth.sh
CLEANFILES=test*.log test*.ideal auto* aclocal* compile config.* configure configure~ configure.scan COPYING depcomp INSTALL install-sh Makefile.in Makefile missing stamp-h1 test-driver

clean-local:
	-rm -rf autom4te.cache .deps