# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: charles <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/05 15:58:14 by charles           #+#    #+#              #
#    Updated: 2021/10/05 15:58:17 by charles          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				= minishell
CC					= gcc
RM					= rm -rf

CFLAGS				= -Wall -Wextra -Werror
IFLAGS				= -I${INC_DIR}

SRCS_DIR			= srcs
INC_DIR				= includes
OBJS_DIR			= objs

INC				 	= $(shell find ${INC_DIR} -type f -name "*.h")
SRCS 				= $(notdir $(shell find ${SRCS_DIR} -type f -name "*.c"))
OBJS 				= $(addprefix ${OBJS_DIR}/, ${SRCS:.c=.o})
vpath				%.c $(shell find ${SRCS_DIR} -type d)
				
all: 				init ${NAME}

init:
					$(shell mkdir -p ${OBJS_DIR})

${NAME}:			${OBJS}
					@${CC} ${CFLAGS} ${IFLAGS} -o $@ $^
					@echo "Done"
					
${OBJS_DIR}/%.o:	%.c
					@${CC} ${CFLAGS} ${IFLAGS} -c $< -o $@
	
clean:
					@${RM} ${OBJS_DIR}

fclean:				clean
					@${RM} ${NAME}
					@${RM} ${CHECK}

re:					fclean all

.SUFFIXES:			.c .o .h
.PHONY:				all clean fclean re
