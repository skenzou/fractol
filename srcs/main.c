/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 13:46:58 by midrissi          #+#    #+#             */
/*   Updated: 2019/03/16 17:41:44 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

// static inline void			center(t_fractol *fract, int x, int y)
// {
// 	double percent;
//
// 	percent = ft_percent(WIN_W / 2, x < WIN_W / 2 ? 0 : WIN_W, x);
// 	fract->xoffset += x < WIN_W / 2 ? (-1.5 * percent) / fract->zoom
// 					: (1.5 * percent) / fract->zoom;
// 	percent = ft_percent(WIN_H / 2, y < WIN_H / 2 ? 0
// 					: WIN_H, y);
// 	fract->yoffset += y < WIN_H / 2 ? -percent / fract->zoom
// 					: percent / fract->zoom;
// }

 void 	launch_threads(t_fractol *fract)
 {
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

static void   check_error(int argc, char **argv)
{
	if (argc != 2 || (ft_strcmp(argv[1], "Julia")
	&& ft_strcmp(argv[1], "Burningship") && ft_strcmp(argv[1], "Mandelbrot")
  && ft_strcmp(argv[1], "Tricorn")))
	{
		ft_putendl_fd(ANSI_BOLD ANSI_RED "usage: ./fractol <fractol_name>"
		ANSI_RESET, 2);
		ft_putendl_fd(ANSI_BOLD ANSI_CYAN "fractols:" ANSI_RESET, 2);
		ft_putendl_fd(ANSI_BOLD ANSI_BLUE "--> Mandelbrot" ANSI_RESET, 2);
		ft_putendl_fd(ANSI_BOLD ANSI_MAGENTA "--> Julia" ANSI_RESET, 2);
		ft_putendl_fd(ANSI_BOLD ANSI_YELLOW "--> Burningship" ANSI_RESET, 2);
    ft_putendl_fd(ANSI_BOLD ANSI_GREEN "--> Tricorn" ANSI_RESET, 2);
		exit(1);
	}
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
