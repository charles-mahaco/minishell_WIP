NAME		=	libftprintf.a



CC			=	gcc

CFLAGS		+=	-Werror -Wall -Wextra

AR			=	ar -rcs



SRC			=	ft_printf.c \
				src/print_alpha.c \
				src/print_num.c \
				src/print_d.c \
				src/parsing.c \
				utils/ft_printf_utils.c \
				utils/ft_printf_utils_int.c

SRC_BONUS	=	bonus/ft_printf_bonus.c \
				bonus/src/print_alpha_bonus.c \
				bonus/src/print_num_bonus.c \
				bonus/src/print_d_bonus.c \
				bonus/src/parsing_bonus.c \
				bonus/utils/ft_printf_utils_bonus.c \
				bonus/utils/ft_printf_utils_int_bonus.c


OBJS		=	$(SRC:%.c=%.o)

OBJS_BONUS	=	$(SRC_BONUS:%.c=%.o)


all:		$(NAME)

$(NAME): $(OBJS) ft_printf.h
			$(AR) $(NAME) $(OBJS)

%.o: %.c
			$(CC) $(CFLAGS) -c $< -o $@ -I.


bonus: $(OBJS_BONUS) ft_printf_bonus.h
			$(AR) $(NAME) $(OBJS_BONUS)

clean:
			rm -rf $(OBJS) $(OBJS_BONUS)

fclean: clean
			rm -rf $(NAME)

re: fclean all

rebonus: fclean bonus

.PHONY: clean fclean all re