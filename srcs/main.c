/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 13:46:58 by midrissi          #+#    #+#             */
/*   Updated: 2019/03/22 17:32:50 by midrissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void		launch_threads(t_fractol *fract)
{
	pthread_attr_t	attr;
	int				err;
	int				i;

	i = 0;
	pthread_attr_init(&attr);
	while (i < TNUM)
	{
		err = pthread_create(&(fract->tids[i]), &attr, fract->thread,
															&fract->tdata[i]);
		if (err)
		{
			perror("thread error");
			exit(1);
		}
		i++;
	}
	i = 0;
	while (i < TNUM)
		pthread_join(fract->tids[i++], NULL);
}

void			process(t_fractol *fract)
{
	launch_threads(fract);
	mlx_put_image_to_window(fract->mlx_ptr, fract->win_ptr, fract->img->ptr,
																		503, 0);
}

static void		check_error(int argc, char **argv)
{
	if (argc != 2 || (ft_strcmp(argv[1], "Julia")
	&& ft_strcmp(argv[1], "Burningship") && ft_strcmp(argv[1], "Mandelbrot")
	&& ft_strcmp(argv[1], "Tricorn")))
	{
		ft_putendl_fd(ANSI_RED "usage: ./fractol <fractol_name>"
		ANSI_RESET, 2);
		ft_putendl_fd(ANSI_CYAN "fractols:" ANSI_RESET, 2);
		ft_putendl_fd(ANSI_BLUE "--> Mandelbrot" ANSI_RESET, 2);
		ft_putendl_fd(ANSI_MAGENTA "--> Julia" ANSI_RESET, 2);
		ft_putendl_fd(ANSI_YELLOW "--> Burningship" ANSI_RESET, 2);
		ft_putendl_fd(ANSI_GREEN "--> Tricorn" ANSI_RESET, 2);
		exit(1);
	}
}

static void		put_thumbnails(t_fractol *fract)
{
	julia_thumbnail(fract);
	tricorn_thumbnail(fract);
	mandelbrot_thumbnails(fract);
	burningship_thumbnails(fract);
}

int				main(int argc, char **argv)
{
	t_fractol *fract;

	check_error(argc, argv);
	fract = init_fract(argv[1]);
	put_legend(fract);
	put_thumbnails(fract);
	process(fract);
	mlx_loop(fract->mlx_ptr);
	return (0);
}
