/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 12:44:08 by midrissi          #+#    #+#             */
/*   Updated: 2019/03/23 19:24:33 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static inline void		zoom(t_fractol *f, int x, int y, double zoomfactor)
{
	double	rmouse;
	double	imouse;
	double	interpolation;

	interpolation = 1.0 / zoomfactor;
	rmouse = (double)x / (WIN_W / (f->rmax - f->rmin)) + f->rmin;
	imouse = (double)y / (WIN_H / (f->imax - f->imin)) + f->imin;
	f->rmin = interpolate(rmouse, f->rmin, interpolation);
	f->imin = interpolate(imouse, f->imin, interpolation);
	f->rmax = interpolate(rmouse, f->rmax, interpolation);
	f->imax = interpolate(imouse, f->imax, interpolation);
}

int						julia_mouse(int x, int y, t_fractol *fract)
{
	x -= 503;
	if (fract->thread == &julia_thread && x > 0 && x < WIN_W && y > 0
											&& y < WIN_H && !fract->lockjulia)
	{
		fract->shapecte1 = -2.5 + ((double)x / WIN_W) * 3.5;
		fract->shapecte2 = -1.0 + ((double)y / WIN_H) * 2.0;
		process(fract);
	}
	return (1);
}

static inline int		fetchcolor(t_fractol *fract, int x, int y)
{
	t_list		*list;
	t_point		point;

	list = fract->palette;
	fract->smooth = 0;
	while (list)
	{
		point = *(t_point *)list->content;
		if (point.x == x && point.y == y)
			return (point.color);
		list = list->next;
	}
	return (0);
}

int						handle_mouse(int b, int x, int y, t_fractol *f)
{
	if ((b == 5 || b == 4) && x > 503 && x < WIN_W + 503 && y > 0 && y < WIN_H)
	{
		zoom(f, x - 503, y, b == 5 ? ZOOMFACTOR : 1 / ZOOMFACTOR);
		f->zoom = b == 5 ? f->zoom * ZOOMFACTOR : f->zoom / ZOOMFACTOR;
	}
	if (b == 1)
	{
		if (x >= WIN_W + 550 && x < WIN_W + 580 && y > 650 && y < 950)
			f->color = fetchcolor(f, x, y);
		if (x > 0 && x < 500)
		{
			f->thread = y < 300 && y > 0 ? &julia_thread : f->thread;
			f->thread = y < 603 && y > 302 ? &tricorn_thread : f->thread;
			f->thread = y < 906 && y > 605 ? &mandelbrot_thread : f->thread;
			f->thread = y < 1209 && y > 908 ? &burningship_thread : f->thread;
			default_values(f);
		}
	}
	process(f);
	return (1);
}

int						handle_key(int keycode, t_fractol *fract)
{
	keycode == ESCAPE ? exit(0) : 0;
	(keycode == RIGHTARROW) && (fract->xoffset -= 0.1 / fract->zoom);
	(keycode == LEFTARROW) && (fract->xoffset += 0.1 / fract->zoom);
	(keycode == UPARROW) && (fract->yoffset += 0.1 / fract->zoom);
	(keycode == DOWNARROW) && (fract->yoffset -= 0.1 / fract->zoom);
	(keycode == WKEY || keycode == PLUS) && (fract->m_it < 150)
														&& (fract->m_it += 15);
	(keycode == SKEY || keycode == MINUS) && (fract->m_it > 30)
														&& (fract->m_it -= 15);
	if (keycode > 17 && keycode < 22)
	{
		(keycode == 18) && (fract->thread = &mandelbrot_thread);
		(keycode == 19) && (fract->thread = &julia_thread);
		(keycode == 20) && (fract->thread = &burningship_thread);
		(keycode == 21) && (fract->thread = &tricorn_thread);
		default_values(fract);
	}
	if (keycode == QKEY)
		fract->lockjulia = fract->lockjulia ? 0 : 1;
	keycode == RKEY ? default_values(fract) : 0;
	if (keycode == SPACE)
		fract->smooth = fract->smooth ? 0 : 1;
	process(fract);
	return (1);
}
