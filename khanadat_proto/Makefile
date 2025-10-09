# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/09 14:24:07 by khanadat          #+#    #+#              #
#    Updated: 2025/10/09 16:35:17 by khanadat         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell
CC			=	cc
CCFLAGS		=	-Wall -Wextra -Werror
RDFLAGS		=	-lreadline -lncurses

LIBFT_DIR	=	libft
LIBFT_A		=	$(LIBFT_DIR)/libft.a

INCS_FLAGS	=	-I . \
				-I ast \
				-I err \
				-I exec \
				-I library \
				-I prompt \
				-I ast/tokenizer \
				-I exec/builtin \
				-I exec/expand \
				-I $(LIBFT_DIR)/includes

SRCS		=	exec/exec.c \
				exec/exec_utils0.c \
				exec/exec_utils1.c \
				exec/get_path.c \
				exec/set_redirect.c \
				exec/set_redirect_utils.c \
				library/minishell_lib0.c \
				library/minishell_lib1.c \
				library/minishell_lib2.c \
				library/minishell_lib3.c \
				library/minishell_lib4.c \
				prompt/prompt_main.c \
				prompt/prompt_set.c \
				ast/tokenizer/tokenizer.c \
				ast/tokenizer/tokenizer_utils.c \
				ast/tokenizer/tokenizer_validate.c \
				exec/builtin/builtin.c \
				exec/builtin/builtin_cd.c \
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
				exec/expand/expand_utils.c

OBJS_DIR	=	objs
OBJS		=	$(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT_A)
		$(CC) $(CCFLAGS) $^ $(LIBFT_A) -o $@ $(RDFLAGS)

$(OBJS_DIR)/%.o: %.c
		@mkdir -p $(dir $@)
		$(CC) $(CCFLAGS) -c $< -o $@ $(INCS_FLAGS)

$(LIBFT_A):
		@$(MAKE) -s -C $(LIBFT_DIR)

clean:
		@rm -rf $(OBJS_DIR)
		@$(MAKE) -s fclean -C $(LIBFT_DIR)

fclean: clean
		@rm -f $(NAME)

re: fclean all