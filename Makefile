# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kpanikka <kpanikka@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/03 18:36:40 by kpanikka          #+#    #+#              #
#    Updated: 2022/12/25 22:46:56 by kpanikka         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME	= minishell
cc		= gcc -g
CFLAG	= -Wall -Werror -Wextra  -g -fsanitize=address
RDLINE_L = -L /usr/local/opt/readline/lib -lreadline
RDLINE_I = -I /usr/local/opt/readline/include

RMFLAG  = -f


PARSING	=	minishell parse  error dlist   \
		parse_spl_char parse_quote env elist util  \
		parse_split parse_split_helper parse_expand signals \
		hardcodes heredoc

EXECUTION = execution file_util	env validation builtin cmd_execution
	  

SRC =	$(addsuffix .c, $(addprefix parsing/, $(PARSING))) \
		$(addsuffix .c,$(addprefix execution/, $(EXECUTION))) \

LIBFT	= -L libft -lft


OBJS	= $(SRC:.c=.o)

all		: $(NAME)

bonus	: all
 
%.o : %.c
	$(CC) $(CFLAG) $(RDLINE_I)  -I includes/ -I libft/ -c $< -o $@

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

		@$(cc) $(CFLAG) $(OBJS) -o    $(NAME) $(LIBFT)  $(RDLINE_L) 
		@echo "\n\033[0mDone !"

.PHONY : all clean fclean re
