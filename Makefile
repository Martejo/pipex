NAME = pipex

CC = gcc

CFLAGS = -Werror -Wall -Wextra

RM = rm -rf

SRCS = 	pipex.c\
		utils.c\
		error.c\
		settings.c\
		libft/libft.a\

OBJS	= ${SRCS:.c=.o}


%.o: %.c  pipex.h
	${CC} ${CFLAGS} -I libft -c $< -o $@

${NAME}: ${OBJS}
	make all -C libft
	${CC} ${CFLAGS} -I libft -o $@ $^ libft/libft.a

all : $(NAME)

fclean : clean
	$(RM) $(NAME)
	make fclean -C libft

clean :
	$(RM) $(NAME) $(OBJS)
	

re : fclean all