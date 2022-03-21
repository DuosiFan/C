CFLAGS= -ggdb3 -Wall -Werror -pedantic

build: strindex.c
	gcc $(CFLAGS) -o strindex.app strindex.c
doc: strindex.tex
	latexmk -xelatex strindex.tex
	latexmk -c strindex.tex
run: strindex
	./strindex
