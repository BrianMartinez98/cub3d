/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_move.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brimarti <brimarti@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 14:29:19 by brimarti          #+#    #+#             */
/*   Updated: 2025/06/27 14:29:22 by brimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	is_valid_move(t_data *data, int new_x, int new_y)
{
	int	map_x;
	int	map_y;

	map_x = new_x / TILE_SIZE;
	map_y = new_y / TILE_SIZE;
	if (new_x < 0 || new_y < 0 || new_x >= data->size_x * 32
		|| new_y >= data->size_y * 32)
		return (0);
	if (data->map[map_y][map_x] == '1')
		return (0);
	else if (data->map[map_y][map_x] == 'E')
	{
		data->flag = true;
		if (data->total_collectables == 0)
		{
			open_exit(data);
			return (1);
		}
	}
	else
		data->flag = false;
	if (data->map[map_y][map_x] == 'C')
		data->total_collectables--;
	return (1);
}

static void	movement(int keycode, int *new_x, int *new_y, t_data *data)
{
	if (keycode == KEY_LEFT || keycode == A)
	{
		*new_x -= TILE_SIZE;
		data->flag_move = true;
	}
	else if (keycode == KEY_RIGHT || keycode == D)
	{
		*new_x += TILE_SIZE;
		data->flag_move = true;
	}
	else if (keycode == KEY_UP || keycode == W)
	{
		*new_y -= TILE_SIZE;
		data->flag_move = true;
	}
	else if (keycode == KEY_DOWN || keycode == S)
	{
		*new_y += TILE_SIZE;
		data->flag_move = true;
	}
}

int	key_hook(int keycode, t_data *data)
{
	int	new_x;
	int	new_y;

	new_x = data->player_x;
	new_y = data->player_y;
	if (keycode == 65307)
		destroy_all(data);
	if (data->flag)
		data->map[data->player_y / TILE_SIZE][data->player_x / TILE_SIZE] = 'E';
	else
		data->map[data->player_y / TILE_SIZE][data->player_x / TILE_SIZE] = '0';
	data->flag_move = false;
	movement(keycode, &new_x, &new_y, data);
	if (is_valid_move(data, new_x, new_y))
	{
		if (data->flag_move)
			ft_printf("moves: %d\n", data->player_moves++);
		data->player_x = new_x;
		data->player_y = new_y;
		if (data->map[new_y / TILE_SIZE][new_x / TILE_SIZE] != 'E')
			data->map[new_y / TILE_SIZE][new_x / TILE_SIZE] = 'P';
		create_map(data);
	}
	return (0);
}
