NAME = pipex

CC = gcc

CFLAGS = -Werror -Wall -Wextra

RM = rm -rf

SRCS = 	srcs/pipex.c\
		srcs/parsing.c\
		srcs/error.c\
		srcs/settings.c\
		srcs/handler.c\
		libft/libft.a\
	

OBJS	= ${SRCS:.c=.o}
LIBFT	= make all -C libft/


%.o: %.c  include/pipex.h
	@${CC} ${CFLAGS} -Iinclude -Ilibft/ -c $< -o $@
	
${NAME}: ${OBJS}
	${CC} ${CFLAGS} -Iinclude -Ilibft/ -o $@ $^ -Llibft/

all : libft $(NAME)

fclean : clean
	$(RM) $(NAME)
	@make -s fclean -C libft/

clean :
	$(RM) $(OBJS)
	
re : fclean all

libft:
	@make -s all -C libft/

.PHONY: all clean fclean re libft