# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rliou-ke <rliou-ke@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/12/07 18:21:40 by rliou-ke          #+#    #+#              #
#    Updated: 2016/03/11 09:24:56 by rliou-ke         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= 	lem-in
SRC		=	main.c
OBJDIR	=	trash
OBJ		=	$(patsubst %.c,$(OBJDIR)/%.o,$(SRC))
LIB		=	-L libft/ -lft
HEADER	=	-Ilibft/ -Iinclude/
CFLAGS	=	-Wall -Wextra -Werror
CC		=	gcc $(CFLAGS)

SYS 	:= $(shell gcc -dumpmachine)
ifneq (, $(findstring cygwin, $(SYS)))
	 CLEAN = $(NAME).exe.stackdump
endif

.PHONY: all clean fclean re

all : $(NAME)

$(NAME) : $(OBJ)
	@make -C libft/
	@$(CC) -o $@ $^ $(LIB)
	@echo "$(NAME) has been created !"

$(OBJ) : | $(OBJDIR)

$(OBJDIR) :
	@mkdir -p $@

$(OBJDIR)/%.o : src/%.c
	@$(CC) $(HEADER) -c $< -o $@

clean :
	@rm -fr $(OBJDIR) $(CLEAN)
	@make -C libft/ clean

fclean : clean
	@rm -f $(NAME)
	@make -C libft/ fclean
	@echo "$(NAME) & libft.a have been removed."

re : fclean all
