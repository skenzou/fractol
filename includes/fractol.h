/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/09 04:10:21 by midrissi          #+#    #+#             */
/*   Updated: 2019/03/17 17:42:55 by midrissi         ###   ########.fr       */
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
# define TNUM			32
# define ZOOMFACTOR		1.11
# define WIN_W			1216
# define WIN_H			900
# define ESCAPE			53
# define UPARROW		126
# define DOWNARROW		125
# define RIGHTARROW		124
# define LEFTARROW		123
# define PLUS			69
# define MINUS			78
# define AKEY			0
# define SKEY			1
# define DKEY			2
# define QKEY			12
# define WKEY			13
# define SCROLLUP		5
# define SCROLLDOWN		4
# define SPACE			49
# define RKEY			15
# define PALETTERADIUS	100
# define ANSI_RED		"\x1b[1m\x1b[31m"
# define ANSI_GREEN		"\x1b[1m\x1b[32m"
# define ANSI_YELLOW	"\x1b[1m\x1b[33m"
# define ANSI_BLUE		"\x1b[1m\x1b[34m"
# define ANSI_MAGENTA	"\x1b[1m\x1b[35m"
# define ANSI_CYAN		"\x1b[1m\x1b[36m"
# define ANSI_RESET		"\x1b[1m\x1b[0m"
# define ANSI_BOLD		"\x1b[1m"
# define LIGHTRED		0xff0080

typedef struct		s_var
{
	double		tempi;
	double		tempr;
	double		newi;
	double		newr;
	double		oldi;
	double		oldr;
	double		pr;
	double		pi;
	int			x;
	int			y;
	int			i;
}					t_var;

typedef struct		s_image
{
	void		*ptr;
	char		*data;
	int			bpp;
	int			sizeline;
	int			endian;
}					t_image;

typedef struct		s_thread_data
{
	struct s_fractol	*f;
	double				tempi;
	double				tempr;
	double				oldi;
	double				oldr;
	double				newi;
	double				newr;
	double				pi;
	double				pr;
	int					i;
	int					x;
	int					y;
	int					y_s;
	int					y_end;
	int					x_s;
	int					x_end;
}					t_thread_data;

typedef struct		s_fractol
{
	void			*mlx_ptr;
	void			*win_ptr;
	char			smooth;
	t_image			*img;
	char			lockjulia;
	double			zoom;
	double			rmin;
	double			rmax;
	double			imax;
	double			imin;
	double			xoffset;
	double			yoffset;
	double			shapecte1;
	double			shapecte2;
	int				m_it;
	t_thread_data	tdata[TNUM];
	pthread_t		tids[TNUM];
	void			*(*thread)(void *data);
}					t_fractol;

void				create_image(t_fractol *fract);
void				process(t_fractol *frac);
void				put_pixel_img(t_fractol *frac, int x, int y, int color);
int					get_color(int n, t_fractol *fract);

void				*julia_thread(void *data);
void				*mandelbrot_thread(void *data);
void				*burningship_thread(void *data);
void				*tricorn_thread(void *data);

void				default_values(t_fractol *fract);
t_fractol			*init_fract(char *name);

void				put_legend(t_fractol *fract);

int					handle_mouse(int button, int x, int y, t_fractol *fract);
int					handle_key(int keycode, t_fractol *fract);
int					julia_mouse(int x, int y, t_fractol *fract);

#endif
