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

test: prog.out prog-a.out prog-so.out
	cmp prog.out prog-a.out
	cmp prog-so.out prog-a.out

prog.out: prog
	bash -c "exec -a prog ./$< > $@ 2>&1"
	bash -c "exec -a prog ./$< "abc" >> $@ 2>&1"
	bash -c "exec -a prog ./$< "abc" "def" "ghi" >> $@ 2>&1"

prog-a.out: prog-a
	bash -c "exec -a prog ./$< > $@ 2>&1"
	bash -c "exec -a prog ./$< "abc" >> $@ 2>&1"
	bash -c "exec -a prog ./$< "abc" "def" "ghi" >> $@ 2>&1"

prog-so.out: prog-so
	LD_LIBRARY_PATH=$(shell pwd):$$LD_LIBRARY_PATH bash -c "exec -a prog ./$< > $@ 2>&1"
	LD_LIBRARY_PATH=$(shell pwd):$$LD_LIBRARY_PATH bash -c "exec -a prog ./$< "abc" >> $@ 2>&1"
	LD_LIBRARY_PATH=$(shell pwd):$$LD_LIBRARY_PATH bash -c "exec -a prog ./$< "abc" "def" "ghi" >> $@ 2>&1"

clean:
	rm -f $(TRASH) $(GENERATES)
