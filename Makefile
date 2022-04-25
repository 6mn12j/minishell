CFLAGS = -Wall -Wextra -Werror -Iinclude
CC = gcc

# 인텔 맥 ( 클러스터 PC X )
# READLINE_LIB 	= -lreadline -L/usr/local/opt/readline/lib
# READLINE_INC	= -I/usr/local/opt/readline/include

# 인텔 맥 ( 클러스터 PC O )
READLINE_LIB 	= -lreadline -L /Users/$(USER)/.brew/opt/readline/lib
READLINE_INC	= -I /Users/$(USER)/.brew/opt/readline/include

# M1 맥 ( 클러스터 PC X )
# READLINE_LIB	= -lreadline -L/opt/homebrew/opt/readline/lib
# READLINE_INC	= -I/opt/homebrew/opt/readline/include

SRCS = srcs/main.c \
		srcs/env.c \
		srcs/execute.c \
		srcs/signal.c \
		srcs/utils/minishell_util1.c \
		srcs/utils/error.c \
		srcs/pipe/pipe.c \
		srcs/cmd/execute.c \
		srcs/redirection/redirection.c \
		srcs/utils/ft_free.c \
		srcs/utils/test.c \
		srcs/parse/parser.c \
		srcs/parse/ft_split_cmds.c \
		srcs/parse/set_is_path.c \
		srcs/parse/parse_cmds.c \
		srcs/parse/set_cmd_list.c \
		srcs/list/cmd_list.c \
		srcs/list/redir_list.c 

LIBFT = libft/libft.a

GNL = get_next_line/libgnl.a

NAME = minishell

OBJS = $(SRCS:.c=.o)

all:  $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(GNL)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(GNL) $(READLINE_INC) $(READLINE_LIB)

$(LIBFT):
	@make -C ./libft

$(GNL):
	@make -C ./get_next_line

%.o: %.c
	$(CC) $(CFLAGS) $(READLINE_INC) -c $< -o $@

clean:
	@make clean -C libft/
	@make clean -C get_next_line/
	@rm -rf $(OBJS)


fclean: clean
	@make fclean -C libft/
	@make fclean -C get_next_line/
	@rm -rf $(NAME) $(OBJS)

re: fclean all
