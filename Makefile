NAME= minishell
CFLAGS += -g   -Wextra -Wall -Werror
# CFLAGS += -g -Wextra -Wall
D ?= 0
ifeq ($(D), 1)
	CFLAGS += -fsanitize=address
endif
CC = cc
SRC =  main.c \
		./shell_subsys/readline.c \
		./shell_subsys/signal_handling.c \
		./shell_subsys/signal_handling2.c	\
		./shell_subsys/environment_handling.c \
		./shell_subsys/shell_subsys_utils.c \
		./shell_subsys/ft_env.c \
		./shell_subsys/ft_export_utils.c \
		./shell_subsys/ft_export_utils2.c \
		./shell_subsys/ft_export.c \
		./shell_subsys/ft_unset.c \
		./shell_subsys/ft_echo.c \
		./shell_subsys/ft_pwd.c \
		./shell_subsys/ft_cd.c \
		./shell_subsys/env_var_extension.c \
		./shell_subsys/executor.c \
		./shell_subsys/ft_heredoc.c \
		./shell_subsys/ft_heredoc_helper.c \
		./shell_subsys/ft_heredoc_helper2.c \
		./shell_subsys/terminal.c \
		./lexer/lexer.c \
		./lexer/lexer_get_tokens.c \
		./lexer/lexer_handle_tokens.c \
		./lexer/lexer_utils.c \
		./lexer/lexer_handle_token_name.c \
		./parser/parser.c \
		./parser/parser_utils.c \
		./parser/parser_utils2.c \
		./parser/parser_add_list_node.c \
		./parser/parser_check_token.c \
		./parser/parser_check_redirect.c \
		./parser/parser_check_redirect_dless.c \
		./parser/parser_add_new_empty_node.c \
		./parser/parser_free_list.c \
		./parser/parser_put_error_str.c \
		./pipex_repo/src/cmd_fuctions.c \
		./pipex_repo/src/pipe_list.c \
		./pipex_repo/src/pipex_utils.c \
		./pipex_repo/src/redirection_files.c \
		./pipex_repo/src/redirection_files_helper.c \
		./pipex_repo/src/pipex.c \
		./pipex_repo/src/fork.c \
		./pipex_repo/src/pipex_builtin_integration.c \
		./pipex_repo/src/close_fds.c \
		./pipex_repo/src/fork_utils.c
CINCLUDES += -I pipex_repo/include/ -I shell_subsys/ -I lexer/ -I parser/ -I .
SRC_BONUS =
DEPS_BONUS =
CINCLUDES += -I/usr/local/opt/readline/include/
READLINE_LIB = /usr/local/opt/readline/lib/
LFLAGS = -L$(READLINE_LIB) -lreadline
LIBFT_DIR = libft/
LIBFT_DEPS = libft.h
LIBFT =  $(LIBFT_DIR)libft.a
LIBFT_FLAGS = -L$(LIBFT_DIR) -lft
all: $(NAME)
$(NAME): $(SRC) | $(LIBFT) 
	@echo $(GREEN)
	$(CC) $(CFLAGS) $(CINCLUDES) $(SRC) -o $(NAME) $(LIBFT_FLAGS) $(LFLAGS)
	@echo $(NOCOLOR)
$(LIBFT):
	@echo $(BLUE)
	@make -C $(LIBFT_DIR)
bonus:
# %.o: %.c $(LFLAGS) $(DEPS) $(DEPS_BONUS) $(LIBFT_DEPS) $(READLINE_DEPS) $(LFLAGS)
#   $(CC) -c $(LFLAGS) $(CFLAGS)
reval:
	make re -C . D=0
	make val 
val: $(NAME)
	valgrind --leak-check=full \
	--gen-suppressions=all \
	--show-leak-kinds=all \
	--track-origins=yes \
	--show-reachable=no \
	--track-fds=yes \
	--suppressions=readline.supp \
	-s ./minishell
val2: $(NAME)
	valgrind --leak-check=full \
	--gen-suppressions=all \
	--show-leak-kinds=all \
	--track-origins=yes \
	--show-reachable=no \
	--track-fds=yes \
	--suppressions=readline_original.supp \
	-s ./minishell
gen_supp:
	valgrind --leak-check=full \
	--gen-suppressions=all \
	--show-leak-kinds=all \
	--error-limit=no \
	--log-file=minishell.log \
	./minishell
	cat minishell.log | awk 'BEGIN{ RS="}"; FS="{" } NF>1 {print "{" $$NF "}\n" }' > readline.supp
bash:
	valgrind --leak-check=full \
	--gen-suppressions=all \
	--show-leak-kinds=all \
	--track-origins=yes \
	--show-reachable=no \
	--track-fds=yes \
	--suppressions=readline.supp \
	-s bash
releaks:
	make re -C . D=0
	make leaks
leaks: $(NAME)
	leaks --atExit -- ./minishell
resan:
	make re -C . D=1
	make san
san:
	./minishell
clean:
	rm -f $(OBJ)
	rm -f $(OBJ_BONUS)
	rm -f lexer/TESTER_LEXER
	make clean -C ${LIBFT_DIR}
fclean: clean
	/bin/rm -f $(NAME)
	make fclean -C ${LIBFT_DIR}
readline:
ifeq ($(wildcard /usr/local/opt/readline), /usr/local/opt/readline)
	@echo $(YELLOW) "READLINE Found" $(NOCOLOR)
	@echo /usr/local/opt/readline
else
ifeq ($(shell uname), Linux)
	@echo $(GREEN) LINUX Found
	sudo apt-get install libreadline-dev
endif
ifeq ($(shell uname), Darwin)
	@echo $(GREEN) DARWIN Found
ifeq ($(wildcard $(HOME)/.brew/opt/readline), $(HOME)/.brew/opt/readline)
	@echo $(YELLOW) "BREW READLINE Found"
else
ifeq ($(wildcard $(HOME)/.brew/), $(HOME)/.brew/)
	@echo $(YELLOW) "Installig Readline ..."
else
	@echo  $(YELLOW) "Installing Brew && Readline"
	git clone --depth=1 https://github.com/Homebrew/brew $(HOME)/.brew
	echo 'export PATH=$(HOME)/.brew/bin:$(PATH)' >> $(HOME)/.zshrc && source $(HOME)/.zshrc
	echo 'export PATH=$(HOME)/.brew/bin:$(PATH)' >> $(HOME)/.bashrc && source $(HOME)/.bashrc
	echo 'export PATH=$(HOME)/.brew/bin:$(PATH)' >> $(HOME)/.bash_profile && source $(HOME)/.bash_profile
endif
	brew update
	brew install readline
	@echo $(NOCOLOR)
#CINCLUDES -= -I/usr/local/opt/readline/include/
CINCLUDES += -I$(HOME)/.brew/opt/readline/include/
#LFLAGS -= -L$(READLINE_LIB) -lreadline
READLINE_LIB = $(HOME)/.brew/opt/readline/lib/
LFLAGS += -L$(READLINE_LIB) -lreadline
endif
endif
endif
ls:
	@ls -CFGAF
linux_install:
	sudo apt-get install libreadline-dev
linux_remove:
	sudo apt-get remove libreadline-dev
	sudo apt autoremove
linux_check:
	apt list --installed | cat | grep readline
find_readline:
	find / -type d -name "*readline*" -print 2>/dev/null
re: fclean all
CROSS = "\033[8m"giut
RED = "\033[0;1;91m"
GREEN = "\033[0;1;32m"
BLUE = "\033[0;1;34m"
YELLOW = "\033[0;1;33m"
NOCOLOR	= "\033[m"
.PHONY: all clean fclean re