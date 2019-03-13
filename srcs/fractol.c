/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/09 04:24:02 by midrissi          #+#    #+#             */
/*   Updated: 2019/03/13 08:18:40 by midrissi         ###   ########.fr       */
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
// percent = ft_percent(WIN_WIDTH / 2, x < WIN_WIDTH / 2 ? 0 : WIN_WIDTH, x);
// fract->xoffset += x < WIN_WIDTH / 2 ? -1.5 * percent : 1.5 * percent;
// percent = ft_percent(WIN_HEIGHT / 2, y < WIN_HEIGHT / 2 ? 0 : WIN_HEIGHT, y);
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
	(keycode == 18) && (fract->max_iter *= 2);
	(keycode == 19) && (fract->max_iter > 2) && (fract->max_iter /= 2);
	keycode == RKEY ? default_values(fract) : 0;
	process(fract);
	return (1);
}

static inline int   get_rgb_smooth(int n, int iter_max)
{
  register float t;
  int r;
  int g;
  int b;

	// if (n % 4 == 0 && n < iter_max)
	// 	return (0xFF3345);
	// if (n % 3 == 0 && n < iter_max)
	// 	return (0xAAbbaa);
  t = (float)n / (float)iter_max;
  r = (int)(9.0 * (1.0 - t) * t * t * t * 255.0);
  g = (int)(15.0 * (1.0 - t) * (1.0 - t) * t * t * 255.0);
  b = (int)(8.5 * (1.0 - t) * (1.0 - t) * (1.0 - t) * t * 255.0);
  return ((r << 16) | (g << 8) | b);
}

void      *julia_thread(void *dat)
{
  register t_complex new;
  register t_complex old;
  register int i;
  register int x;
  register t_thread_data *data;

  data = (t_thread_data *)dat;
  data->y--;
  while (++data->y < data->y_end && (x = data->x - 1))
    while(++x < data->x_end && (i = -1))
    {
      new.r = 1.5 * ((double)x - WIN_WIDTH / 2.0) / (double)(0.5 * data->fract->zoom * WIN_WIDTH) + data->fract->xoffset;
      new.i = ((double)data->y - WIN_HEIGHT / 2.0) / (double)(0.5 * data->fract->zoom * WIN_HEIGHT) + data->fract->yoffset;
      while (new.r * new.r + new.i * new.i < 4.0 && ++i < data->fract->max_iter)
      {
        old.r = new.r;
        old.i = new.i;
        new.r = old.r * old.r - old.i * old.i + data->fract->shapecte1;
        new.i = 2 * old.r * old.i + data->fract->shapecte2;
        if((new.r * new.r + new.i * new.i) > 4.0)
              break;
      }
      put_pixel_img(data->fract,
      (t_point){.x = x, .y = data->y, .color = get_rgb_smooth(i, data->fract->max_iter)}, 1);
    }
  return (0);
}

static inline int        ft_opti(double x, double y)
{
    double x_square;
    double y_square;

    x_square = x * x;
    y_square = y * y;
    if (x_square + 2 * x + 1 + y_square <= 1 / 16)
        return (0);
    return (1);
}

void      *mandelbrot_thread(void *dat)
{
  register t_complex new;
  register t_complex old;
  register t_complex p;
  register t_complex temp;
  register int i;
  register int x;
  register t_thread_data *data;

  data = (t_thread_data *)dat;
  data->y--;
  while (++data->y < data->y_end && (x = data->x - 1))
    while(++x < data->x_end && (i = -1))
    {
      p.r = 1.5 * (x - WIN_WIDTH / 2.0) / (0.5 * data->fract->zoom * WIN_WIDTH) + data->fract->xoffset;
      p.i = (data->y - WIN_HEIGHT / 2.0) / (0.5 * data->fract->zoom * WIN_HEIGHT) + data->fract->yoffset;
      new.r = 0.0;
      new.i = 0.0;
	  if (!ft_opti(p.r, p.i))
	  	i = data->fract->max_iter - 1;
      while (new.r * new.r + new.i * new.i < 2.0 && ++i < data->fract->max_iter)
      {
        old.r = new.r;
        temp.r = old.r * old.r - new.i * new.i + p.r;
        temp.i = 2.0 * old.r * new.i + p.i;
		if (temp.r == new.r && temp.i == new.i && (i = data->fract->max_iter))
			break;
		new.r = temp.r;
		new.i = temp.i;
      }
	  	put_pixel_img(data->fract,
      	(t_point){.x = x, .y = data->y, .color = get_rgb_smooth(i, data->fract->max_iter)}, 1);
    }
  return (0);
}


