CC = gcc
FLAGS = -glldb -Wall -Werror -Wextra
SRCS = srcs/philosophers.c srcs/init.c srcs/simulation.c srcs/phil_utils.c
OBJS = $(SRCS:.c=.o)
B_SRCS = bonus/simulation_bonus.c bonus/init_bonus.c bonus/philosophers_bonus.c bonus/utils_bonus.c
B_OBJS = $(B_SRCS:.c=.o)
INCLUDE	= -lpthread
NAME = philo
BNAME = philo_bonus
Color_s = \033[92m
Color_e = \033[0m


all: banner name

name: $(OBJS)
	$(CC) $(INCLUDE) $(FLAGS) -o $(NAME) $(OBJS)

bonus: banner $(B_OBJS)
	$(CC) $(INCLUDE) $(FLAGS) -o $(BNAME) $(B_OBJS)

clean:
	rm -rf $(OBJS)
	rm -rf $(B_OBJS)

fclean: clean
	rm -rf $(NAME)
	rm -rf $(BNAME)

re: fclean all

norm:
	norminette srcs/*.c
	norminette bonus/*.c
	norminette include/*.h

banner:
	@echo "$(Color_s).------. .------. .------. .------. .------. .------. .------."
	@echo "|\x1B[31mC$(Color_s).--. | |\x1B[33mA$(Color_s).--. | |\x1B[34mN$(Color_s).--. | |\x1B[35mO$(Color_s).--. | |\x1B[36mD$(Color_s).--. | |\x1B[37mI$(Color_s).--. | |\x1b[31mS$(Color_s).--. |"
	@echo "| :/\: | | (\/) | | :(): | | :/\: | | :/\: | | (\/) | | :/\: |"
	@echo "| :\/: | | :\/: | | ()() | | :\/: | | (__) | | :\/: | | :\/: |"
	@echo "| '--'\x1B[31mC$(Color_s)| | '--'\x1B[33mA$(Color_s)| | '--'\x1B[34mN$(Color_s)| | '--'\x1B[35mO$(Color_s)| | '--'\x1B[36mD$(Color_s)| | '--'\x1B[37mI$(Color_s)| | '--'\x1b[31mS$(Color_s)|"
	@echo "\`------' \`------' \`------' \`------' \`------' \`------' \`------'\$(Color_e)"