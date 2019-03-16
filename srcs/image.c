/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 03:50:36 by midrissi          #+#    #+#             */
/*   Updated: 2019/03/16 13:36:29 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

inline void		put_pixel_img(t_fractol *frac, int x, int y, int color)
{
	int offset;

	offset = ((x + y * WIN_W) * frac->img->bpp);
	if (x < WIN_W && x > 0 && y < WIN_H && y > 0)
	{
		frac->img->data[offset] = color & 0xFF;
		frac->img->data[offset + 1] = (color >> 8) & 0xFF;
		frac->img->data[offset + 2] = (color >> 16) & 0xFF;
	}
}

void			create_image(t_fractol *fract)
{
	fract->img->ptr = mlx_new_image(fract->mlx_ptr, WIN_W, WIN_H);
	if (!(fract->img->ptr))
		exit(1);
	fract->img->data = mlx_get_data_addr(fract->img->ptr,
			&fract->img->bpp, &fract->img->sizeline, &fract->img->endian);
	fract->img->bpp /= 8;
}

void			process(t_fractol *fract)
{
	launch_threads(fract);
	mlx_put_image_to_window(fract->mlx_ptr, fract->win_ptr, fract->img->ptr,
																		0, 0);
}
