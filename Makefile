##
## EPITECH PROJECT, 2024
## Makefile
## File description:
## Makefile
##

NAME	=	myftp

SRC	=	src/*.cpp include/*.cpp

OBJ = $(SRC:.c=.o)

all:	$(NAME)

$(NAME):
	g++ -o $(NAME) $(SRC) -I include/
	@echo "\033[32m= = = = =  COMPILATION COMPLETED  = = = = =\033[0m"

clean:
	@$(RM) $(NAME)

fclean: clean
	@$(RM) $(NAME)
	@$(RM) *~
	@echo "\033[31m= = = = = =   CLEAR COMPLETED   = = = = = =\033[0m"

re: fclean all
