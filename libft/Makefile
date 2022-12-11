# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kpanikka <kpanikka@student.42abudhabi.ae>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/30 13:37:19 by kpanikka          #+#    #+#              #
#    Updated: 2022/03/08 08:51:48 by kpanikka         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS			=	ft_tolower.c ft_isdigit.c ft_substr.c ft_calloc.c \
				ft_strlen.c ft_strjoin.c ft_memcpy.c ft_memset.c \
				ft_bzero.c ft_memmove.c ft_strlcat.c ft_memchr.c \
				ft_memcmp.c ft_isalpha.c ft_isalnum.c ft_isascii.c \
				ft_isprint.c ft_toupper.c ft_strchr.c ft_strrchr.c \
				ft_strncmp.c ft_atoi.c ft_strdup.c ft_strlcpy.c \
				ft_strnstr.c ft_strtrim.c ft_substr.c ft_putchar_fd.c \
				ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
				ft_split.c ft_strmapi.c ft_striteri.c ft_itoa.c	\

BSRCS 			=	ft_lstnew.c ft_lstadd_front.c ft_lstsize.c \
				ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c \
				ft_lstclear.c ft_lstiter.c ft_lstmap.c

OBJS			= $(SRCS:.c=.o)
CC				= gcc
RM				= rm -f
CFLAGS			= -g -Wall -Wextra -Werror -I.

NAME			= libft.a

all:			$(NAME)

BOBJS			= $(BSRCS:.c=.o)

bonus :			$(BOBJS)
				ar rcs $(NAME) $(BOBJS)

$(NAME):		$(OBJS)
				ar rcs $(NAME) $(OBJS)

clean:
				$(RM) $(OBJS) 
				$(RM) $(BOBJS) 

fclean:			clean
				$(RM) $(NAME)

re:				fclean $(NAME)

.PHONY:			all clean fclean re
