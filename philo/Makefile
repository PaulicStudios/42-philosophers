# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pgrossma <pgrossma@student.42heilbronn.de> +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/28 14:55:39 by pgrossma          #+#    #+#              #
#    Updated: 2024/03/28 15:01:49 by pgrossma         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

VPATH	= src
SRC		= main.c
OBJDIR	= obj
OBJ		= $(addprefix $(OBJDIR)/, $(SRC:.c=.o))

CC		= cc
CFLAGS	= -Wall -Wextra -Werror #-fsanitize=address -fsanitize=undefined -fno-sanitize-recover=all -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fno-sanitize=null -fno-sanitize=alignment
INC		= -I inc

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $(NAME) $(INC)

$(OBJDIR)/%.o: %.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@ $(INC)

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all
