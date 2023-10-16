CC=gcc
CFLAGS=-O0 -g
GEN=*.o range out1.txt out2.txt res1.txt res2.txt

all: range test

range: range.c
	${CC} ${CFLAGS} $< -o $@

test: range
	gdb -x gdb1.txt --batch --quiet --args ./$< >out1.txt
	gdb -x gdb2.txt --batch --quiet --args ./$< >out2.txt
	grep @@@ out1.txt >res1.txt
	grep @@@ out2.txt >res2.txt
	cmp res1.txt ideal1.txt
	cmp res2.txt ideal2.txt

clean:
	rm -rf ${GEN}