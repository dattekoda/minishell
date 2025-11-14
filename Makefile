# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: khanadat <khanadat@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/09 14:24:07 by khanadat          #+#    #+#              #
#    Updated: 2025/11/14 11:15:43 by khanadat         ###   ########.fr        #
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
				-I $(LIBFT_DIR)/includes

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
				exec/exec_utils1.c \
				exec/exec_pipe.c \
				exec/exec_pipe_utils.c \
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
				exec/expand/expand_wc_red.c \
				exec/expand/expand_wc_utils.c \
				exec/expand/expand_wc_word.c \
				exec/expand/expand.c \
				exec/expand/expand_utils_add.c \
				exec/expand/expand_utils.c \
				utils/minishell_utils0.c \
				utils/minishell_utils1.c \
				utils/minishell_utils2.c \
				utils/minishell_utils3.c \
				utils/minishell_utils4.c

BONUS_INCS_FLAGS	:=	-I .bonus \
						-I .bonus/ast \
						-I .bonus/err \
						-I .bonus/exec \
						-I .bonus/utils \
						-I .bonus/prompt \
						-I .bonus/ast/tokenizer \
						-I .bonus/exec/builtin \
						-I .bonus/exec/expand \
						-I .bonus/exec/set_redirect \
						-I $(LIBFT_DIR)/includes

BONUS_SRCS	=	.bonus/main_bonus.c \
				.bonus/ast/ast_utils_cmd_bonus.c \
				.bonus/ast/ast_utils_is0_bonus.c \
				.bonus/ast/ast_utils_is1_bonus.c \
				.bonus/ast/ast_utils_is2_bonus.c \
				.bonus/ast/ast_utils_new_node_bonus.c \
				.bonus/ast/ast_utils_red_bonus.c \
				.bonus/ast/ast_utils_valid_bonus.c \
				.bonus/ast/ast_utils_bonus.c \
				.bonus/ast/ast_bonus.c \
				.bonus/err/minishell_err0_bonus.c \
				.bonus/err/minishell_err1_bonus.c \
				.bonus/err/minishell_err2_bonus.c \
				.bonus/err/minishell_err3_bonus.c \
				.bonus/exec/exec_bonus.c \
				.bonus/exec/exec_utils0_bonus.c \
				.bonus/exec/exec_utils1_bonus.c \
				.bonus/exec/exec_pipe_bonus.c \
				.bonus/exec/exec_pipe_utils_bonus.c \
				.bonus/exec/get_path_bonus.c \
				.bonus/exec/set_redirect/set_redirect_bonus.c \
				.bonus/exec/set_redirect/set_redirect_utils_bonus.c \
				.bonus/prompt/prompt_bonus.c \
				.bonus/prompt/minishell_set_bonus.c \
				.bonus/ast/tokenizer/tokenizer_bonus.c \
				.bonus/ast/tokenizer/tokenizer_utils_bonus.c \
				.bonus/ast/tokenizer/tokenizer_validate_bonus.c \
				.bonus/exec/builtin/builtin_bonus.c \
				.bonus/exec/builtin/builtin_cd0_bonus.c \
				.bonus/exec/builtin/builtin_cd1_bonus.c \
				.bonus/exec/builtin/builtin_echo_bonus.c \
				.bonus/exec/builtin/builtin_env_bonus.c \
				.bonus/exec/builtin/builtin_exit_bonus.c \
				.bonus/exec/builtin/builtin_export_bonus.c \
				.bonus/exec/builtin/builtin_pwd_bonus.c \
				.bonus/exec/builtin/builtin_unset_bonus.c \
				.bonus/exec/expand/add_new_utils_bonus.c \
				.bonus/exec/expand/classify_utils0_bonus.c \
				.bonus/exec/expand/classify_utils1_bonus.c \
				.bonus/exec/expand/expand_wc_red_bonus.c \
				.bonus/exec/expand/expand_wc_utils_bonus.c \
				.bonus/exec/expand/expand_wc_word_bonus.c \
				.bonus/exec/expand/expand_bonus.c \
				.bonus/exec/expand/expand_utils_add_bonus.c \
				.bonus/exec/expand/expand_utils_bonus.c \
				.bonus/utils/minishell_utils0_bonus.c \
				.bonus/utils/minishell_utils1_bonus.c \
				.bonus/utils/minishell_utils2_bonus.c \
				.bonus/utils/minishell_utils3_bonus.c \
				.bonus/utils/minishell_utils4_bonus.c

OBJS_DIR		=	objs
OBJS			=	$(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))

BONUS_OBJS_DIR	=	bonus_objs
BONUS_OBJS		=	$(addprefix $(BONUS_OBJS_DIR)/, $(BONUS_SRCS:.c=.o))

UNAME		=	$(shell uname -s)

ifeq ($(UNAME),Darwin)
	RL_A				:=	-L /opt/homebrew/opt/readline/lib
	INCS_FLAGS			+=	-I /opt/homebrew/opt/readline/include
	BONUS_INCS_FLAGS	+=	-I /opt/homebrew/opt/readline/include
else ifeq ($(UNAME),Linux)
	RL_FLAGS	+=	-lncurses
else
	$(error Unsupported OS: $(UNAME))
endif

ifeq ($(MAKECMDGOALS),bonus)
	BUILD_OBJS	:= $(BONUS_OBJS)
else ifeq ($(MAKECMDGOALS),rebonus)
	BUILD_OBJS	:= $(BONUS_OBJS)
else
	BUILD_OBJS	:= $(OBJS)
endif

.PHONY: all clean fclean re bonus rebonus

all: $(NAME)

bonus: $(NAME)

$(NAME): $(BUILD_OBJS) $(LIBFT_A)
		$(CC) $(CCFLAGS) $^ $(RL_A) -o $@ $(RL_FLAGS)

$(BUILD_OBJS): $(LIBFT_A)

$(OBJS_DIR)/%.o: %.c
		@mkdir -p $(dir $@)
		$(CC) $(CCFLAGS) $(INCS_FLAGS) -c $< -o $@

$(BONUS_OBJS_DIR)/%.o: %.c
		@mkdir -p $(dir $@)
		$(CC) $(CCFLAGS) $(BONUS_INCS_FLAGS) -c $< -o $@

$(LIBFT_A): $(LIBFT_DIR)
		@$(MAKE) -s bonus -C $<

$(LIBFT_DIR):
		git clone git@github.com:dattekoda/libft.git $@
		rm -rf $@/.git

debug:	CCFLAGS	+=	-g -O0
debug:	all

clean:
		@rm -rf tester
		@rm -rf $(OBJS_DIR)
		@rm -rf $(BONUS_OBJS_DIR)
		@$(MAKE) -s fclean -C $(LIBFT_DIR)

fclean: clean
		rm -f $(NAME)

re: fclean all

rebonus: fclean bonus