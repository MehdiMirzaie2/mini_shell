NAME := minishell
SRC_DIR := src
OBJ_DIR	:= obj

SRCS := main.c util/ft_strdup_extra.c lexer.c

SRCS := $(SRCS:%=$(SRC_DIR)/%)
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

CC := cc
CFLAGS := -g -Wall -Wextra -Werror -lreadline -L.libft -lft $(DFLAGS)
CPPFLAGS := -I include -I .libft

RM := rm -f
MAKEFLAGS += --no-print-directory
DIR_DUP = mkdir -p $(@D)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) -o $(NAME)
	$(info CREATED $(NAME))

$(OBJS): $(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(DIR_DUP)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<
	$(info CREATED $@)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean  all

.PHONY: clean fclean re all
.SILENT:
