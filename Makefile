# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dgoremyk <dgoremyk@student.42wolfsburg.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/22 19:00:37 by dgoremyk          #+#    #+#              #
#    Updated: 2022/12/02 14:33:09 by dgoremyk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#name of the program we are making
NAME = pipex

CC = gcc -g

CFLAGS = -Wall -Werror -Wextra

RM = rm -f

SRC = main.c arg_checker.c exit.c parsing.c open_files.c

OBJ = $(SRC:.c=.o)

LIBFT_OBJ = libft/*.o
	
all: $(NAME)

LIBRARY:
	make -C libft

# -C option is for running MAKE command on libft subfolder
$(NAME):  LIBRARY $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT_OBJ) -o pipex

clean:
	$(MAKE) clean -C libft
	$(RM) $(OBJ)

	
fclean: clean
	$(MAKE) fclean -C libft
	$(RM) $(NAME)
	
re: fclean all

.PHONY: all clean fclean re