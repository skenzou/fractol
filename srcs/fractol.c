/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/09 04:24:02 by midrissi          #+#    #+#             */
/*   Updated: 2019/03/15 19:39:05 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void   check_error(int argc, char **argv)
{
  if (argc != 2 || (ft_strcmp(argv[1], "Julia") && ft_strcmp(argv[1], "Turtle")
      && ft_strcmp(argv[1], "Mandelbrot")))
  {
    ft_putendl_fd(ANSI_BOLD ANSI_RED "usage: ./fractol <fractol_name>"
    ANSI_RESET, 2);
    ft_putendl_fd(ANSI_BOLD ANSI_CYAN "fractols:" ANSI_RESET, 2);
    ft_putendl_fd(ANSI_BOLD ANSI_BLUE "--> Mandelbrot" ANSI_RESET, 2);
    ft_putendl_fd(ANSI_BOLD ANSI_MAGENTA "--> Julia" ANSI_RESET, 2);
    ft_putendl_fd(ANSI_BOLD ANSI_YELLOW "--> Turtle" ANSI_RESET, 2);
    exit(1);
  }
}

static inline void			center(t_fractol *fract, int x, int y)
{
	double percent;

	percent = ft_percent(WIN_WIDTH / 2, x < WIN_WIDTH / 2 ? 0 : WIN_WIDTH, x);
	fract->xoffset += x < WIN_WIDTH / 2 ? (-1.5 * percent) / fract->zoom
					: (1.5 * percent) / fract->zoom;
	percent = ft_percent(WIN_HEIGHT / 2, y < WIN_HEIGHT / 2 ? 0
					: WIN_HEIGHT, y);
	fract->yoffset += y < WIN_HEIGHT / 2 ? -percent / fract->zoom
					: percent / fract->zoom;
}

int				handle_mouse(int button, int x, int y, t_fractol *fract)
{
	if (x < 0 || x > WIN_WIDTH || y < 0 || y > WIN_HEIGHT)
		return (1);
	button == 1 ? center(fract, x, y) : 0;
	fract->zoom = button == SCROLLUP ? fract->zoom += fract->zoom * 0.3
																: fract->zoom;
	fract->zoom = button == SCROLLDOWN ? fract->zoom -= fract->zoom * 0.3
																: fract->zoom;
	process(fract);
	return (1);
}

int				handle_key(int keycode, t_fractol *fract)
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

static inline int   get_col(int n, t_fractol *fract)
{
	register float t;
	int r;
	int g;
	int b;

	if (n == fract->m_it)
		return (0);
	else if (!fract->smooth)
		return (n * 0x453433);
	t = (float)n / (float)fract->m_it;
	r = (int)(9.0 * (1.0 - t) * t * t * t * 255.0);
	g = (int)(15.0 * (1.0 - t) * (1.0 - t) * t * t * 255.0);
	b = (int)(8.5 * (1.0 - t) * (1.0 - t) * (1.0 - t) * t * 255.0);
	return ((r << 16) | (g << 8) | b);
}

void      *julia_thread(void *data)
{
	register t_var var;
	register t_thread_data *d;

	d = (t_thread_data *)data;
	var.y = d->y - 1;
	while (++var.y < d->y_end && (var.x = d->x - 1))
		while(++var.x < d->x_end && (var.i = -1))
		{
			var.newr = 1.5 * (var.x - WIN_WIDTH / 2.0) /
								(0.5 * d->f->zoom * WIN_WIDTH) + d->f->xoffset;
			var.newi = (var.y - WIN_HEIGHT / 2.0) /
								(0.5 * d->f->zoom * WIN_HEIGHT) + d->f->yoffset;
			while (var.newr * var.newr + var.newi * var.newi < 4.0
														&& ++var.i < d->f->m_it)
			{
				var.oldr = var.newr;
				var.oldi = var.newi;
				var.newr = var.oldr * var.oldr - var.oldi * var.oldi +
															d->f->shapecte1;
				var.newi = 2 * var.oldr * var.oldi + d->f->shapecte2;
			}
			put_pixel_img(d->f, var.x, var.y, get_col(var.i, d->f));
		}
	return (0);
}

// void      *julia_thread(void *dat)
// {
//   register t_complex new;
//   register t_complex old;
//   register int i;
//   register int x;
//   register int y;
//   register t_thread_data *data;
//
//   data = (t_thread_data *)dat;
//   y = data->y - 1;
//   while (++y < data->y_end && (x = data->x - 1))
//     while(++x < data->x_end && (i = -1))
//     {
//       new.r = 1.5 * (x - WIN_WIDTH / 2.0) / (0.5 * data->fract->zoom * WIN_WIDTH) + data->fract->xoffset;
//       new.i = (y - WIN_HEIGHT / 2.0) / (0.5 * data->fract->zoom * WIN_HEIGHT) + data->fract->yoffset;
//       while (new.r * new.r + new.i * new.i < 4.0 && ++i < data->fract->max_iter)
//       {
//         old.r = new.r;
//         old.i = new.i;
//         new.r = old.r * old.r - old.i * old.i + data->fract->shapecte1;
//         new.i = 2 * old.r * old.i + data->fract->shapecte2;
//       }
// 	  put_pixel_img(data->fract, x, y, get_rgb_smooth(i, data->fract->max_iter));
// 		// if (i == data->fract->max_iter)
// 		// 	put_pixel_img(data->fract, x, y, 0x0);
// 		// else
// 		// 	put_pixel_img(data->fract, x, y, i * 0xFF3345);
//     }
//   return (0);
// }

// void      *mandelbrot_thread(void *dat)
// {
//   register t_thread_data *data;
//
//   data = (t_thread_data *)dat;
//   data->y = data->y_s - 1;
//   while (++data->y < data->y_end && (data->x = data->x_s - 1))
//     while(++data->x < data->x_end && (data->i = -1))
//     {
//       data->pr = 1.5 * (data->x - WIN_WIDTH / 2.0) / (0.5 * data->fract->zoom * WIN_WIDTH) + data->fract->xoffset;
//       data->pi = (data->y - WIN_HEIGHT / 2.0) / (0.5 * data->fract->zoom * WIN_HEIGHT) + data->fract->yoffset;
//       data->newr = 0.0;
//       data->newi = 0.0;
//       while (data->newr * data->newr + data->newi * data->newi < 2.0 && ++data->i < data->fract->max_iter)
//       {
//         data->oldr = data->newr;
//         data->tempr = data->oldr * data->oldr - data->newi * data->newi + data->pr;
//         data->tempi = 2.0 * data->oldr * data->newi + data->pi;
// 		if (data->tempr == data->newr && data->tempi == data->newi && (data->i = data->fract->max_iter))
// 			break;
// 		data->newr = data->tempr;
// 		data->newi = data->tempi;
//       }
// 	 put_pixel_img(data->fract, data->x, data->y, get_rgb_smooth(data->i, data->fract->max_iter));
//     }
//   return (0);
// }


void      *mandelbrot_thread(void *data)
{
	register t_var var;
	register t_thread_data *d;

	d = (t_thread_data *)data;
	var.y = d->y - 1;
	while (++var.y < d->y_end && (var.x = d->x - 1))
		while(++var.x < d->x_end && (var.i = -1))
		{
			var.pr = 1.5 * (var.x - WIN_WIDTH / 2.0) / (0.5 * d->f->zoom * WIN_WIDTH) + d->f->xoffset;
			var.pi = (var.y - WIN_HEIGHT / 2.0) / (0.5 * d->f->zoom * WIN_HEIGHT) + d->f->yoffset;
			var.newr = 0.0;
			var.newi = 0.0;
			while (var.newr * var.newr + var.newi * var.newi < 2.0 && ++var.i < d->f->m_it)
			{
				var.oldr = var.newr;
				var.tempr = var.oldr * var.oldr - var.newi * var.newi + var.pr;
				var.tempi = 2.0 * var.oldr * var.newi + var.pi;
				if (var.tempr == var.newr && var.tempi == var.newi && (var.i = d->f->m_it))
					break;
				var.newr = var.tempr;
				var.newi = var.tempi;
			}
			put_pixel_img(d->f, var.x, var.y, get_col(var.i, d->f));
		}
	return (0);
}

void	init_thread_data(t_fractol *fract)
{
	int i;
	int x_s;
	int x_end;

	i = 0;
	x_end = WIN_WIDTH / TNUM;
	x_s = 0;
	while (i < TNUM)
	{
		fract->tdata[i++] = (t_thread_data){.x = x_s, .y = 0, .y_end = WIN_HEIGHT,
			.x_end = x_end, .f = fract};
		x_s += (WIN_WIDTH / TNUM);
		x_end += (WIN_WIDTH / TNUM);
	}
}

 void 	launch_threads(t_fractol *fract)
 {
	//mandelbrot_thread(&(t_thread_data){.x = 0, .y = 0, .y_end = WIN_HEIGHT, .x_end = WIN_WIDTH, .fract = fract});
	pthread_attr_t attr;
	int i;

	i = 0;
	pthread_attr_init(&attr);
	while (i < TNUM)
	{
		pthread_create(&(fract->tids[i]), &attr, fract->thread, &fract->tdata[i]);
		i++;
	}
	i = 0;
	while (i < TNUM)
		pthread_join(fract->tids[i++], NULL);
}

void        default_values(t_fractol *fract)
{
  fract->shapecte1 = -0.7;
  fract->shapecte2 = 0.27015;
  fract->m_it = 125;
  fract->zoom = 1.0;
  fract->xoffset = 0.0;
  fract->yoffset = 0.0;
  fract->smooth = 1;
}

t_fractol   *init_fract(char *name)
{
	t_fractol *fract;

	if (!(fract = (t_fractol *)ft_memalloc(sizeof(t_fractol))))
		exit(1);
	if (!(fract->mlx_ptr = mlx_init()))
		exit(1);
	fract->win_ptr =
		mlx_new_window(fract->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "Fractol");
	if (!(fract->img = (t_image *)malloc(sizeof(t_image))))
		exit(1);
	fract->img->ptr = NULL;
	if (!fract->win_ptr)
		exit(1);
	if (!ft_strcmp(name, "Mandelbrot"))
	fract->thread = &mandelbrot_thread;
	if (!ft_strcmp(name, "Julia"))
	fract->thread = &julia_thread;
	mlx_key_hook(fract->win_ptr, &handle_key, fract);
	mlx_mouse_hook(fract->win_ptr, &handle_mouse, fract);
	default_values(fract);
	init_thread_data(fract);
	create_image(fract);
	return (fract);
}

int main(int argc, char **argv)
{
  t_fractol *fract;

  check_error(argc, argv);
  fract = init_fract(argv[1]);
  process(fract);
  mlx_loop(fract->mlx_ptr);
  return (0);
}
