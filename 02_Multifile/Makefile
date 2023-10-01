GENERATES = prog prog-a prog-so liboutput_static.a liboutput.so prog.out prog-a.out prog-so.out
TRASH = *.o *~ o.*
LIB_SOURCES = fun.o const.o
CFLAGS_SO = -fPIC

all: prog liboutput_static.a liboutput.so prog-a prog-so test

prog:   const.o fun.o prog.o

%.o: %.c
	$(CC) $(CFLAGS_SO) -c $< -o $@

fun.o:  outlib.h

prog.o: outlib.h

prog-a: prog.o liboutput_static.a
	$(CC) -L. $< -loutput_static -o $@

liboutput_static.a: $(LIB_SOURCES)
	ar -rcs $@ $^

prog-so: prog.o liboutput.so
	$(CC) -L. $< -loutput -o $@

liboutput.so: $(LIB_SOURCES)
	$(CC) -shared $(CFLAGS_SO) $^ -o $@

# tests will fail because prog's Usage differs
test: prog.out prog-a.out prog-so.out
	cmp prog.out prog-a.out
	cmp prog-so.out prog-a.out

prog.out: prog
	./$< > $@ 2>&1
	./$< "abc" >> $@ 2>&1
	./$< "abc" "def" "ghi" >> $@ 2>&1

prog-a.out: prog-a
	./$< > $@ 2>&1
	./$< "abc" >> $@ 2>&1
	./$< "abc" "def" "ghi" >> $@ 2>&1

prog-so.out: prog-so
	LD_LIBRARY_PATH=$(shell pwd):$$LD_LIBRARY_PATH ./$< > $@ 2>&1
	LD_LIBRARY_PATH=$(shell pwd):$$LD_LIBRARY_PATH ./$< "abc" >> $@ 2>&1
	LD_LIBRARY_PATH=$(shell pwd):$$LD_LIBRARY_PATH ./$< "abc" "def" "ghi" >> $@ 2>&1

clean:
	rm -f $(TRASH) $(GENERATES)
