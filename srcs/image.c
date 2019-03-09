/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 03:50:36 by midrissi          #+#    #+#             */
/*   Updated: 2019/03/09 09:55:53 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

inline 	int				put_pixel_img(t_fractol *frac, t_point p, int border)
{
	int offset;
	int color;

	offset = ((p.x + p.y * WIN_WIDTH) * frac->img->bpp);
	color = mlx_get_color_value(frac->mlx_ptr, p.color);
	if (border || (p.x < DRAW_WIDTH && p.x > 0 && p.y < DRAW_HEIGHT && p.y > 0))
		*(int *)(frac->img->data + offset) = color;
	// 	*(int *)(frac->img->data + offset) = (color >> 16) & 0xFF;
	// 	*(int *)(frac->img->data + offset + 1) = (color >> 8) & 0xFF;
	// 	*(int *)(frac->img->data + offset + 2) = (color) & 0xFF;
	// }
	return (1);
}

static void		create_image(t_fractol *frac)
{
	frac->img->ptr = mlx_new_image(frac->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	if (!(frac->img->ptr))
		exit(1);
	frac->img->data = mlx_get_data_addr(frac->img->ptr,
			&frac->img->bpp, &frac->img->sizeline, &frac->img->endian);
	frac->img->bpp /= 8;
}

void			process(t_fractol *fract)
{
	mlx_clear_window(fract->mlx_ptr, fract->win_ptr);
	if (fract->img->ptr)
		mlx_destroy_image(fract->mlx_ptr, fract->img->ptr);
	create_image(fract);
	create_julia(fract);
	mlx_put_image_to_window(fract->mlx_ptr, fract->win_ptr, fract->img->ptr, 0, 0);
}
