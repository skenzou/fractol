/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 13:17:27 by midrissi          #+#    #+#             */
/*   Updated: 2019/03/21 10:15:35 by midrissi         ###   ########.fr       */
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
	fract->m_it = 60;
	fract->zoom = 1;
	fract->xoffset = 0.0;
	fract->yoffset = 0.0;
	fract->smooth = 1;
	fract->lockjulia = 0;
	(fract->thread == &mandelbrot_thread) && (fract->rmin = -2.5);
	(fract->thread == &mandelbrot_thread) && (fract->rmax = 0.6);
	(fract->thread == &mandelbrot_thread) && (fract->imin = -1.2);
	(fract->thread == &mandelbrot_thread) && (fract->imax = 1.2);
	(fract->thread == &julia_thread || fract->thread == &tricorn_thread ||
		fract->thread == &burningship_thread) && (fract->rmin = -2.5);
	(fract->thread == &julia_thread || fract->thread == &tricorn_thread ||
		fract->thread == &burningship_thread) && (fract->rmax = 1.0);
	(fract->thread == &julia_thread || fract->thread == &tricorn_thread ||
		fract->thread == &burningship_thread) && (fract->imin = -1.0);
	(fract->thread == &julia_thread || fract->thread == &tricorn_thread ||
		fract->thread == &burningship_thread) && (fract->imax = 1.0);
}

t_fractol		*init_fract(char *name)
{
	t_fractol *f;

	if (!(f = (t_fractol *)ft_memalloc(sizeof(t_fractol))))
		exit(1);
	if (!(f->mlx_ptr = mlx_init()))
		exit(1);
	f->win_ptr = mlx_new_window(f->mlx_ptr, WIN_W + 1000, WIN_H, "Frac");
	if (!(f->img = (t_image *)malloc(sizeof(t_image))))
		exit(1);
	!f->win_ptr ? exit(1) : 0;
	if (!ft_strcmp(name, "Mandelbrot"))
		f->thread = &mandelbrot_thread;
	if (!ft_strcmp(name, "Julia"))
		f->thread = &julia_thread;
	if (!ft_strcmp(name, "Burningship"))
		f->thread = &burningship_thread;
	if (!ft_strcmp(name, "Tricorn"))
		f->thread = &tricorn_thread;
	mlx_key_hook(f->win_ptr, &handle_key, f);
	mlx_mouse_hook(f->win_ptr, &handle_mouse, f);
	mlx_hook(f->win_ptr, 6, 1L << 6, &julia_mouse, f);
	default_values(f);
	init_thread_data(f);
	create_image(f);
	return (f);
}
