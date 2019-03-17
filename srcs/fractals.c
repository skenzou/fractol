/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 12:54:50 by midrissi          #+#    #+#             */
/*   Updated: 2019/03/17 15:16:19 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int						get_color(int n, t_fractol *fract)
{
	register float	t;
	register int	r;
	register int	g;
	register int	b;

	if (n == fract->m_it)
		return (0);
	else if (!fract->smooth)
		return (n * 0xFFbb45);
	t = (float)n / (float)fract->m_it;
	r = (int)(9.0 * (1.0 - t) * t * t * t * 255.0);
	g = (int)(15.0 * (1.0 - t) * (1.0 - t) * t * t * 255.0);
	b = (int)(8.5 * (1.0 - t) * (1.0 - t) * (1.0 - t) * t * 255.0);
	return ((r << 16) | (g << 8) | b);
}

void					*tricorn_thread(void *data)
{
	register t_var			var;
	register t_thread_data	*d;

	d = (t_thread_data *)data;
	var.y = d->y - 1;
	while (++var.y < d->y_end && (var.x = d->x - 1))
		while (++var.x < d->x_end && (var.i = -1))
		{
			var.pr = (double)var.x / (WIN_W / (d->f->rmax - d->f->rmin))
											+ d->f->rmin + 0.4 + d->f->xoffset;
			var.pi = (double)var.y / ((WIN_H) * 0.8 / (d->f->imax - d->f->imin))
											+ d->f->imin - 0.23 + d->f->yoffset;
			var.newr = var.pr;
			var.newi = var.pi;
			while (var.newr * var.newr + var.newi * var.newi < 16.0
														&& ++var.i < d->f->m_it)
			{
				var.tempr = var.newr * var.newr - var.newi * var.newi + var.pr;
				var.newi = -2.0 * var.newr * var.newi + var.pi;
				var.newr = var.tempr;
			}
			put_pixel_img(d->f, var.x, var.y, get_color(var.i, d->f));
		}
	return (0);
}

static inline void		mandelbrot_loop(t_var *var, int maxiter)
{
	while (var->newr * var->newr + var->newi * var->newi < 16.0
												&& ++var->i < maxiter)
	{
		var->oldr = var->newr;
		var->tempr = var->oldr * var->oldr - var->newi * var->newi + var->pr;
		var->tempi = 2.0 * var->oldr * var->newi + var->pi;
		if (var->tempr == var->newr && var->tempi == var->newi &&
												(var->i = maxiter))
			break ;
		var->newr = var->tempr;
		var->newi = var->tempi;
	}
}

void					*mandelbrot_thread(void *data)
{
	t_var					var;
	register t_thread_data	*d;

	d = (t_thread_data *)data;
	var.y = d->y - 1;
	while (++var.y < d->y_end && (var.x = d->x - 1))
		while (++var.x < d->x_end && (var.i = -1))
		{
			var.pr = (double)var.x / (WIN_W / (d->f->rmax - d->f->rmin))
											+ d->f->rmin + 0.3 + d->f->xoffset;
			var.pi = (double)var.y / (WIN_H / (d->f->imax - d->f->imin))
												+ d->f->imin + d->f->yoffset;
			var.newr = 0.0;
			var.newi = 0.0;
			mandelbrot_loop(&var, d->f->m_it);
			put_pixel_img(d->f, var.x, var.y, get_color(var.i, d->f));
		}
	return (0);
}

void					*julia_thread(void *data)
{
	register t_var			var;
	register t_thread_data	*d;

	d = (t_thread_data *)data;
	var.y = d->y - 1;
	while (++var.y < d->y_end && (var.x = d->x - 1))
		while (++var.x < d->x_end && (var.i = -1))
		{
			var.newr = (double)var.x / (WIN_W / (d->f->rmax - d->f->rmin))
										+ d->f->rmin + 0.755 + d->f->xoffset;
			var.newi = (double)var.y / (WIN_H / (d->f->imax - d->f->imin))
												+ d->f->imin + d->f->yoffset;
			while (var.newr * var.newr + var.newi * var.newi < 16.0
														&& ++var.i < d->f->m_it)
			{
				var.oldr = var.newr;
				var.oldi = var.newi;
				var.newr = var.oldr * var.oldr - var.oldi * var.oldi +
															d->f->shapecte1;
				var.newi = 2 * var.oldr * var.oldi + d->f->shapecte2;
			}
			put_pixel_img(d->f, var.x, var.y, get_color(var.i, d->f));
		}
	return (0);
}
