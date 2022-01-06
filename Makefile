NAME = pipex

SRCS	= 	pipex.c				srcs/ft_split.c		srcs/ft_strjoin.c		\
			srcs/ft_strlcpy.c	srcs/ft_strlen.c 	srcs/ft_strncmp.c 		\
			pipex_utils.c \

HEAD	=	includes/pipex.h

OBJC	=	$(SRCS:.c=.o)

CC		=	gcc

CFLAGS	=	-Wall -Wextra -Werror

RM		=	rm -rf


F_NONE		= \033[37m
F_BOLD		= \033[1m
F_RED		= \033[31m
F_ORANGE	= \033[38m
F_YELLOW	= \033[33m
F_GREEN		= \033[32m
F_CYAN		= \033[36m
F_BLUE		= \033[34m

%.o:%.c		$(HEAD)
			@$(CC) $(FLAGS) -c $< -o ${<:.c=.o}


all:		$(NAME)

$(NAME):	$(OBJC)
			$(CC) $(CFLAGS) -o $(NAME) $(OBJC)
			@echo "$(F_BLUE)Object files pipex in ready! $(F_NONE)"


clean:
			@$(RM) $(OBJC)

fclean:		clean
			@$(RM) $(NAME)

re:			fclean all

norm:
			norminette *.c includes/*.h

.PHONY:		all clean fclean re