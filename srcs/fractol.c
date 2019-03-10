/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/09 04:24:02 by midrissi          #+#    #+#             */
/*   Updated: 2019/03/10 02:49:24 by midrissi         ###   ########.fr       */
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

int				handle_mouse(int button, int x, int y, t_fractol *fract)
{
	if (x > 4 && x < DRAW_WIDTH && y > 4 && y < DRAW_HEIGHT)
	{
    if (fract->zoom < 100)
    {
		  fract->zoom = button == SCROLLUP ? fract->zoom + 5.0 : fract->zoom;
		  fract->zoom = button == SCROLLDOWN ? fract->zoom - 5.0 : fract->zoom;
    }
    else
    {
      fract->zoom = button == SCROLLUP ? fract->zoom += fract->zoom * 0.3 : fract->zoom;
		  fract->zoom = button == SCROLLDOWN ? fract->zoom -= fract->zoom * 0.3 : fract->zoom;
    }
	}
  process(fract);
  return (1);
}

int				handle_key(int keycode, t_fractol *fract)
{
	keycode == ESCAPE ? exit(0) : 0;
	(keycode == RIGHTARROW) && (fract->xoffset += 0.01 / fract->zoom);
	(keycode == LEFTARROW) && (fract->xoffset -= 0.01 / fract->zoom);
	(keycode == UPARROW) && (fract->yoffset -= 0.1 / fract->zoom);
	(keycode == DOWNARROW) && (fract->yoffset += 0.1 / fract->zoom);
  (keycode == DKEY) && (fract->shapecte2 += 0.01 / fract->zoom);
  (keycode == AKEY) && (fract->shapecte2 -= 0.01 / fract->zoom);
  (keycode == WKEY) && (fract->shapecte1 += 0.01 / fract->zoom);
  (keycode == SKEY) && (fract->shapecte1 -= 0.01 / fract->zoom);
  (keycode == 18) && (fract->max_iter *= 2);
  (keycode == 19) && (fract->max_iter > 2) && (fract->max_iter /= 2);
  if (keycode == RKEY)
    default_values(fract);
	process(fract);
	return (1);
}

static inline int   get_rgb_smooth(int n, int iter_max)
{
  register float t;
  int r;
  int g;
  int b;

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
  register int y;
  t_thread_data *data;
  data = (t_thread_data *)dat;
  t_fractol *fract = data->fract;

  y = data->y - 1;
  while (++y < data->y_end && (x = data->x - 1))
    while(++x < data->x_end && (i = -1))
    {
      new.r = 1.5 * (x - WIN_WIDTH / 2) / (0.5 * fract->zoom * WIN_WIDTH) + fract->xoffset;
      new.i = (y - WIN_HEIGHT / 2) / (0.5 * fract->zoom * WIN_HEIGHT) + fract->yoffset;
      while (++i < fract->max_iter)
      {
        old.r = new.r;
        old.i = new.i;
        new.r = old.r * old.r - old.i * old.i + fract->shapecte1;
        new.i = 2 * old.r * old.i + fract->shapecte2;
        if((new.r * new.r + new.i * new.i) > 4)
              break;
      }
      put_pixel_img(fract,
      (t_point){.x = x, .y = y, .color = get_rgb_smooth(i, fract->max_iter)}, 1);
    }
  return (0);
}

void      *mandelbrot_thread(void *dat)
{
  register t_complex new;
  register t_complex old;
  register t_complex p;
  register int i;
  register int x;
  register int y;
  t_thread_data *data;
  data = (t_thread_data *)dat;
  t_fractol *fract = data->fract;

  y = data->y - 1;
  while (++y < data->y_end && (x = data->x - 1))
    while(++x < data->x_end && (i = -1))
    {
      p.r = 1.5 * (x - WIN_WIDTH / 2) / (0.5 * fract->zoom * WIN_WIDTH) + fract->xoffset;
      p.i = (y - WIN_HEIGHT / 2) / (0.5 * fract->zoom * WIN_HEIGHT) + fract->yoffset;
      new.r = 0;
      new.i = 0;
      old.i = 0;
      old.r = 0;
      while (++i < fract->max_iter)
      {
        old.r = new.r;
        old.i = new.i;
        new.r = old.r * old.r - old.i * old.i + p.r;
        new.i = 2 * old.r * old.i + p.i;
        if((new.r * new.r + new.i * new.i) > 2)
              break;
      }
      put_pixel_img(fract,
      (t_point){.x = x, .y = y, .color = get_rgb_smooth(i, fract->max_iter)}, 1);
    }
  return (0);
}

