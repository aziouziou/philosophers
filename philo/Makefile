# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abziouzi <abziouzi@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/19 11:35:27 by abziouzi          #+#    #+#              #
#    Updated: 2023/04/29 22:25:09 by abziouzi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #

#	Compilation

NAME			=	philo

CC				=	cc

CFLAGS			=	-Wall -Wextra -Werror -pthread

RM				=	rm -rf

#	Files & Directories

DIR_HEADERS		=	./inc/

DIR_OBJ			=	./obj/

DIR_SRC			=	./src/

SRCS			=	philo_main.c	\
					philo_parser.c	\
					philo_routine.c	\
					philo_utils.c

SRC				=	$(SRCS)

OBJ				=	$(SRC:%.c=$(DIR_OBJ)%.o)

#	Rules

all				:	$(NAME)

$(NAME)			:	$(OBJ)
					@$(CC) $(CFLAGS) -I $(DIR_HEADERS) $(OBJ) -o $(NAME)

$(OBJ)			:	| $(DIR_OBJ)

$(DIR_OBJ)%.o	:	$(DIR_SRC)%.c
					@$(CC) $(CFLAGS) -I $(DIR_HEADERS) -c $< -o $@

$(DIR_OBJ)		:
					@mkdir $(DIR_OBJ)

clean			:
					@$(RM) $(DIR_OBJ)

fclean			:	clean
					@$(RM) $(NAME)

re				:	fclean all

#	Norme

norm			:
					@$(NORMINETTE) $(DIR_SRC)
					@$(NORMINETTE) $(DIR_HEADERS)

.PHONY			:	all clean fclean re norm
