/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/17 10:35:20 by midrissi          #+#    #+#             */
/*   Updated: 2019/03/18 18:29:55 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

double	abs_double(double nb)
{
	return (nb < 0 ? -nb : nb);
}

void					*burningship_thread(void *data)
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
			var.pi = (double)var.y / (WIN_H / (d->f->imax - d->f->imin))
											+ d->f->imin - 0.47 + d->f->yoffset;
			var.newr = var.pr;
			var.newi = var.pi;
			while (var.newr * var.newr + var.newi * var.newi < 16.0
														&& ++var.i < d->f->m_it)
			{
				var.tempr = var.newr * var.newr - var.newi * var.newi + var.pr;
				var.newi = abs_double(2.0 * var.newr * var.newi) + var.pi;
				var.newr = abs_double(var.tempr);
			}
			put_pixel_img(d->f, var.x, var.y, get_color(var.i, d->f));
		}
	return (0);
}
