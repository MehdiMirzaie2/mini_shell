# SOURCE FILES
SRCS = 	ft_strlen.c		\
		ft_isalpha.c 	\
		ft_isdigit.c	\
		ft_isalnum.c	\
		ft_isascii.c	\
		ft_isprint.c	\
		ft_toupper.c	\
		ft_tolower.c	\
		ft_atoi.c		\
		ft_bzero.c		\
		ft_memcpy.c		\
		ft_memset.c		\
		ft_memchr.c		\
		ft_memmove.c	\
		ft_memcmp.c		\
		ft_strchr.c		\
		ft_strrchr.c	\
		ft_strlcpy.c	\
		ft_strlcat.c	\
		ft_strncmp.c	\
		ft_strnstr.c	\
		ft_calloc.c		\
		ft_strdup.c		\
		$(SRCS2)		\

SRCS2 = ft_substr.c		\
		ft_strjoin.c	\
		ft_strtrim.c	\
		ft_split.c		\
		ft_itoa.c		\
		ft_strmapi.c	\
		ft_striteri.c	\
		ft_putchar_fd.c	\
		ft_putstr_fd.c	\
		ft_putendl_fd.c	\
		ft_putnbr_fd.c	\

# BONUS SOURCE FILES
SRCSB =	ft_lstnew.c			\
		ft_lstadd_front.c	\
		ft_lstadd_back.c	\
		ft_lstsize.c		\
		ft_lstlast.c		\
		ft_lstdelone.c		\
		ft_lstclear.c		\
		ft_lstiter.c		\
		ft_lstiter.c		\
		ft_lstmap.c			

# TARGET NAME AND VARIBLES
NAME = libft.a
OBJDIR = obj/
CC = clang
FLAGS = -Wall -Wextra -Werror -g

# OBJECT FILES
OBJ := $(patsubst %.c, $(OBJDIR)%.o, $(SRCS))
BONUS_OBJ := $(patsubst %.c, $(OBJDIR)%.o, $(SRCSB))

# ANY
all: $(NAME)

# CLEAN
re: fclean all

fclean: clean
	rm -f $(NAME)

clean:
	rm -rf $(OBJDIR)

# BUILD LIBRARY
$(NAME): $(OBJ)
	@ar rcs $(NAME) $(OBJ)
	@echo "ar rcs $(NAME) ..."
	@echo "Libft libary generated!"

# COMPILE
$(OBJDIR)%.o : %.c libft.h
	@mkdir -p $(OBJDIR)
	$(CC) $(FLAGS) -c $< -o $@

bonus: $(BONUS_OBJ)
	@ar r $(NAME) $(BONUS_OBJ)
	@echo "Libft bonus content generated!"
