
NAME        := minishell

LIBS        := ft
LIBFT_TARGET := lib/libft.a

INCS        = include	\
			   lib/include

OS := $(shell uname)
ARCH := $(shell uname -m)

ifeq ($(OS), Darwin) # MacOS specific commands
ifeq ($(ARCH), arm64)
RL_LIB += /opt/homebrew/opt/readline/lib
INCS += /opt/homebrew/opt/readline/include
else
RL_LIB += /usr/local/Cellar/readline/8.1.2/lib
INCS += /usr/local/Cellar/readline/8.1.2/include
endif
endif

SRC_DIR     :=	src

SRCS        :=	main.c \
				error.c \
				utils/free_mem.c \
				utils/signal_handler.c \
				utils/create_env.c \
				utils/arglst.c \
				utils/iolst.c \
				utils/ft_strdup_extra.c \
				utils/ft_space.c \
				utils/termios.c \
				utils/expand_utils.c \
				utils/expand_handle.c \
				utils/free.c \
				utils/env_to_array.c \
				utils/file_util.c \
				utils/get_home.c \
				utils/rl_util.c \
				parser/lexer.c \
				parser/lexer_utils.c \
				parser/debug_token.c \
				parser/ast.c \
				parser/debug_ast.c \
				parser/cmd_builder.c \
				parser/ast_builder.c \
				parser/expand.c \
				parser/rules.c \
				builtins/cd.c \
				builtins/env.c \
				builtins/export.c \
				builtins/echo.c \
				builtins/pwd.c \
				builtins/exit.c \
				execute/process_ast.c \
				execute/execute.c \
				execute/execute_builtin_cmds.c \
				execute/execute_system_cmds.c \
				execute/get_next_node.c \
				execute/utils.c \
				execute/execve_arg_create.c \
				execute/heredoc.c

SRCS        := $(SRCS:%=$(SRC_DIR)/%)

BUILD_DIR   := .build
OBJS        := $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
DEPS        := $(OBJS:.o=.d)

CC          := cc
CFLAGS      := -Wall -Wextra -Werror $(DFLAGS) 
CPPFLAGS    := $(addprefix -I,$(INCS)) -MMD -MP
LDFLAGS     := $(addprefix -L,$(dir $(LIBFT_TARGET))) $(addprefix -L,$(RL_LIB))
LDLIBS      := $(addprefix -l,$(LIBS))
RLFLAGS		:= -lreadline

RM          := rm -f
MAKEFLAGS   += --silent --no-print-directory
DIR_DUP     = mkdir -p $(@D)

all: $(NAME)

$(NAME): $(LIBFT_TARGET) $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) $(LDLIBS) -o $(NAME) $(RLFLAGS) $(DFLAGS)
	$(call print_linking, $(NAME))

$(LIBFT_TARGET):
	$(MAKE) -C $(@D)

$(OBJS): $(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(DIR_DUP)
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<
	@$(call print_obj,$@)

# cleans only the project.
clean:
	$(RM) $(OBJS) $(DEPS)
	$(call print_clean,$(addsuffix \n,$(OBJS)))

#  lib clean, clean all library objects.
lclean:
	for f in $(dir $(LIBFT_TARGET)); do echo "${GREEN}Cleaning: ${CYAN} $$f ${NC} $$"; $(MAKE) -C $$f clean; done

# full clean, clean all objects and libraries and binaries
fclean: clean
	for f in $(dir $(LIBFT_TARGET)); do $(MAKE) -C $$f fclean; done
	$(RM) $(NAME)
	$(call print_fclean,$(NAME))

re: fclean all

info-%:
	$(MAKE) --dry-run --always-make $* | grep -v "info"
-include $(DEPS)

define print_linking
	echo "${GREEN}Linking:${BLUE} $(or $1, $$1) ${NC}"
endef
define print_fclean
	echo "${BLUE}cleaned:${CYAN} $(or $1, $$1) ${NC}"
endef
define print_clean
	echo "${BLUE}cleaned:\n${YELLOW} $(or $1, $$1) ${NC}"
endef
define print_target
	echo "${GREEN}Compiling:${BLUE} $(or $1, $$1) ${NC}"
endef
define print_obj
	echo "${BLUE}created: ${YELLOW} $(or $1, $$1)${NC}"
endef
.PHONY: re fclean clean lclean all
.SILENT:

export DFLAGS
export print_linking
export print_fclean
export print_clean
export print_target
export print_obj

# COLORS
export GREEN = \033[1;32m
export YELLOW = \033[0;33m
export BLUE = \033[1;34m
export CYAN = \033[1;36m
export NC = \033[0m
