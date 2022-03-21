CFLAGS= -ggdb3 -Wall -Werror -pedantic

string2numeric.app: string2numeric.c
	gcc $(CFLAGS) -o string2numeric.app string2numeric.c
doc: string2numeric.tex
	latexmk -xelatex string2numeric.tex
	latexmk -c string2numeric.tex
run: string2numeric.app
	./string2numeric.app
