# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: huahmad <huahmad@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/11 18:09:09 by huahmad           #+#    #+#              #
#    Updated: 2025/03/13 14:34:01 by huahmad          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
LIBFT = libft/libft.a
CFLAGS = -Wextra -Wall -Werror  
OBJS = ${SRCS:.c=.o}
SRCS = \
		pipex.c \
		pipex2.c \

all: $(LIBFT) $(NAME)

$(NAME) : $(OBJS)
	cc $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT)
	

$(LIBFT):
	$(MAKE) -s -C libft

clean:
	rm -f *.o
	rm -f $(NAME)
	rm -f *.txt
	rm -f *:Zone.Identifier

fclean: clean
	@rm -rf $(NAME)
	$(MAKE) -C libft fclean

re: fclean all