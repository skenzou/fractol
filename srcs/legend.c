/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   legend.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/17 14:02:35 by midrissi          #+#    #+#             */
/*   Updated: 2019/03/18 19:58:44 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void		put_border(t_fractol *fract)
{
	int i;

	i = 0;
	while (i < WIN_H)
	{
		mlx_pixel_put(fract->mlx_ptr, fract->win_ptr, WIN_W + 503, i, LIGHTRED);
		mlx_pixel_put(fract->mlx_ptr, fract->win_ptr, WIN_W + 504, i, LIGHTRED);
		mlx_pixel_put(fract->mlx_ptr, fract->win_ptr, WIN_W + 505, i, LIGHTRED);
		mlx_pixel_put(fract->mlx_ptr, fract->win_ptr, 500, i, LIGHTRED);
		mlx_pixel_put(fract->mlx_ptr, fract->win_ptr, 501, i, LIGHTRED);
		mlx_pixel_put(fract->mlx_ptr, fract->win_ptr, 502, i++, LIGHTRED);
	}
	i = 0;
	while (i < 500)
	{
		mlx_pixel_put(fract->mlx_ptr, fract->win_ptr, i, 300, LIGHTRED);
		mlx_pixel_put(fract->mlx_ptr, fract->win_ptr, i, 301, LIGHTRED);
		mlx_pixel_put(fract->mlx_ptr, fract->win_ptr, i, 302, LIGHTRED);
		mlx_pixel_put(fract->mlx_ptr, fract->win_ptr, i, 603, LIGHTRED);
		mlx_pixel_put(fract->mlx_ptr, fract->win_ptr, i, 604, LIGHTRED);
		mlx_pixel_put(fract->mlx_ptr, fract->win_ptr, i, 605, LIGHTRED);
		mlx_pixel_put(fract->mlx_ptr, fract->win_ptr, i, 906, LIGHTRED);
		mlx_pixel_put(fract->mlx_ptr, fract->win_ptr, i, 907, LIGHTRED);
		mlx_pixel_put(fract->mlx_ptr, fract->win_ptr, i++, 908, LIGHTRED);
	}
}

static void		put_legend_rest(t_fractol *fract)
{
	mlx_string_put(fract->mlx_ptr, fract->win_ptr, WIN_W + 513, 450, LIGHTRED,
	"down arrow            - move down");
	mlx_string_put(fract->mlx_ptr, fract->win_ptr, WIN_W + 513, 490, LIGHTRED,
	"W or +                - increase iterations");
	mlx_string_put(fract->mlx_ptr, fract->win_ptr, WIN_W + 513, 530, LIGHTRED,
	"S or -                - decrease iterations");
	mlx_string_put(fract->mlx_ptr, fract->win_ptr, WIN_W + 513, 570, LIGHTRED,
	"Q                     - lock/unlock Julia");
}

void			put_legend(t_fractol *fract)
{
	put_border(fract);
	mlx_string_put(fract->mlx_ptr, fract->win_ptr, WIN_W + 513, 10, LIGHTRED,
	"1                     - Mandelbrot set");
	mlx_string_put(fract->mlx_ptr, fract->win_ptr, WIN_W + 513, 50, LIGHTRED,
	"2                     - Julia set");
	mlx_string_put(fract->mlx_ptr, fract->win_ptr, WIN_W + 513, 90, LIGHTRED,
	"3                     - Burningship");
	mlx_string_put(fract->mlx_ptr, fract->win_ptr, WIN_W + 513, 130, LIGHTRED,
	"4                     - Tricorn");
	mlx_string_put(fract->mlx_ptr, fract->win_ptr, WIN_W + 513, 170, LIGHTRED,
	"scroll up             - zoom");
	mlx_string_put(fract->mlx_ptr, fract->win_ptr, WIN_W + 513, 210, LIGHTRED,
	"scroll down           - unzoom");
	mlx_string_put(fract->mlx_ptr, fract->win_ptr, WIN_W + 513, 250, LIGHTRED,
	"space                 - change colormode");
	mlx_string_put(fract->mlx_ptr, fract->win_ptr, WIN_W + 513, 290, LIGHTRED,
	"R                     - reset to default values");
	mlx_string_put(fract->mlx_ptr, fract->win_ptr, WIN_W + 513, 330, LIGHTRED,
	"left arrow            - move left");
	mlx_string_put(fract->mlx_ptr, fract->win_ptr, WIN_W + 513, 370, LIGHTRED,
	"right arrow           - move right");
	mlx_string_put(fract->mlx_ptr, fract->win_ptr, WIN_W + 513, 410, LIGHTRED,
	"up arrow              - move up");
	put_legend_rest(fract);
}
