# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kpanikka <kpanikka@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/03 18:36:40 by kpanikka          #+#    #+#              #
#    Updated: 2022/12/11 12:36:58 by kpanikka         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME	= minishell
cc		= gcc -g
CFLAG	= -Wall -Werror -Wextra -I libft/ -g -fsanitize=address
RMFLAG  = -f
SRC		= minishell.c parse.c execute.c error.c dlist.c echo.c  \
		parse_spl_char.c parse_quote.c env.c elist.c util.c pwd.c dir.c \
		export.c parse_split.c
LIBFT	= -L libft -lft


OBJS	= $(SRC:.c=.o)

all		: $(NAME)

bonus	: all
 
%.o : %.c
	$(CC) $(CFLAG) -c $< -o $@

clean	:
		@make clean -C libft/
		$(RM) $(RMFLAG) $(OBJS)

fclean	: clean
	$(RM) $(RMFLAG) $(NAME)

re		: fclean all

$(NAME) : $(OBJS)
		@echo "\n"
		@echo "\033[0;32m*************************\n"
		@make -C libft/

		@echo "Compiling minishell...\n"
		@echo "*************************\n"

		@$(cc) $(CFLAG) $(OBJS) -o  $(NAME) $(LIBFT) -lreadline 
		@echo "\n\033[0mDone !"

.PHONY : all clean fclean re