# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lzaengel <lzaengel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/22 16:43:52 by lzaengel          #+#    #+#              #
#    Updated: 2024/03/22 16:47:43 by lzaengel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philosophers

CFLAGS = -Wall -Werror -Wextra

SRC =	./src/main.c\
		./src/error.c\
		./src/routine.c\
		./src/utils.c

OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ)
			clang -o $(NAME) $(OBJ) $(CFLAGS)

clean :
			rm -rf $(OBJ)

fclean : clean
			rm -rf $(NAME)

re : fclean all

.PHONY : all clean fclean re