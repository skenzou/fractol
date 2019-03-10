/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/09 04:10:21 by midrissi          #+#    #+#             */
/*   Updated: 2019/03/10 01:56:21 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "../libft/includes/libft.h"
# include <stdio.h>
# include <mlx.h>
# include <math.h>
# include <fcntl.h>
# include <pthread.h>
# define WIN_WIDTH 1300
# define WIN_HEIGHT 700
# define DRAW_WIDTH 2000
# define DRAW_HEIGHT 1300
# define ESCAPE 53
# define UPARROW 126
# define DOWNARROW 125
# define RIGHTARROW 124
# define LEFTARROW 123
# define PLUS 69
# define MINUS 78
# define AKEY 0
# define SKEY 1
# define DKEY 2
# define QKEY 12
# define WKEY 13
# define SCROLLUP 5
# define SCROLLDOWN 4
# define SPACE 49
# define RKEY 15
# define PALETTERADIUS 100
# define ANSI_RED     "\x1b[31m"
# define ANSI_GREEN   "\x1b[32m"
# define ANSI_YELLOW  "\x1b[33m"
# define ANSI_BLUE    "\x1b[34m"
# define ANSI_MAGENTA "\x1b[35m"
# define ANSI_CYAN    "\x1b[36m"
# define ANSI_RESET   "\x1b[0m"
# define ANSI_BOLD		"\x1b[1m"

typedef struct		s_map
{
	int				**board;
	int				x;
	int				y;
}					t_map;

typedef struct s_complex
{
	float r;
	float i;
}						t_complex;

typedef struct		s_point
{
	int				x;
	int				y;
	int				color;
	int				border;
}					t_point;

typedef struct		s_image
{
	void		*ptr;
	char		*data;
	int			bpp;
	int			sizeline;
	int			endian;
}					t_image;

typedef struct		s_fractol
{
					void		*mlx_ptr;
					void		*win_ptr;
					t_image		*img;
					t_map		*map;
					int			altitude;
					float			zoom;
					float			xoffset;
					float			yoffset;
					float			shapecte1;
					float			shapecte2;
					int					max_iter;
					t_list		*colors;
					int			colorslist;
					int			spectrum[12];
					void		*(*thread)(void *dat);
}									t_fractol;

typedef struct s_thread_data
{
	t_fractol *fract;
	int y;
	int y_end;
	int x;
	int x_end;
}							t_thread_data;

void			process(t_fractol *frac);
int				put_pixel_img(t_fractol *frac, t_point p, int border);
int   create_julia(t_fractol *fract);
void        default_values(t_fractol *fract);
t_image		*create_image_test(t_fractol *fract);

#endif
