# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kpanikka <kpanikka@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/03 18:36:40 by kpanikka          #+#    #+#              #
#    Updated: 2022/12/12 12:57:27 by kpanikka         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME	= minishell
cc		= gcc -g
CFLAG	= -Wall -Werror -Wextra -I includes/ -I libft/ -g -fsanitize=address
RMFLAG  = -f


PARSING	=	minishell parse execute error dlist echo  \
		parse_spl_char parse_quote env elist util pwd dir \
		export parse_split

EXECUTION = execution file_util	
	  

SRC =$(addsuffix .c, $(addprefix parsing/, $(PARSING))) \
		$(addsuffix .c,$(addprefix execution/, $(EXECUTION))) \

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