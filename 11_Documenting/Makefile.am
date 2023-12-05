@DX_RULES@

all-local:  doxygen-doc

SUBDIRS = src po
CLEANFILES=*/*.o */*~

gitclean:
	git clean -df

http: doxygen-doc
	python3 -m http.server --directory $</html