// void   launch_threads(t_fractol *fract)
// {
//     // DUAL THREAD TEST
//
//     pthread_t tid1;
//     pthread_t tid2;
//
//     pthread_attr_t attr1;
//     pthread_attr_t attr2;
//
//     pthread_attr_init(&attr1);
//     pthread_attr_init(&attr2);
//
//     pthread_create(&tid1, &attr1, fract->thread,
//     &(t_thread_data){.x = 0, .y = 0, .y_end = WIN_HEIGHT, .x_end = WIN_WIDTH / 2, .fract = fract});
//     pthread_create(&tid2, &attr2, fract->thread,
//     &(t_thread_data){.x = WIN_WIDTH / 2, .y = 0, .y_end = WIN_HEIGHT, .x_end = WIN_WIDTH, .fract = fract});
//
//     pthread_join(tid1, NULL);
//     pthread_join(tid2, NULL);
//
//
//
// }

// void   launch_threads(t_fractol *fract)
// {
//     // QUAD THREAD TEST
//
//     pthread_t tid1;
//     pthread_t tid2;
//     pthread_t tid3;
//     pthread_t tid4;
//     pthread_attr_t attr1;
//     pthread_attr_t attr2;
//     pthread_attr_t attr3;
//     pthread_attr_t attr4;
//
//     pthread_attr_init(&attr1);
//     pthread_attr_init(&attr2);
//     pthread_attr_init(&attr3);
//     pthread_attr_init(&attr4);
//     pthread_create(&tid1, &attr1, fract->thread,
//     &(t_thread_data){.x = 0, .y = 0, .y_end = WIN_HEIGHT / 2, .x_end = WIN_WIDTH / 2, .fract = fract});
//     pthread_create(&tid2, &attr2, fract->thread,
//     &(t_thread_data){.x = WIN_WIDTH / 2, .y = 0, .y_end = WIN_HEIGHT / 2, .x_end = WIN_WIDTH, .fract = fract});
//     pthread_create(&tid3, &attr3, fract->thread,
//     &(t_thread_data){.x = 0, .y = WIN_HEIGHT / 2, .y_end = WIN_HEIGHT, .x_end = WIN_WIDTH / 2, .fract = fract});
//     pthread_create(&tid4, &attr4, fract->thread,
//     &(t_thread_data){.x = WIN_WIDTH / 2, .y = WIN_HEIGHT / 2, .y_end = WIN_HEIGHT, .x_end = WIN_WIDTH, .fract = fract});
//
//     pthread_join(tid1, NULL);
//     pthread_join(tid2, NULL);
//     pthread_join(tid3, NULL);
//     pthread_join(tid4, NULL);
//
//
// }

