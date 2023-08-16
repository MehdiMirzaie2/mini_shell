# NAME := minishell
# SRC_DIR := src
# OBJ_DIR	:= obj

# SRCS := main.c \
# 		utils/free_mem.c \
# 		command_tree/process.c \

# SRCS := $(SRCS:%=$(SRC_DIR)/%)
# OBJS := $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# CC := CC
# CFLAGS := -Llibft -lft
# # -Wall -Wextra -Werror
# OFLAGS := -g $(DFLAGS)
# CPPFLAGS := -I include libft
# LDFLAGS := -lreadline
# libft := libft/libft.a

# RM := rm -f
# MAKEFLAGS += --no-print-directory
# DIR_DUP = mkdir -p $(@D)

# all: $(NAME)

# $(libft):
# 				make -C libft

# $(NAME): $(OBJS) | $(libft)
# 	$(CC) $(OBJS) -o $(NAME) $(CFLAGS) $(LDFLAGS)
# 	$(info CREATED $(NAME))

# $(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
# 	$(DIR_DUP)
# 	$(CC) $(OFLAGS) $(CPPFLAGS) -c -o $@ $<
# 	$(info CREATED $@)

# clean:
# 	$(RM) $(OBJS)
# 	make -C libft clean

# fclean: clean
# 	$(RM) $(NAME)
# 	make -C libft fclean

# re: fclean  all

# .PHONY: clean fclean re
# .SILENT:





# @author   clemedon (Clément Vidon)
####################################### BEG_5 ####

NAME        := minishell

#------------------------------------------------#
#   INGREDIENTS                                  #
#------------------------------------------------#
# LIBS        libraries to be used
# LIBS_TARGET libraries to be built
#
# INCS        header file locations
#
# SRC_DIR     source directory
# SRCS        source files
#
# BUILD_DIR   build directory
# OBJS        object files
# DEPS        dependency files
#
# CC          compiler
# CFLAGS      compiler flags
# CPPFLAGS    preprocessor flags
# LDFLAGS     linker flags
# LDLIBS      libraries name

LIBS        := ft
LIBS_TARGET :=            \
	lib/libft.a

INCS        := include    \
	libft/include

SRC_DIR     := src
SRCS        := main.c \
				utils/free_mem.c \
				command_tree/process.c \

SRCS        := $(SRCS:%=$(SRC_DIR)/%)

BUILD_DIR   := .build
OBJS        := $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
DEPS        := $(OBJS:.o=.d)

CC          := clang
CFLAGS      := -Wall -Wextra -Werror -g
CPPFLAGS    := $(addprefix -I,$(INCS)) -MMD -MP
LDFLAGS     := $(addprefix -L,$(dir $(LIBS_TARGET)))
LDLIBS      := $(addprefix -l,$(LIBS))
RLFLAGS		:= -lreadline

#------------------------------------------------#
#   UTENSILS                                     #
#------------------------------------------------#
# RM        force remove
# MAKEFLAGS make flags
# DIR_DUP   duplicate directory tree

RM          := rm -f
MAKEFLAGS   += --silent --no-print-directory
DIR_DUP     = mkdir -p $(@D)

#------------------------------------------------#
#   RECIPES                                      #
#------------------------------------------------#
# all       default goal
# $(NAME)   link .o -> archive
# $(LIBS)   build libraries
# %.o       compilation .c -> .o
# clean     remove .o
# fclean    remove .o + binary
# re        remake default goal
# run       run the program
# info      print the default goal recipe

all: $(NAME)

$(NAME): $(OBJS) $(LIBS_TARGET)
	$(CC) $(LDFLAGS) $(OBJS) $(LDLIBS) -o $(NAME) $(RLFLAGS)
	$(info CREATED $(NAME))

$(LIBS_TARGET):
	$(MAKE) -C $(@D)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(DIR_DUP)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<
	$(info CREATED $@)

-include $(DEPS)

clean:
	for f in $(dir $(LIBS_TARGET)); do $(MAKE) -C $$f clean; done
	$(RM) $(OBJS) $(DEPS)

fclean: clean
	for f in $(dir $(LIBS_TARGET)); do $(MAKE) -C $$f fclean; done
	$(RM) $(NAME)

re:
	$(MAKE) fclean
	$(MAKE) all

info-%:
	$(MAKE) --dry-run --always-make $* | grep -v "info"

#------------------------------------------------#
#   SPEC                                         #
#------------------------------------------------#

.PHONY: clean fclean re
.SILENT:

####################################### END_5 ####
