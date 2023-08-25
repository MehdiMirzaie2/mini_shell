
NAME        := minishell

LIBS        := ft
LIBS_TARGET := lib/libft.a
INCS        := include	\
			   lib/include

SRC_DIR     :=	src

SRCS        :=	main.c \
				error.c \
				utils/free_mem.c \
				utils/signal_handler.c \
				utils/create_env.c \
				util/strlst.c \
				util/iolst.c \
				util/ft_strdup_extra.c \
				parser/lexer.c \
				parser/ast.c \
				parser/cmd_builder.c \
				parser/ast_builder.c \
				parser/token.c

SRCS        := $(SRCS:%=$(SRC_DIR)/%)

BUILD_DIR   := .build
OBJS        := $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
DEPS        := $(OBJS:.o=.d)

CC          := cc
CFLAGS      := -Wall -Wextra -Werror
CPPFLAGS    := $(addprefix -I,$(INCS)) -MMD -MP
LDFLAGS     := $(addprefix -L,$(dir $(LIBS_TARGET)))
LDLIBS      := $(addprefix -l,$(LIBS))
RLFLAGS		:= -lreadline

RM          := rm -f
MAKEFLAGS   += --silent --no-print-directory
DIR_DUP     = mkdir -p $(@D)

all: $(NAME)

$(NAME): $(LIBS_TARGET) $(OBJS) 
	$(CC) $(LDFLAGS) $(OBJS) $(LDLIBS) -o $(NAME) $(RLFLAGS)
	$(call print_linking, $(NAME))

$(LIBS_TARGET):
	$(MAKE) -C $(@D)

$(OBJS): $(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(DIR_DUP)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<
	$(call print_obj,$@)

# cleans only the project.
clean:
	$(RM) $(OBJS) $(DEPS)
	$(call print_clean,$(addsuffix \n,$(OBJS)))

#  lib clean, clean all library objects.
lclean:
	for f in $(dir $(LIBS_TARGET)); do echo "${GREEN}Cleaning: ${CYAN} $$f ${NC} $$"; $(MAKE) -C $$f clean; done

# full clean, clean all objects and libraries and binaries
fclean: clean
	for f in $(dir $(LIBS_TARGET)); do $(MAKE) -C $$f fclean; done
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
