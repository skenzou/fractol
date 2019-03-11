/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 03:50:36 by midrissi          #+#    #+#             */
/*   Updated: 2019/03/11 04:29:35 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

inline 	int				put_pixel_img(t_fractol *frac, t_point p, int border)
{
	int offset;
	int color;

	offset = ((p.x + p.y * WIN_WIDTH) * frac->img->bpp);
	color = mlx_get_color_value(frac->mlx_ptr, p.color);
	if (border || (p.x < WIN_WIDTH && p.x > 0 && p.y < WIN_HEIGHT && p.y > 0))
		*(int *)(frac->img->data + offset) = color;
	// 	*(int *)(frac->img->data + offset) = (color >> 16) & 0xFF;
	// 	*(int *)(frac->img->data + offset + 1) = (color >> 8) & 0xFF;
	// 	*(int *)(frac->img->data + offset + 2) = (color) & 0xFF;
	// }
	return (1);
}

// static inline 	int			put_pixel_test(t_image *img, t_point p, t_fractol *fract)
// {
// 	int offset;
// 	int color;
//
// 	offset = ((p.x + p.y * WIN_WIDTH / 4) * img->bpp);
// 	color = mlx_get_color_value(fract->mlx_ptr, p.color);
// 	if (p.x < WIN_WIDTH && p.x > 0 && p.y < WIN_HEIGHT && p.y > 0)
//     *(int *)(img->data + offset) = color;
//   // 	*(int *)(frac->img->data + offset) = (color >> 16) & 0xFF;
// 	// 	*(int *)(frac->img->data + offset + 1) = (color >> 8) & 0xFF;
// 	// 	*(int *)(frac->img->data + offset + 2) = (color) & 0xFF;
// 	// }
// 	return (1);
// }


static void		create_image(t_fractol *fract)
{
	fract->img->ptr = mlx_new_image(fract->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	if (!(fract->img->ptr))
		exit(1);
	fract->img->data = mlx_get_data_addr(fract->img->ptr,
			&fract->img->bpp, &fract->img->sizeline, &fract->img->endian);
	fract->img->bpp /= 8;
}

// t_image		*create_image_test(t_fractol *fract)
// {
// 	t_image *img;
//
// 	if (!(img = (t_image *)malloc(sizeof(t_image))))
// 		exit(1);
// 	img->ptr = mlx_new_image(fract->mlx_ptr, WIN_WIDTH / 4, WIN_HEIGHT / 2);
// 	if (!(img->ptr))
// 		exit(1);
// 	img->data = mlx_get_data_addr(img->ptr,
// 			&img->bpp, &img->sizeline, &img->endian);
// 	img->bpp /= 8;
// 	return (img);
// }

void			process(t_fractol *fract)
{
	mlx_clear_window(fract->mlx_ptr, fract->win_ptr);
	if (fract->img->ptr)
		mlx_destroy_image(fract->mlx_ptr, fract->img->ptr);
	create_image(fract);
	launch_threads(fract);
	mlx_put_image_to_window(fract->mlx_ptr, fract->win_ptr, fract->img->ptr, 0, 0);
}
