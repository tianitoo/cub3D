SRCS = ft_putstr_fd.c \
ft_calloc.c ft_isalnum.c ft_isalpha.c \
ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c \
ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c \
ft_memset.c ft_split.c ft_strchr.c ft_strdup.c \
ft_strjoin.c ft_strlcat.c ft_strlcpy.c \
ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c \
ft_strtrim.c ft_tolower.c ft_toupper.c  ft_bzero.c \
ft_atoi.c ft_strlen.c ft_substr.c ft_putchar_fd.c ft_putendl_fd.c \
ft_putnbr_fd.c ft_striteri.c 
SRCS_BONUS = ft_lstnew.c ft_lstadd_front.c\
ft_lstsize.c ft_lstadd_back.c ft_lstlast.c
NAME = libft.a
OBJS = $(SRCS:.c=.o)
OBJS_BONUS = $(SRCS_BONUS:.c=.o) 

all: $(NAME)

$(NAME) : $(OBJS)
	ar rc $(NAME) $(OBJS)

%.o: %.c libft.h
	cc -Wall -Wextra -Werror -c $<

clean : clean_BONUS
	rm -rf $(OBJS)

bonus : $(OBJS_BONUS) 
	@ar rc $(NAME) $(OBJS_BONUS)

clean_BONUS : 
	rm -rf $(OBJS_BONUS)

fclean : clean
	rm -rf $(NAME)

re : fclean fclean_BONUS all bonus

.PHONY :  clean fclean bonus clean_BONUS fclean_BONUS re all
