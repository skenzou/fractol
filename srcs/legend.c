/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   legend.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/17 14:02:35 by midrissi          #+#    #+#             */
/*   Updated: 2019/03/23 19:26:03 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void				put_border(t_fractol *f)
{
	int i;
	int y;

	i = 0;
	while (i < WIN_H && (y = -1))
	{
		while (++y < 497)
			mlx_pixel_put(f->mlx_ptr, f->win_ptr, WIN_W + 503 + y, i, RED);
		mlx_pixel_put(f->mlx_ptr, f->win_ptr, 500, i, RED);
		mlx_pixel_put(f->mlx_ptr, f->win_ptr, 501, i, RED);
		mlx_pixel_put(f->mlx_ptr, f->win_ptr, 502, i++, RED);
	}
	i = 0;
	while (i < 500)
	{
		mlx_pixel_put(f->mlx_ptr, f->win_ptr, i, 300, RED);
		mlx_pixel_put(f->mlx_ptr, f->win_ptr, i, 301, RED);
		mlx_pixel_put(f->mlx_ptr, f->win_ptr, i, 302, RED);
		mlx_pixel_put(f->mlx_ptr, f->win_ptr, i, 603, RED);
		mlx_pixel_put(f->mlx_ptr, f->win_ptr, i, 604, RED);
		mlx_pixel_put(f->mlx_ptr, f->win_ptr, i, 605, RED);
		mlx_pixel_put(f->mlx_ptr, f->win_ptr, i, 906, RED);
		mlx_pixel_put(f->mlx_ptr, f->win_ptr, i, 907, RED);
		mlx_pixel_put(f->mlx_ptr, f->win_ptr, i++, 908, RED);
	}
}

static void				put_legend_rest(t_fractol *fract)
{
	mlx_string_put(fract->mlx_ptr, fract->win_ptr, WIN_W + 513, 450, WHITE,
	"down arrow            - move down");
	mlx_string_put(fract->mlx_ptr, fract->win_ptr, WIN_W + 513, 490, WHITE,
	"W or +                - increase iterations");
	mlx_string_put(fract->mlx_ptr, fract->win_ptr, WIN_W + 513, 530, WHITE,
	"S or -                - decrease iterations");
	mlx_string_put(fract->mlx_ptr, fract->win_ptr, WIN_W + 513, 570, WHITE,
	"Q                     - lock/unlock Julia");
}

static inline void		add_palette_pix(t_fractol *fract, int x, int y, int rgb)
{
	t_list *list;

	mlx_pixel_put(fract->mlx_ptr, fract->win_ptr, x, y, rgb);
	if (!(list = ft_lstnew((void*)&(t_point){.x = x, .y = y, .color = rgb},
															sizeof(t_point))))
		exit(1);
	ft_lstadd(&fract->palette, list);
}

static void				put_palette(t_fractol *fract)
{
	int		color[3];
	int		rgb;
	int		i;
	int		j;

	i = 0;
	color[0] = 255;
	color[1] = 0;
	color[2] = 0;
	while (i++ < 300 && (j = 549))
	{
		(color[1] == 0 && color[0] == 255) && (color[2] += 5);
		(color[1] == 255 && color[0] == 0) && (color[2] -= 5);
		(color[1] == 0 && color[2] == 255) && (color[0] -= 5);
		(color[1] == 255 && color[2] == 0) && (color[0] += 5);
		(color[0] == 0 && color[2] == 255) && (color[1] += 5);
		(color[0] == 255 && color[2] == 0) && (color[1] -= 5);
		rgb = (color[0] << 16) + (color[1] << 8) + color[2];
		while (++j < 580)
			add_palette_pix(fract, WIN_W + j, 650 + i, rgb);
	}
}

void					put_legend(t_fractol *fract)
{
	put_border(fract);
	mlx_string_put(fract->mlx_ptr, fract->win_ptr, WIN_W + 513, 10, WHITE,
	"1                     - Mandelbrot set");
	mlx_string_put(fract->mlx_ptr, fract->win_ptr, WIN_W + 513, 50, WHITE,
	"2                     - Julia set");
	mlx_string_put(fract->mlx_ptr, fract->win_ptr, WIN_W + 513, 90, WHITE,
	"3                     - Burningship");
	mlx_string_put(fract->mlx_ptr, fract->win_ptr, WIN_W + 513, 130, WHITE,
	"4                     - Tricorn");
	mlx_string_put(fract->mlx_ptr, fract->win_ptr, WIN_W + 513, 170, WHITE,
	"scroll up             - zoom");
	mlx_string_put(fract->mlx_ptr, fract->win_ptr, WIN_W + 513, 210, WHITE,
	"scroll down           - unzoom");
	mlx_string_put(fract->mlx_ptr, fract->win_ptr, WIN_W + 513, 250, WHITE,
	"space                 - change colormode");
	mlx_string_put(fract->mlx_ptr, fract->win_ptr, WIN_W + 513, 290, WHITE,
	"R                     - reset to default values");
	mlx_string_put(fract->mlx_ptr, fract->win_ptr, WIN_W + 513, 330, WHITE,
	"left arrow            - move left");
	mlx_string_put(fract->mlx_ptr, fract->win_ptr, WIN_W + 513, 370, WHITE,
	"right arrow           - move right");
	mlx_string_put(fract->mlx_ptr, fract->win_ptr, WIN_W + 513, 410, WHITE,
	"up arrow              - move up");
	put_legend_rest(fract);
	put_palette(fract);
}
