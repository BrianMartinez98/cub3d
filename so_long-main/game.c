/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brimarti <brimarti@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 14:29:32 by brimarti          #+#    #+#             */
/*   Updated: 2025/06/27 14:29:34 by brimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	ft_img_init(t_data *data)
{
	int	width;
	int	height;

	data->back = mlx_xpm_file_to_image(data->mlx,
			"rs/back.xpm", &width, &height);
	data->obj = mlx_xpm_file_to_image(data->mlx,
			"rs/obj.xpm", &width, &height);
	data->wall = mlx_xpm_file_to_image(data->mlx,
			"rs/wall.xpm", &width, &height);
	data->player = mlx_xpm_file_to_image(data->mlx,
			"rs/player.xpm", &width, &height);
	data->exit = mlx_xpm_file_to_image(data->mlx,
			"rs/exit.xpm", &width, &height);
	if (!data->back || !data->obj || !data->wall
		|| !data->player || !data->exit)
		handle_error(IMG_ERROR, data);
}

void	game_init(t_data *data)
{
	data->mlx = mlx_init();
	if (NULL == data->mlx)
		destroy_all(data);
	data->window = mlx_new_window(data->mlx, data->size_x * TILE_SIZE,
			data->size_y * TILE_SIZE + TILE_SIZE, "so_long");
	if (NULL == data->window)
		destroy_all(data);
	ft_img_init(data);
	create_map(data);
	mlx_hook(data->window, KEY_PRESS, 1L >> 0, key_hook, data);
	mlx_hook(data->window, MOUSE_PRESS, 0, destroy_all, data);
	data->game_over = false;
	mlx_loop_hook(data->mlx, game_loop, data);
	mlx_loop(data->mlx);
}

int	game_loop(t_data *data)
{
	if (data->game_over)
	{
		destroy_all(data);
		exit(0);
	}
	return (0);
}