// void  *mandelbrot_thread(void *dat)
// {
// screen(400, 300, 0, "Mandelbrot Set"); //make larger to see more detail!
//
//   //each iteration, it calculates: newz = oldz*oldz + p, where p is the current pixel, and oldz stars at the origin
//   double pr, pi;           //real and imaginary part of the pixel p
//   double newRe, newIm, oldRe, oldIm;   //real and imaginary parts of new and old z
//   ColorRGB color; //the RGB color value for the pixel
//   int maxIterations = 300;//after how much iterations the function should stop
//
//   //loop through every pixel
//   for(int y = 0; y < h; y++)
//   for(int x = 0; x < w; x++)
//   {
//     //calculate the initial real and imaginary part of z, based on the pixel location and zoom and position values
//     pr = 1.5 * (x - w / 2) / (0.5 * zoom * w) + moveX;
//     pi = (y - h / 2) / (0.5 * zoom * h) + moveY;
//     newRe = newIm = oldRe = oldIm = 0; //these should start at 0,0
//     //"i" will represent the number of iterations
//     int i;
//     //start the iteration process
//     for(i = 0; i < maxIterations; i++)
//     {
//       //remember value of previous iteration
//       oldRe = newRe;
//       oldIm = newIm;
//       //the actual iteration, the real and imaginary part are calculated
//       newRe = oldRe * oldRe - oldIm * oldIm + pr;
//       newIm = 2 * oldRe * oldIm + pi;
//       //if the point is outside the circle with radius 2: stop
//       if((newRe * newRe + newIm * newIm) > 4) break;
//     }
//     //use color model conversion to get rainbow palette, make brightness black if maxIterations reached
//     color = HSVtoRGB(ColorHSV(i % 256, 255, 255 * (i < maxIterations)));
//      //draw the pixel
//      pset(x, y, color);
//   }
//   //make the Mandelbrot Set visible and wait to exit
//   redraw();
//   sleep();
//   return 0;
// }

int   create_julia(t_fractol *fract)
{

    pthread_t tid1;
    pthread_t tid2;
    pthread_t tid3;
    pthread_t tid4;
    pthread_t tid5;
    pthread_t tid6;
    pthread_t tid7;
    pthread_t tid8;
    pthread_attr_t attr1;
    pthread_attr_t attr2;
    pthread_attr_t attr3;
    pthread_attr_t attr4;
    pthread_attr_t attr5;
    pthread_attr_t attr6;
    pthread_attr_t attr7;
    pthread_attr_t attr8;

    pthread_attr_init(&attr1);
    pthread_attr_init(&attr2);
    pthread_attr_init(&attr3);
    pthread_attr_init(&attr4);
    pthread_attr_init(&attr5);
    pthread_attr_init(&attr6);
    pthread_attr_init(&attr7);
    pthread_attr_init(&attr8);
    pthread_create(&tid1, &attr1, fract->thread,
    &(t_thread_data){.x = 0, .y = 0, .y_end = WIN_HEIGHT / 2, .x_end = WIN_WIDTH / 4, .fract = fract});
    pthread_create(&tid2, &attr2, fract->thread,
    &(t_thread_data){.x = WIN_WIDTH / 4, .y = 0, .y_end = WIN_HEIGHT / 2, .x_end = WIN_WIDTH / 2, .fract = fract});
    pthread_create(&tid3, &attr3, fract->thread,
    &(t_thread_data){.x = WIN_WIDTH / 2, .y = 0, .y_end = WIN_HEIGHT / 2, .x_end = (WIN_WIDTH * 3) / 4, .fract = fract});
    pthread_create(&tid4, &attr4, fract->thread,
    &(t_thread_data){.x = (WIN_WIDTH * 3) / 4, .y = 0, .y_end = WIN_HEIGHT / 2, .x_end = WIN_WIDTH, .fract = fract});
    pthread_create(&tid5, &attr5, fract->thread,
    &(t_thread_data){.x = 0, .y = WIN_HEIGHT / 2, .y_end = WIN_HEIGHT, .x_end = WIN_WIDTH / 4, .fract = fract});
    pthread_create(&tid6, &attr6, fract->thread,
    &(t_thread_data){.x = WIN_WIDTH / 4, .y = WIN_HEIGHT / 2, .y_end = WIN_HEIGHT, .x_end = WIN_WIDTH / 2, .fract = fract});
    pthread_create(&tid7, &attr7, fract->thread,
    &(t_thread_data){.x = WIN_WIDTH / 2, .y = WIN_HEIGHT / 2, .y_end = WIN_HEIGHT, .x_end = (WIN_WIDTH * 3) / 4, .fract = fract});
    pthread_create(&tid8, &attr8, fract->thread,
    &(t_thread_data){.x = (WIN_WIDTH * 3) / 4, .y = WIN_HEIGHT / 2, .y_end = WIN_HEIGHT, .x_end = WIN_WIDTH, .fract = fract});

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    pthread_join(tid3, NULL);
    pthread_join(tid4, NULL);
    pthread_join(tid5, NULL);
    pthread_join(tid6, NULL);
    pthread_join(tid7, NULL);
    pthread_join(tid8, NULL);

    return (0);
}
// int   create_julia(t_fractol *fract)
// {
//   register t_complex new;
//   register t_complex old;
//   register int i;
//   register int x;
//   register int y;
//
//   y = -1;
//   while (++y < WIN_HEIGHT && (x = -1))
//     while(++x < WIN_WIDTH && (i = -1))
//     {
//       new.r = 1.5 * (x - WIN_WIDTH / 2) / (0.5 * fract->zoom * WIN_WIDTH) + fract->xoffset;
//       new.i = (y - WIN_HEIGHT / 2) / (0.5 * fract->zoom * WIN_HEIGHT) + fract->yoffset;
//       while (++i < fract->max_iter)
//       {
//         old.r = new.r;
//         old.i = new.i;
//         new.r = old.r * old.r - old.i * old.i + fract->shapecte1;
//         new.i = 2 * old.r * old.i + fract->shapecte2;
//         if((new.r * new.r + new.i * new.i) > 4)
//               break;
//       }
//       put_pixel_img(fract,
//       (t_point){.x = x, .y = y, .color = get_rgb_smooth(i, fract->max_iter)}, 1);
//     }
//   return (0);
// }

