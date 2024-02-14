ifneq ($(OS), Windows_NT)
	CREATE = mkdir -p $(1)
	REMOVE = rm -rf $(1)
	NAME = philo
else
	CREATE = mkdir -p $(1)
	REMOVE = rm -rf $(1)
	NAME = philo.exe
	CC = gcc
endif
INCLUDE = $(CURDIR)
SRC = 	util.c \
		timer.c \
		life.c \
		life-create.c \
		life-update.c \
		life-pop.c \
		philo.c \
		philo-action.c \
		main.c
OBJ = obj
SRCOBJ = $(SRC:%.c=${OBJ}/%.o)
FLAG = -Wall -Werror -Wextra -g
LIB = -pthread

all: $(NAME)
$(NAME): $(SRCOBJ)
	$(CC) $^ $(LIB) -o $(NAME)
${OBJ}/%.o : %.c
	@$(call CREATE,${OBJ})
	$(CC) -c $< -o $@ $(FLAG) -I$(INCLUDE)
clean:
	$(call REMOVE,${OBJ})
fclean: clean
	$(call REMOVE,${NAME})
re: fclean all
fucker:
	./$(NAME) 8 800 200 200 5
play:
	valgrind --leak-check=full -q ./$(NAME) 4 210 100 100 2
hell:
	valgrind --tool=helgrind ./$(NAME) 2 310 100 100 2