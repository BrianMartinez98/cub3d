/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brimarti <brimarti@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 14:27:38 by brimarti          #+#    #+#             */
/*   Updated: 2025/06/27 14:27:41 by brimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	rectangular(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	if (!data->map[0] || data->width == 0)
		return (0);
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j] && data->map[i][j] != '\n')
			j++;
		if (j != data->width)
			return (0);
		i++;
	}
	return (1);
}

static int	walls(t_data *data)
{
	int	i;
	int	j;

	if (!data->map || !data->map[0])
		return (0);
	i = 0;
	while (i < data->height)
	{
		j = 0;
		while (j < data->width)
		{
			if ((j == 0 || j == data->width - 1) && data->map[i][j] != '1')
				return (0);
			if ((i == 0 || i == data->height - 1) && data->map[i][j] != '1')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

static int	possible(t_data *data)
{
	char	*place;

	if (!data->map_copy)
		handle_error(MAPERROR, data);
	data->collectables = 0;
	data->exit = 0;
	place = find_place(data, 'P');
	if (!place)
		handle_error(NOTPLAYER, data);
	ft_painting(data, place[0], place[1], data->map_copy);
	free(place);
	if (data->exit_r == 0 || data->collectables != data->total_collectables)
		return (0);
	return (1);
}

static void	ber_to_char(t_data *data, int fd)
{
	int		i;
	char	*line;

	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		data->map[i] = line;
		if (i == 0)
			data->width = ft_strlen(line) - 1;
		i++;
		line = get_next_line(fd);
	}
	data->height = i;
	close(fd);
}

void	map_checker(t_data *data)
{
	ber_to_char(data, data->fd);
	count_collectables(data);
	check_chars(data);
	data->map_copy = duplicate_map(data->map, data->height, data);
	if (!rectangular(data))
		handle_error(NOTRECTANGULAR, data);
	if (!walls(data))
		handle_error(NOTWALLS, data);
	if (!possible(data))
		handle_error(NOTPOSSIBLE, data);
}
