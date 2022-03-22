CFLAGS= -ggdb3 -Wall -Werror -pedantic
NAME=reverse_polish_calculator

$(NAME).app: $(NAME).c
	gcc $(CFLAGS) -o $(NAME).app $(NAME).c

doc: $(NAME).tex
	latexmk -xelatex $(NAME).tex
	latexmk -c $(NAME).tex
run: $(NAME).app
	./$(NAME).app
