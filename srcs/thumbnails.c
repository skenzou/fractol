/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thumbnails.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 17:58:37 by midrissi          #+#    #+#             */
/*   Updated: 2019/03/18 20:03:35 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void   julia_thumbnail(t_fractol *f)
{
  register t_var			var;

  var.y = -1;
  while (++var.y < 300 && (var.x =  -1))
    while (++var.x < 500 && (var.i = -1))
    {
      var.newr = (double)var.x / (500 / (f->rmax - f->rmin))
                    + f->rmin + 0.755;
      var.newi = (double)var.y / (300 / (f->imax - f->imin))
                        + f->imin;
      while (var.newr * var.newr + var.newi * var.newi < 16.0
                            && ++var.i < f->m_it)
      {
        var.oldr = var.newr;
        var.newr = var.oldr * var.oldr - var.newi * var.newi +
                              f->shapecte1;
        var.newi = 2.0 * var.oldr * var.newi + f->shapecte2;
      }
      mlx_pixel_put(f->mlx_ptr, f->win_ptr, var.x, var.y, get_color(var.i, f));
    }
}

void					burningship_thumbnails(t_fractol *f)
{
	register t_var			var;

	var.y = -1;
	while (++var.y < 300 && (var.x = -1))
		while (++var.x < 500 && (var.i = -1))
		{
			var.pr = (double)var.x / (500 / (f->rmax - f->rmin))
											+ f->rmin + 0.4;
			var.pi = (double)var.y / (300 / (f->imax - f->imin))
											+ f->imin - 0.47;
			var.newr = var.pr;
			var.newi = var.pi;
			while (var.newr * var.newr + var.newi * var.newi < 16.0
														&& ++var.i < f->m_it)
			{
				var.tempr = var.newr * var.newr - var.newi * var.newi + var.pr;
				var.newi = abs_double(2.0 * var.newr * var.newi) + var.pi;
				var.newr = abs_double(var.tempr);
			}
			mlx_pixel_put(f->mlx_ptr, f->win_ptr, var.x, var.y + 909,
                                                          get_color(var.i, f));
		}
}

void					tricorn_thumbnail(t_fractol *f)
{
	register t_var			var;

	var.y = -1;
	while (++var.y < 300 && (var.x = -1))
		while (++var.x < 500 && (var.i = -1))
		{
			var.pr = (double)var.x / (500 / (f->rmax - f->rmin))
											+ f->rmin + 0.4;
			var.pi = (double)var.y / (300 * 0.8 / (f->imax - f->imin))
											+ f->imin - 0.23;
			var.newr = var.pr;
			var.newi = var.pi;
			while (var.newr * var.newr + var.newi * var.newi < 16.0
														&& ++var.i < f->m_it)
			{
				var.tempr = var.newr * var.newr - var.newi * var.newi + var.pr;
				var.newi = -2.0 * var.newr * var.newi + var.pi;
				var.newr = var.tempr;
			}
			mlx_pixel_put(f->mlx_ptr, f->win_ptr, var.x, var.y + 303,
                                                          get_color(var.i, f));
		}
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

void					mandelbrot_thumbnails(t_fractol  *f)
{
	t_var					var;

	var.y =  -1;
	while (++var.y < 300 && (var.x = -1))
		while (++var.x < 500 && (var.i = -1))
		{
			var.pr = (double)var.x / (500 / (f->rmax - f->rmin))
											+ f->rmin + 0.3;
			var.pi = (double)var.y / (300 / (f->imax - f->imin))
												+ f->imin;
			var.newr = 0.0;
			var.newi = 0.0;
			mandelbrot_loop(&var, f->m_it);
			mlx_pixel_put(f->mlx_ptr, f->win_ptr, var.x, var.y + 606,
                                                          get_color(var.i, f));
		}
}
