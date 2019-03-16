# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/03 09:24:41 by midrissi          #+#    #+#              #
#    Updated: 2019/03/16 13:42:19 by midrissi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


_END			=	\x1b[0m
_BOLD			=	\x1b[1m
_UNDER			=	\x1b[4m
_REV			=	\x1b[7m
_GREY			=	\x1b[30m
_RED			=	\x1b[31m
_GREEN			=	\x1b[32m
_YELLOW			=	\x1b[33m
_BLUE			=	\x1b[34m
_PURPLE			=	\x1b[35m
_CYAN			=	\x1b[36m
_WHITE			=	\x1b[37m
_IGREY			=	\x1b[40m
_IRED			=	\x1b[41m
_IGREEN			=	\x1b[42m
_IYELLOW		=	\x1b[43m
_IBLUE			=	\x1b[44m
_IPURPLE		=	\x1b[45m
_ICYAN			=	\x1b[46m
_IWHITE			=	\x1b[47m
_MAGENTA		=	\x1b[35m

MSG				=	Compiling fractol
.PHONY: all, $(NAME), clean, fclean, re

NAME = fractol

cc = gcc
C_FLAGS = -Wall -Wextra -Werror -pthread -Ofast

MLX_PATH = ./minilibx
MLX_LINK = -L $(MLX_PATH) -lmlx -framework OpenGL -framework AppKit
MLX_INC = -I $(MLX_PATH)

OBJ_PATH = ./obj/
LFT_PATH = ./libft/
INC_PATH = ./includes
SRC_PATH = ./srcs/

SRC_NAME = main.c image.c events.c fractals.c init.c
OBJ_NAME = $(SRC_NAME:.c=.o)
INC_NAME = fractol.h

SRC = $(addprefix $(SRC_PATH),$(SRC_NAME))
LONGEST			=	$(shell echo $(notdir $(SRC)) | tr " " "\n" | awk ' { if (\
				length > x ) { x = length; y = $$0 } }END{ print y }' | wc -c)
OBJ = $(addprefix $(OBJ_PATH),$(OBJ_NAME))
INC = $(addprefix -I,$(INC_PATH))

all: $(LIBFT_PATH)$(LIBFT_NAME) $(NAME)

$(LIBFT_PATH)$(LIBFT_NAME):
	@$(MAKE) -C $(LIBFT_PATH);

$(NAME): $(LIBFT_PATH)$(LIBFT_NAME) $(OBJ)
		@echo
		@make -C $(LFT_PATH)
		@make -C $(MLX_PATH)
		@$(CC) -o $(NAME) $(MLX_LINK) $(FRAM) -L $(LFT_PATH) -lft $^ -o $@
		@printf "$(_BOLD)$(_RED)./fractol is ready for use\n$(_END)$(_CYAN)$(_END)"
		@printf "$(_BOLD)$(_RED)\n\nusage: ./fractol <fractol_name>\n$(_RESET)"
		@printf "$(_BOLD)$(_CYAN)fractols:\n$(_RESET)"
		@printf "$(_BOLD)$(_BLUE)--> Mandelbrot\n$(_RESET)"
		@printf "$(_BOLD)$(_MAGENTA)--> Julia\n$(_RESET)"
		@printf "$(_BOLD)$(_YELLOW)--> Burningship\n$(_RESET)"


$(OBJ_PATH)%.o: $(SRC_PATH)%.c
		@mkdir -p $(OBJ_PATH) 2> /dev/null || true
		@$(CC) $(C_FLAGS) $(INC) $(MLX_INC) -o $@ -c $<
		@printf "$(_BOLD)$(_BLUE)$(MSG)$(_END) $(_BOLD)$(_CYAN)%-$(LONGEST)s\
		$(_END)" $(notdir $<)
		@if test -s srcs/$*.c; then \
		printf "$(_GREEN) [SUCCES]\n$(_END)";\
		else \
		printf "$(_RED) [ERROR]\n$(_END)"; fi


clean:
		@make -C $(LFT_PATH) clean
		@make -C $(MLX_PATH) clean
		@rm -rf $(OBJ_PATH)
		@echo "$(_BOLD)$(_RED)Sucessfuly removed all objects from fractol$(_END)"

fclean: clean
		@make -C $(MLX_PATH) clean
		@make -C $(LFT_PATH) fclean
		@rm -f $(NAME)
		@echo "$(_BOLD)$(_RED)Sucessfuly removed ${NAME} from fractol$(_END)"

re: fclean all
