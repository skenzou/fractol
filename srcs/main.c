/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midrissi <midrissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 13:46:58 by midrissi          #+#    #+#             */
/*   Updated: 2019/03/17 15:16:00 by midrissi         ###   ########.fr       */
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
																		0, 0);
}

static void		check_error(int argc, char **argv)
{
	if (argc != 2 || (ft_strcmp(argv[1], "Julia")
	&& ft_strcmp(argv[1], "Burningship") && ft_strcmp(argv[1], "Mandelbrot")
	&& ft_strcmp(argv[1], "Tricorn")))
	{
		ft_putendl_fd("usage: ./fractol <fractol_name>", 2);
		ft_putendl_fd("fractols:", 2);
		ft_putendl_fd("--> Mandelbrot", 2);
		ft_putendl_fd("--> Julia", 2);
		ft_putendl_fd("--> Burningship", 2);
		ft_putendl_fd("--> Tricorn", 2);
		exit(1);
	}
}

int				main(int argc, char **argv)
{
	t_fractol *fract;

	check_error(argc, argv);
	fract = init_fract(argv[1]);
	put_legend(fract);
	process(fract);
	mlx_loop(fract->mlx_ptr);
	return (0);
}
