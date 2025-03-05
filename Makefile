##
## EPITECH PROJECT, 2024
## Makefile
## File description:
## Makefile
##

NAME	=	myftp

SRC	=	server.c

OBJ = $(SRC:.c=.o)

all:	$(NAME)

$(NAME):
	mv server.cpp server.c
	@$(CC) -o $(NAME) server.c
	mv server.c server.cpp
	@echo "\033[32m= = = = =  COMPILATION COMPLETED  = = = = =\033[0m"

clean:
	@$(RM) $(NAME)

fclean: clean
	@$(RM) $(NAME)
	@$(RM) *~
	@echo "\033[31m= = = = = =   CLEAR COMPLETED   = = = = = =\033[0m"

re: fclean all
