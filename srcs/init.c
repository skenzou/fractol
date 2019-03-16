/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 13:17:27 by midrissi          #+#    #+#             */
/*   Updated: 2019/03/16 13:39:29 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void		init_thread_data(t_fractol *fract)
{
	int i;
	int x_s;
	int x_end;

	i = 0;
	x_end = WIN_W / TNUM;
	x_s = 0;
	while (i < TNUM)
	{
		fract->tdata[i++] = (t_thread_data){.x = x_s, .y = 0, .y_end = WIN_H,
			.x_end = x_end, .f = fract};
		x_s += (WIN_W / TNUM);
		x_end += (WIN_W / TNUM);
	}
}

void			default_values(t_fractol *fract)
{
	fract->shapecte1 = -0.7;
	fract->shapecte2 = 0.27015;
	fract->m_it = 125;
	fract->zoom = 1;
	fract->xoffset = 0.0;
	fract->yoffset = 0.0;
	fract->smooth = 1;
	(fract->thread == &mandelbrot_thread) && (fract->rmin = -2.5);
	(fract->thread == &mandelbrot_thread) && (fract->rmax = 0.6);
	(fract->thread == &mandelbrot_thread) && (fract->imin = -1.2);
	(fract->thread == &mandelbrot_thread) && (fract->imax = 1.2);
	(fract->thread == &julia_thread ||
		fract->thread == &burningship_thread) && (fract->rmin = -2.5);
	(fract->thread == &julia_thread ||
		fract->thread == &burningship_thread) && (fract->rmax = 1.0);
	(fract->thread == &julia_thread ||
		fract->thread == &burningship_thread) && (fract->imin = -1.0);
	(fract->thread == &julia_thread ||
		fract->thread == &burningship_thread) && (fract->imax = 1.0);
}

t_fractol		*init_fract(char *name)
{
	t_fractol *fract;

	if (!(fract = (t_fractol *)ft_memalloc(sizeof(t_fractol))))
		exit(1);
	if (!(fract->mlx_ptr = mlx_init()))
		exit(1);
	fract->win_ptr =
		mlx_new_window(fract->mlx_ptr, WIN_W, WIN_H, "Fractol");
	if (!(fract->img = (t_image *)malloc(sizeof(t_image))))
		exit(1);
	fract->img->ptr = NULL;
	if (!fract->win_ptr)
		exit(1);
	if (!ft_strcmp(name, "Mandelbrot"))
		fract->thread = &mandelbrot_thread;
	if (!ft_strcmp(name, "Julia"))
		fract->thread = &julia_thread;
	if (!ft_strcmp(name, "Burningship"))
		fract->thread = &burningship_thread;
	mlx_key_hook(fract->win_ptr, &handle_key, fract);
	mlx_mouse_hook(fract->win_ptr, &handle_mouse, fract);
	default_values(fract);
	init_thread_data(fract);
	create_image(fract);
	return (fract);
}
