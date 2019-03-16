/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 12:44:08 by midrissi          #+#    #+#             */
/*   Updated: 2019/03/16 13:42:26 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static inline double	interpolate(double start, double end, double interpolat)
{
	return (start + ((end - start) * interpolat));
}

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

int						handle_mouse(int button, int x, int y, t_fractol *fract)
{
	if (x < 0 || x > WIN_W || y < 0 || y > WIN_H)
		return (1);
	if (button == SCROLLUP)
	{
		fract->zoom *= ZOOMFACTOR;
		zoom(fract, x, y, ZOOMFACTOR);
	}
	if (button == SCROLLDOWN)
	{
		fract->zoom /= ZOOMFACTOR;
		zoom(fract, x, y, 1.0 / ZOOMFACTOR);
	}
	process(fract);
	return (1);
}

int						handle_key(int keycode, t_fractol *fract)
{
	keycode == ESCAPE ? exit(0) : 0;
	(keycode == RIGHTARROW) && (fract->xoffset += 0.1 / fract->zoom);
	(keycode == LEFTARROW) && (fract->xoffset -= 0.1 / fract->zoom);
	(keycode == UPARROW) && (fract->yoffset -= 0.1 / fract->zoom);
	(keycode == DOWNARROW) && (fract->yoffset += 0.1 / fract->zoom);
	(keycode == DKEY) && (fract->shapecte2 += 0.01 / fract->zoom);
	(keycode == AKEY) && (fract->shapecte2 -= 0.01 / fract->zoom);
	(keycode == WKEY) && (fract->shapecte1 += 0.01 / fract->zoom);
	(keycode == SKEY) && (fract->shapecte1 -= 0.01 / fract->zoom);
	(keycode == 18) && (fract->m_it *= 2);
	(keycode == 19) && (fract->m_it > 2) && (fract->m_it /= 2);
	keycode == RKEY ? default_values(fract) : 0;
	if (keycode == QKEY)
		fract->smooth = fract->smooth ? 0 : 1;
	process(fract);
	return (1);
}