// int   create_julia(t_fractol *fract)
// {
// //each iteration, it calculates: new = old*old + c, where c is a constant and old starts at current pixel
// //real and imaginary part of the constant c, determinate shape of the Julia Set
// register double newRe, newIm, oldRe, oldIm;   //real and imaginary parts of new and old
// int color; //the RGB color value for the pixel
//
// //pick some values for the constant c, this determines the shape of the Julia Set
//
// //loop through every pixel
// for(int y = 0; y < WIN_HEIGHT; y++)
// for(int x = 0; x < WIN_WIDTH; x++)
// {
//   //calculate the initial real and imaginary part of z, based on the pixel location and fract->zoom and position values
//   newRe = 1.5 * (x - WIN_WIDTH / 2) / (0.5 * fract->zoom * WIN_WIDTH) + fract->xoffset;
//   newIm = (y - WIN_HEIGHT / 2) / (0.5 * fract->zoom * WIN_HEIGHT) + fract->yoffset;
//   //i will represent the number of iterations
//   int i;
//   //start the iteration process
//   for(i = 0; i < fract->max_iter; i++)
//
//   {
//     //remember value of previous iteration
//     oldRe = newRe;
//     oldIm = newIm;
//     //the actual iteration, the real and imaginary part are calculated
//     newRe = oldRe * oldRe - oldIm * oldIm + fract->shapecte1;
//     newIm = 2 * oldRe * oldIm + fract->shapecte2;
//     //if the point is outside the circle with radius 2: stop
//     if((newRe * newRe + newIm * newIm) > 4) break;
//   }
//   //use color model conversion to get rainbow palette, make brightness black if fract->maxIterations reached
//   color = get_rgb_smooth(i, fract->max_iter);
//   //draw the pixel
//   put_pixel_img(fract, (t_point){.x = x, .y = y, .color = color}, 1);
// }
// return 0;
// }

void        default_values(t_fractol *fract)
{
  fract->shapecte1 = -0.7;
  fract->shapecte2 = 0.27015;
  fract->max_iter = 500;
  fract->zoom = 1.0;
  fract->xoffset = 0.0;
  fract->yoffset = 0.0;
}

t_fractol   *init_fract(char *name)
{
  t_fractol *fract;

  (void)name;
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
