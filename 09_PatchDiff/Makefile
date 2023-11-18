CC=clang
GEN=*.o maze_gen maze_gen_v1 maze_gen_v2 maze_gen_v3 maze_gen_v1.c maze_gen_v2.c maze_gen_v3.c *.orig *.rej

all: maze_gen maze_gen_v1 maze_gen_v2 maze_gen_v3 run

maze_gen: maze_gen.c
	${CC} $< -o $@

maze_gen_v1.c: maze_gen.c v1.patch
	patch -b $< v1.patch
	mv $< maze_gen_v1.c
	mv $<.orig $<

maze_gen_v1: maze_gen_v1.c
	${CC} $< -o $@

maze_gen_v2.c: maze_gen_v1.c v2.patch
	patch -b $< v2.patch
	mv $< maze_gen_v2.c
	mv $<.orig $<

maze_gen_v2: maze_gen_v2.c
	${CC} $< -o $@

maze_gen_v3.c: maze_gen_v2.c v3.patch
	patch -b $< v3.patch
	mv $< maze_gen_v3.c
	mv $<.orig $<

maze_gen_v3: maze_gen_v3.c
	${CC} $< -o $@

run: maze_gen maze_gen_v1 maze_gen_v2 maze_gen_v3
	./maze_gen
	./maze_gen_v1 3
	./maze_gen_v2 " *" 5
	./maze_gen_v3 5 " *" 3
	./maze_gen_v3 5 " *" 3
	./maze_gen_v3 5 " *" 3

clean:
	rm -rf ${GEN}
