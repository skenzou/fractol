/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/09 04:24:02 by midrissi          #+#    #+#             */
/*   Updated: 2019/03/09 09:55:43 by midrissi         ###   ########.fr       */
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
		fract->zoom = button == SCROLLUP ? fract->zoom + 1 : fract->zoom;
		fract->zoom = button == SCROLLDOWN ? fract->zoom - 1 : fract->zoom;
	}
  process(fract);
  return (1);
}

int				handle_key(int keycode, t_fractol *fract)
{
	keycode == ESCAPE ? exit(0) : 0;
	(keycode == RIGHTARROW) && (fract->xoffset += 0.01 / fract->zoom);
	(keycode == LEFTARROW) && (fract->xoffset -= 0.01 / fract->zoom);
	(keycode == UPARROW) && (fract->yoffset -= 0.01 / fract->zoom);
	(keycode == DOWNARROW) && (fract->yoffset += 0.01 / fract->zoom);
  (keycode == DKEY) && (fract->shapecte2 += 0.01 / fract->zoom);
  (keycode == AKEY) && (fract->shapecte2 -= 0.01 / fract->zoom);
  (keycode == WKEY) && (fract->shapecte1 += 0.01 / fract->zoom);
  (keycode == SKEY) && (fract->shapecte1 -= 0.01 / fract->zoom);
  (keycode == 18) && (fract->max_iter *= 2);
  (keycode == 19) && (fract->max_iter > 2) && (fract->max_iter /= 2);
	process(fract);
	return (1);
}

static inline int   get_rgb_smooth(int n, int iter_max)
{
  double t;
  int r;
  int g;
  int b;

  t = (double)n / (double)iter_max;
  r = (int)(9.0 * (1.0 - t) * t * t * t * 255.0);
  g = (int)(15.0 * (1.0 - t) * (1.0 - t) * t * t * 255.0);
  b = (int)(8.5 * (1.0 - t) * (1.0 - t) * (1.0 - t) * t * 255.0);
  return ((r << 16) | (g << 8) | b);
}

int   create_julia(t_fractol *fract)
{
  register t_complex new;
  register t_complex old;
  register int i;
  register int x;
  register int y;

  y = -1;
  while (++y < WIN_HEIGHT && (x = -1))
    while(++x < WIN_WIDTH && (i = -1))
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
  mlx_key_hook(fract->win_ptr, &handle_key, fract);
  mlx_mouse_hook(fract->win_ptr, &handle_mouse, fract);
  fract->shapecte1 = -0.7;
  fract->shapecte2 = 0.27015;
  fract->max_iter = 100;
  fract->zoom = 1.0;
  fract->xoffset = 0.0;
  fract->yoffset = 0.0;
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
