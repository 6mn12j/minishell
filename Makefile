CFLAGS = -Wall -Wextra -Werror -Iinclude
CC = gcc

# 인텔 맥 ( 클러스터 PC X )
# READLINE_LIB 	= -lreadline -L/usr/local/opt/readline/lib
# READLINE_INC	= -I/usr/local/opt/readline/include

# 인텔 맥 ( 클러스터 PC O )
# READLINE_LIB 	= -lreadline -L /Users/$(USER)/.brew/opt/readline/lib
# READLINE_INC	= -I /Users/$(USER)/.brew/opt/readline/include

# M1 맥 ( 클러스터 PC X )
READLINE_LIB	= -lreadline -L/opt/homebrew/opt/readline/lib
READLINE_INC	= -I/opt/homebrew/opt/readline/include

SRCS = src/main.c \
		src/utils/minishell_util1.c \

LIBFT = libft/libft.a

NAME = minishell


OBJS = $(SRCS:.c=.o)

all:  $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(READLINE_INC) $(READLINE_LIB)

$(LIBFT):
	make -C ./libft

%.o: %.c
	$(CC) $(CFLAGS) $(READLINE_INC) -c $< -o $@

clean:
	make clean -C libft/
	rm -rf $(OBJS)


fclean: clean
	make fclean -C libft/
	rm -rf $(NAME) $(OBJS)

re: fclean all
