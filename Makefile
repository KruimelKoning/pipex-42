NAME = pipex

RED = \033[0;31m
GREEN = \033[0;32m
RESET = \033[0m

CFLAGS = -Werror -Wall -Wextra -g

RM = rm -rf

SRC = 	pipex.c \
		pipex_utils.c \
		free_open.c \
		libft/libft.a

SRCB = 	pipex_bonus.c \
		pipex_utils.c \
		free_open.c \
		libft/libft.a

$(NAME) :
	@echo "$(RED)Building $(NAME)...$(RESET)"
	@make -C libft -s
	@cc $(CFLAGS) $(SRC) -o $(NAME)
	@echo "$(GREEN)$(NAME) built$(RESET)"

all : $(NAME)

bonus:
	@echo "$(RED)Building $(NAME) bonus...$(RESET)"
	@make -C libft -s
	@cc $(CFLAGS) $(SRCB) -o $(NAME)
	@echo "$(GREEN)$(NAME) bonus built$(RESET)"

fclean : clean
	@make fclean -C libft -s

clean :
	$(RM) $(NAME)
	@make clean -C libft -s

re : fclean all

.PHONY:				all clean fclean re
