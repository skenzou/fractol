/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   legend.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/17 14:02:35 by midrissi          #+#    #+#             */
/*   Updated: 2019/03/17 14:16:18 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void		put_border(t_fractol *fract)
{
	int i;

	i = 0;
	while (i < WIN_H)
	{
		mlx_pixel_put(fract->mlx_ptr, fract->win_ptr, WIN_W, i, LIGHTRED);
		mlx_pixel_put(fract->mlx_ptr, fract->win_ptr, WIN_W + 1, i, LIGHTRED);
		mlx_pixel_put(fract->mlx_ptr, fract->win_ptr, WIN_W + 2, i++, LIGHTRED);
	}
}

static void		put_legend_rest(t_fractol *fract)
{
	mlx_string_put(fract->mlx_ptr, fract->win_ptr, WIN_W + 10, 450, LIGHTRED,
	"down arrow            - move down");
	mlx_string_put(fract->mlx_ptr, fract->win_ptr, WIN_W + 10, 490, LIGHTRED,
	"W or +                - increase iterations");
	mlx_string_put(fract->mlx_ptr, fract->win_ptr, WIN_W + 10, 530, LIGHTRED,
	"S or -                - decrease iterations");
}

void			put_legend(t_fractol *fract)
{
	put_border(fract);
	mlx_string_put(fract->mlx_ptr, fract->win_ptr, WIN_W + 10, 10, LIGHTRED,
	"1                     - Mandelbrot set");
	mlx_string_put(fract->mlx_ptr, fract->win_ptr, WIN_W + 10, 50, LIGHTRED,
	"2                     - Julia set");
	mlx_string_put(fract->mlx_ptr, fract->win_ptr, WIN_W + 10, 90, LIGHTRED,
	"3                     - Burningship");
	mlx_string_put(fract->mlx_ptr, fract->win_ptr, WIN_W + 10, 130, LIGHTRED,
	"4                     - Tricorn");
	mlx_string_put(fract->mlx_ptr, fract->win_ptr, WIN_W + 10, 170, LIGHTRED,
	"scroll up             - zoom");
	mlx_string_put(fract->mlx_ptr, fract->win_ptr, WIN_W + 10, 210, LIGHTRED,
	"scroll down           - unzoom");
	mlx_string_put(fract->mlx_ptr, fract->win_ptr, WIN_W + 10, 250, LIGHTRED,
	"space                 - change colormode");
	mlx_string_put(fract->mlx_ptr, fract->win_ptr, WIN_W + 10, 290, LIGHTRED,
	"R                     - reset to default values");
	mlx_string_put(fract->mlx_ptr, fract->win_ptr, WIN_W + 10, 330, LIGHTRED,
	"left arrow            - move left");
	mlx_string_put(fract->mlx_ptr, fract->win_ptr, WIN_W + 10, 370, LIGHTRED,
	"right arrow           - move right");
	mlx_string_put(fract->mlx_ptr, fract->win_ptr, WIN_W + 10, 410, LIGHTRED,
	"up arrow              - move up");
	put_legend_rest(fract);
}
