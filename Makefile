RESET=\033[0m
BOLD=\033[1m
RED=\033[31m
GREEN=\033[32m
YELLOW=\033[33m
BLUE=\033[34m
MAGENTA=\033[35m
CYAN=\033[36m
WHITE=\033[37m

BG_RED=\033[41m
BG_GREEN=\033[42m
BG_YELLOW=\033[43m
BG_BLUE=\033[44m
BG_MAGENTA=\033[45m
BG_CYAN=\033[46m
BG_WHITE=\033[47m

CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

CLIENT_EXC = client
C_SRC = client.c utils/ft_atoi.c utils/ft_putstr.c utils/ft_strjoin.c utils/ft_bzero.c utils/ft_putnbr.c
C_OBJ = $(C_SRC:.c=.o)

CLIENT_EXC_BONUS = client_bonus
C_SRC_BONUS = client_bonus.c utils/ft_atoi.c utils/ft_putstr.c utils/ft_strjoin.c utils/ft_bzero.c utils/ft_putnbr.c
C_OBJ_BONUS = $(C_SRC_BONUS:.c=.o)

SERVER_EXC = server
S_SRC = server.c utils/ft_atoi.c utils/ft_putstr.c utils/ft_strjoin.c utils/ft_bzero.c utils/ft_putnbr.c
S_OBJ = $(S_SRC:.c=.o)

SERVER_EXC_BONUS = server_bonus
S_SRC_BONUS = server_bonus.c utils/ft_atoi.c utils/ft_putstr.c utils/ft_strjoin.c utils/ft_bzero.c utils/ft_putnbr.c
S_OBJ_BONUS = $(S_SRC_BONUS:.c=.o)

all : $(CLIENT_EXC) $(SERVER_EXC)
bonus : $(CLIENT_EXC_BONUS) $(SERVER_EXC_BONUS)

$(CLIENT_EXC) : $(C_OBJ) minitalk.h
	@echo "$(BG_YELLOW)compiling client executable...$(RESET)"
	@$(CC) $(CFLAGS) $(C_OBJ) -o $@
	@echo "$(GREEN)client executable ready to use $(RESET)"

$(CLIENT_EXC_BONUS) : $(C_OBJ_BONUS) minitalk.h
	@echo "$(BG_YELLOW)compiling client bonus executable...$(RESET)"
	@$(CC) $(CFLAGS) $(C_OBJ_BONUS) -o $@
	@echo "$(GREEN)client bonus executable ready to use $(RESET)"

$(SERVER_EXC) : $(S_OBJ) minitalk.h
	@echo "$(BG_YELLOW)compiling server executable...$(RESET)"
	@$(CC) $(CFLAGS) $(S_OBJ) -o $@
	@echo "$(GREEN)server executable ready to use $(RESET)"

$(SERVER_EXC_BONUS) : $(S_OBJ_BONUS) minitalk.h
	@echo "$(BG_YELLOW)compiling server bonus executable...$(RESET)"
	@$(CC) $(CFLAGS) $(S_OBJ_BONUS) -o $@
	@echo "$(GREEN)server bonus executable ready to use $(RESET)"


%_bonus.o : %_bonus.c minitalk.h
	@echo "$(CYAN)generating $@...$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "$(BG_GREEN)$@ generated successfully$(RESET)"

%.o : %.c minitalk.h
	@echo "$(CYAN)generating $@...$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "$(BG_GREEN)$@ generated successfully$(RESET)"

clean :
	@echo "$(BG_RED)deleting output files...$(RESET)"
	@$(RM) $(C_OBJ) $(S_OBJ) $(S_OBJ_BONUS) $(C_OBJ_BONUS)
	@echo "$(RED)output files deleted successfully$(RESET)"

fclean : clean
	@echo "$(BG_RED)deleting executables...$(RESET)"
	@$(RM) $(SERVER_EXC) $(CLIENT_EXC) $(SERVER_EXC_BONUS) $(CLIENT_EXC_BONUS)
	@echo "$(RED)executables deleted successfully$(RESET)"

re : fclean all

.PHONY: clean