# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rliou-ke <rliou-ke@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/12/07 18:21:40 by rliou-ke          #+#    #+#              #
#    Updated: 2016/05/05 16:42:55 by akarin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= 	lem-in
SRC		=	main.c get_next_line.c find_antsnbr.c str_parse.c \
			find_rooms.c assign.c mk_rooms.c fill_connections.c get_room_links.c \
			find_connections.c ft_is_solvable.c print.c instantiate_ants.c\
			little_ant_gonna_lift.c shit_just_got_serious.c read_opts.c\
			test_le-min.c
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
