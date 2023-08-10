NAME := minishell
SRC_DIR := src
OBJ_DIR	:= obj

SRCS := main.c

SRCS := $(SRCS:%=$(SRC_DIR)/%)
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

CC := CC
CFLAGS := -g -Wall -Wextra -Werror $(DFLAGS)
CPPFLAGS := -I include
LDFLAGS := -lreadline

RM := rm -f
MAKEFLAGS += --no-print-directory
DIR_DUP = mkdir -p $(@D)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME) $(LDFLAGS)
	$(info CREATED $(NAME))

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(DIR_DUP)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<
	$(info CREATED $@)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean  all

.PHONY: clean fclean re
.SILENT:
