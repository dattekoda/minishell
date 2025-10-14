# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/09 14:24:07 by khanadat          #+#    #+#              #
#    Updated: 2025/10/14 22:46:50 by khanadat         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell
CC			=	cc
CCFLAGS		:=	-Wall -Wextra -Werror

RL_FLAGS	:=	-lreadline

LIBFT_DIR	=	libft
LIBFT_A		=	$(LIBFT_DIR)/libft.a

INCS_FLAGS	:=	-I . \
				-I ast \
				-I err \
				-I exec \
				-I utils \
				-I prompt \
				-I ast/tokenizer \
				-I exec/builtin \
				-I exec/expand \
				-I exec/set_redirect \
				-I $(LIBFT_DIR)/includes \

SRCS		=	main.c \
				ast/ast_utils_cmd.c \
				ast/ast_utils_is0.c \
				ast/ast_utils_is1.c \
				ast/ast_utils_is2.c \
				ast/ast_utils_new_node.c \
				ast/ast_utils_red.c \
				ast/ast_utils_valid.c \
				ast/ast_utils.c \
				ast/ast.c \
				err/minishell_err0.c \
				err/minishell_err1.c \
				err/minishell_err2.c \
				err/minishell_err3.c \
				exec/exec.c \
				exec/exec_utils0.c \
				exec/exec_pipe.c \
				exec/exec_pipe_utils.c \
				exec/exec_utils2.c \
				exec/get_path.c \
				exec/set_redirect/set_redirect.c \
				exec/set_redirect/set_redirect_utils.c \
				prompt/prompt.c \
				prompt/minishell_set.c \
				ast/tokenizer/tokenizer.c \
				ast/tokenizer/tokenizer_utils.c \
				ast/tokenizer/tokenizer_validate.c \
				exec/builtin/builtin.c \
				exec/builtin/builtin_cd0.c \
				exec/builtin/builtin_cd1.c \
				exec/builtin/builtin_echo.c \
				exec/builtin/builtin_env.c \
				exec/builtin/builtin_exit.c \
				exec/builtin/builtin_export.c \
				exec/builtin/builtin_pwd.c \
				exec/builtin/builtin_unset.c \
				exec/expand/add_new_utils.c \
				exec/expand/classify_utils0.c \
				exec/expand/classify_utils1.c \
				exec/expand/expand.c \
				exec/expand/expand_utils_add.c \
				exec/expand/expand_utils.c \
				utils/minishell_utils0.c \
				utils/minishell_utils1.c \
				utils/minishell_utils2.c \
				utils/minishell_utils3.c \
				utils/minishell_utils4.c

OBJS_DIR	=	objs
OBJS		=	$(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))

UNAME		=	$(shell uname -s)

ifeq ($(UNAME),Darwin)
	RL_A		:=	-L /opt/homebrew/opt/readline/lib
	INCS_FLAGS	+=	-I /opt/homebrew/opt/readline/include
else ifeq ($(UNAME),Linux)
	RL_FLAGS	+=	-lncurses
else
	$(error Unsupported OS: $(UNAME))
endif

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT_A)
		$(CC) $(CCFLAGS) $^ $(RL_A) -o $@ $(RL_FLAGS)

$(OBJS_DIR)/%.o: %.c
		@mkdir -p $(dir $@)
		$(CC) $(CCFLAGS) $(INCS_FLAGS) -c $< -o $@

$(LIBFT_A):
		@$(MAKE) -s bonus -C $(LIBFT_DIR)

debug:	CCFLAGS	+=	-g -O0
debug:	all

clean:
		@rm -rf tester
		@rm -rf $(OBJS_DIR)
		@$(MAKE) -s fclean -C $(LIBFT_DIR)

fclean: clean
		rm -f $(NAME)

re: fclean all