# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abarot <abarot@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/07/02 20:31:48 by abarot            #+#    #+#              #
#    Updated: 2020/09/11 18:29:20 by abarot           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell

SRCS	=	srcs/main.c srcs/parse_ft.c srcs/ft_redirect_cmd.c srcs/env_ft.c \
			srcs/pipe_ft.c srcs/signal_handling.c srcs/redirection_ft.c

OBJS	=	$(SRCS:.c=.o)

CFLAGS	=	-Wall -Wextra -Werror

INCL	=	include

LIB 	=  libft.a

LIB_PATH	=	libft

RM	=	rm -f
			
%.o : %.c
		gcc $(CFLAGS) -c $< -o $@ -I$(INCL)

all	:	
		make -C libft
		make $(NAME)

$(NAME)	: $(OBJS) 
			gcc $(CFLAGS) $(OBJS) -L./libft/. -lft -o $(NAME) -I$(INCL)
			
clean	:
		$(RM) $(OBJS) && make -C libft fclean

fclean	:	clean
		$(RM) $(NAME) 

re	:	fclean all