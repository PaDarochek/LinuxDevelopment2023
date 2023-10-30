CC=clang
CFLAGS=-O0
IN_FILE=in.txt
OUT_FILE=out.txt
GEN=move ${IN_FILE}* ${OUT_FILE} log *.o *.so

all: move libremove.so test

move: move.c
	${CC} ${CFLAGS} $< -o $@

libremove.so: remove_protected.c
	${CC} ${CFLAGS} -c $< -o remove_protected.o
	${CC} ${CFLAGS} -shared remove_protected.o -o $@

test: move libremove.so
	echo "12345 abc" >${IN_FILE}
	strace -e fault=openat:when=1:error=ENOENT -P ${IN_FILE} ./$< ${IN_FILE} ${OUT_FILE} 2>>log && test $$? -eq 1 || test $$? -eq 1
	test -f ${IN_FILE}
	strace -e fault=openat:when=1:error=ENOENT -P ${OUT_FILE} ./$< ${IN_FILE} ${OUT_FILE} 2>>log && test $$? -eq 2 || test $$? -eq 2
	test -f ${IN_FILE}
	strace -e fault=read:when=1:error=ETXTBSY -P ${IN_FILE} ./$< ${IN_FILE} ${OUT_FILE} 2>>log && test $$? -eq 4 || test $$? -eq 4
	test -f ${IN_FILE}
	strace -e fault=close:when=1:error=EROFS -P ${IN_FILE} ./$< ${IN_FILE} ${OUT_FILE} 2>>log && test $$? -eq 6 || test $$? -eq 6
	test -f ${IN_FILE}
	strace -e fault=close:when=4:error=EROFS ./$< ${IN_FILE} ${OUT_FILE} 2>>log && test $$? -eq 7 || test $$? -eq 7
	test -f ${IN_FILE}
	strace -e fault=unlink:when=1:error=ETXTBSY -y -P ${IN_FILE} ./$< ${IN_FILE} ${OUT_FILE} 2>>log && test $$? -eq 8 || test $$? -eq 8
	test -f ${IN_FILE}

	echo "12345 abc" >${IN_FILE}_PROTECT
	LD_PRELOAD="./libremove.so" ./$< ${IN_FILE}_PROTECT ${OUT_FILE} 2>>log && test $$? -eq 8 || test $$? -eq 8
	test -f ${IN_FILE}_PROTECT

clean:
	rm -rf ${GEN}