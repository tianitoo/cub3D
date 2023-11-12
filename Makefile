NAME =  cub3D
HEADER =  cub3D.h
CFLAG = -Werror -Wall -Werror -Include 
FRAMEWOKR = -framework Cocoa -framework OpenGL -framework IOKit
MLX = MLX42/build/libmlx42.a -Iinclude -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/"
SRS = Cub3d.c get_next_line.c get_next_line_utils.c c_f_color.c order_path.c 
OBJS = $(SRS:.c=.o)

all : $(NAME)
	
%.o : %.c cub3D.h get_next_line.h
	cc -Werror -Wall -Werror -c $< -o $@
	
$(NAME) : $(OBJS)
	@cd libft && make
	 cc   $(CFLAG) $^ $(MLX) $(FRAMEWOKR) ./libft/libft.a -o $@ 

bonus : all

clean :
	@cd libft && make clean
	rm -f $(OBJS)

fclean : clean
	@cd libft && make fclean
	rm -f $(NAME)

re : fclean all

.phony : all bonus clean fclean re
