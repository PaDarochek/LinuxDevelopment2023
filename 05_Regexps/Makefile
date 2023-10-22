CC=clang
CFLAGS=-g
GEN=esub esub*.txt sed*.txt

all: esub test

esub: esub.c
	${CC} ${CFLAGS} $< -o $@

test: esub
	./$< '1' '#2#' '123' >esub1.txt
	echo '123' | sed -E 's/1/#2#/' >sed1.txt
	cmp esub1.txt sed1.txt

	./$< '(a.*b)' '#\1#' '12aaabbb3' >esub2.txt
	echo '12aaabbb3' | sed -E 's/(a.*b)/#\1#/' >sed2.txt
	cmp esub2.txt sed2.txt

	./$< '(a.*b)' '#\\1\\#' '12aaabbb3' >esub3.txt
	echo '12aaabbb3' | sed -E 's/(a.*b)/#\\1\\#/' >sed3.txt
	cmp esub3.txt sed3.txt

	./$< '1(a.*b)2' '#\1#' 'sdg1aaabbb2ehjyj' >esub4.txt
	echo 'sdg1aaabbb2ehjyj' | sed -E 's/1(a.*b)2/#\1#/' >sed4.txt
	cmp esub4.txt sed4.txt

	./$< '1(a.*b)2' '#\0#' 'sdg1aaabbb2ehjyj' >esub5.txt
	echo 'sdg1aaabbb2ehjyj' | sed -E 's/1(a.*b)2/#\0#/' >sed5.txt
	cmp esub5.txt sed5.txt

	./$< '1(a.*b)2.*(c.*d)3.*(e.*f)4' '#\\0=\0,\\1=\1,\\2=\2,\\3=\3#' 'sdte1asg5hb2fgwceyd3kye6jf4dhrtj' >esub6.txt
	echo 'sdte1asg5hb2fgwceyd3kye6jf4dhrtj' | sed -E 's/1(a.*b)2.*(c.*d)3.*(e.*f)4/#\\0=\0,\\1=\1,\\2=\2,\\3=\3#/' >sed6.txt
	cmp esub6.txt sed6.txt

clean:
	rm -rf ${GEN}
