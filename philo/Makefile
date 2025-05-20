NAME	=	philo
SRCS	=	main.c \
			helpers.c \
			parser.c \
			philosopher.c \
			philosopher_routine.c \
			philosopher_utils.c \
			threads.c \
			sleep.c
OBJS	:=	$(SRCS:.c=.o)

CFlags	= -Wall -Wextra -Werror -g -fsanitize=thread

vpath %.c src

%.o: %.c
	@$(CC) $(CFlags) -Iincl $< -c -o $@

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFlags) $^ -o $(NAME)

clean:
	@$(RM) $(OBJS)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