void	init_thread_data(t_fractol *fract, t_thread_data data[8])
{
	data[0] = (t_thread_data){.x = 0, .y = 0, .y_end = WIN_HEIGHT / 2,
		.x_end = WIN_WIDTH / 4, .fract = fract};
	data[1] = (t_thread_data){.x = WIN_WIDTH / 4, .y = 0,
		.y_end = WIN_HEIGHT / 2, .x_end = WIN_WIDTH / 2, .fract = fract};
	data[2] = (t_thread_data){.x = WIN_WIDTH / 2, .y = 0,
		.y_end = WIN_HEIGHT / 2, .x_end = (WIN_WIDTH * 3) / 4, .fract = fract};
	data[3] = (t_thread_data){.x = (WIN_WIDTH * 3) / 4, .y = 0,
		.y_end = WIN_HEIGHT / 2, .x_end = WIN_WIDTH, .fract = fract};
	data[4] = (t_thread_data){.x = 0, .y = WIN_HEIGHT / 2,
		.y_end = WIN_HEIGHT, .x_end = WIN_WIDTH / 4, .fract = fract};
	data[5] = (t_thread_data){.x = WIN_WIDTH / 4, .y = WIN_HEIGHT / 2,
		.y_end = WIN_HEIGHT, .x_end = WIN_WIDTH / 2, .fract = fract};
	data[6] = (t_thread_data){.x = WIN_WIDTH / 2, .y = WIN_HEIGHT / 2,
		.y_end = WIN_HEIGHT, .x_end = (WIN_WIDTH * 3) / 4, .fract = fract};
	data[7] = (t_thread_data){.x = (WIN_WIDTH * 3) / 4, .y = WIN_HEIGHT / 2,
		.y_end = WIN_HEIGHT, .x_end = WIN_WIDTH, .fract = fract};
}

 void 	launch_threads(t_fractol *fract)
 {
	//mandelbrot_thread(&(t_thread_data){.x = 0, .y = 0, .y_end = WIN_HEIGHT, .x_end = WIN_WIDTH, .fract = fract});
	pthread_t ids[8];
	t_thread_data data[8];
	pthread_attr_t attr;

	pthread_attr_init(&attr);
	init_thread_data(fract, data);
	pthread_create(&(ids[0]), &attr, fract->thread, &data[0]);
	pthread_create(&(ids[1]), &attr, fract->thread, &data[1]);
	pthread_create(&(ids[2]), &attr, fract->thread, &data[2]);
	pthread_create(&(ids[3]), &attr, fract->thread, &data[3]);
	pthread_create(&(ids[4]), &attr, fract->thread, &data[4]);
	pthread_create(&(ids[5]), &attr, fract->thread, &data[5]);
	pthread_create(&(ids[6]), &attr, fract->thread, &data[6]);
	pthread_create(&(ids[7]), &attr, fract->thread, &data[7]);
	pthread_join(ids[0], NULL);
	pthread_join(ids[1], NULL);
	pthread_join(ids[2], NULL);
	pthread_join(ids[3], NULL);
	pthread_join(ids[4], NULL);
	pthread_join(ids[5], NULL);
	pthread_join(ids[6], NULL);
	pthread_join(ids[7], NULL);
}
// void   launch_threads(t_fractol *fract)
// {
//    //mandelbrot_thread(&(t_thread_data){.x = 0, .y = 0, .y_end = WIN_HEIGHT, .x_end = WIN_WIDTH, .fract = fract});
//    pthread_t tid1;
//    pthread_t tid2;
//    pthread_t tid3;
//    pthread_t tid4;
//    pthread_t tid5;
//    pthread_t tid6;
//    pthread_t tid7;
//    pthread_t tid8;
//    pthread_attr_t attr1;
//    pthread_attr_t attr2;
//    pthread_attr_t attr3;
//    pthread_attr_t attr4;
//    pthread_attr_t attr5;
//    pthread_attr_t attr6;
//    pthread_attr_t attr7;
//    pthread_attr_t attr8;
//
//    pthread_attr_init(&attr1);
//    pthread_attr_init(&attr2);
//    pthread_attr_init(&attr3);
//    pthread_attr_init(&attr4);
//    pthread_attr_init(&attr5);
//    pthread_attr_init(&attr6);
//    pthread_attr_init(&attr7);
//    pthread_attr_init(&attr8);
//    pthread_create(&tid1, &attr1, fract->thread,
//    &(t_thread_data){.x = 0, .y = 0, .y_end = WIN_HEIGHT / 2, .x_end = WIN_WIDTH / 4, .fract = fract});
//    pthread_create(&tid2, &attr2, fract->thread,
//    &(t_thread_data){.x = WIN_WIDTH / 4, .y = 0, .y_end = WIN_HEIGHT / 2, .x_end = WIN_WIDTH / 2, .fract = fract});
//    pthread_create(&tid3, &attr3, fract->thread,
//    &(t_thread_data){.x = WIN_WIDTH / 2, .y = 0, .y_end = WIN_HEIGHT / 2, .x_end = (WIN_WIDTH * 3) / 4, .fract = fract});
//    pthread_create(&tid4, &attr4, fract->thread,
//    &(t_thread_data){.x = (WIN_WIDTH * 3) / 4, .y = 0, .y_end = WIN_HEIGHT / 2, .x_end = WIN_WIDTH, .fract = fract});
//    pthread_create(&tid5, &attr5, fract->thread,
//    &(t_thread_data){.x = 0, .y = WIN_HEIGHT / 2, .y_end = WIN_HEIGHT, .x_end = WIN_WIDTH / 4, .fract = fract});
//    pthread_create(&tid6, &attr6, fract->thread,
//    &(t_thread_data){.x = WIN_WIDTH / 4, .y = WIN_HEIGHT / 2, .y_end = WIN_HEIGHT, .x_end = WIN_WIDTH / 2, .fract = fract});
//    pthread_create(&tid7, &attr7, fract->thread,
//    &(t_thread_data){.x = WIN_WIDTH / 2, .y = WIN_HEIGHT / 2, .y_end = WIN_HEIGHT, .x_end = (WIN_WIDTH * 3) / 4, .fract = fract});
//    pthread_create(&tid8, &attr8, fract->thread,
//    &(t_thread_data){.x = (WIN_WIDTH * 3) / 4, .y = WIN_HEIGHT / 2, .y_end = WIN_HEIGHT, .x_end = WIN_WIDTH, .fract = fract});
//
//    pthread_join(tid1, NULL);
//    pthread_join(tid2, NULL);
//    pthread_join(tid3, NULL);
//    pthread_join(tid4, NULL);
//    pthread_join(tid5, NULL);
//    pthread_join(tid6, NULL);
//    pthread_join(tid7, NULL);
//    pthread_join(tid8, NULL);
//
// }

void        default_values(t_fractol *fract)
{
  fract->shapecte1 = -0.7;
  fract->shapecte2 = 0.27015;
  fract->max_iter = 125;
  fract->zoom = 1.0;
  fract->xoffset = 0.0;
  fract->yoffset = 0.0;
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
