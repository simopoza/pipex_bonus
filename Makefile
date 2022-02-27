NAME= pipex
CC= gcc
SFLAGS= -Wall -Wextra -Werror
SRC= main.c pipex.c check_cmd.c  check_files.c pipex_utils.c split_path.c \
pipex_mand.c get_next_line_utils.c get_next_line.c ft_herdoc.c ft_proc.c
OBJ= $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(SFLAGS) $(SRC) -o $(NAME)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all