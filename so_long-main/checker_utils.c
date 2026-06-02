/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brimarti <brimarti@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 14:26:58 by brimarti          #+#    #+#             */
/*   Updated: 2025/06/27 14:27:11 by brimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	count_collectables(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] == 'C')
				data->total_collectables += 1;
			j++;
		}
		i++;
	}
}

char	**duplicate_map(char **original, int height, t_data *data)
{
	int		i;
	char	**copy;

	copy = malloc(sizeof(char *) * (height + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < height)
	{
		copy[i] = ft_strdup(original[i]);
		if (!copy[i])
			handle_error(MALLOCERROR, data);
		i++;
	}
	copy[height] = NULL;
	return (copy);
}

static char	*set_place(int i, int j, char *place)
{
	place[0] = i;
	place[1] = j;
	return (place);
}

char	*find_place(t_data *data, char a)
{
	int		i;
	int		j;
	char	*place;

	i = 0;
	place = (char *)malloc(sizeof(char) * 3);
	if (!place)
		return (NULL);
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] == a)
			{
				set_place(i, j, place);
				return (place);
			}
			j++;
		}
		i++;
	}
	free(place);
	return (NULL);
}

void	ft_painting(t_data *data, int row, int colum, char **map)
{
	char	current;

	if (row < 0 || colum < 0 || row >= data->height)
		return ;
	if (colum >= (int)ft_strlen(map[row]))
		return ;
	current = map[row][colum];
	if (current == 'r' || current == '1')
		return ;
	if (current == '0' || current == 'C')
	{
		if (current == 'C')
			data->collectables++;
		map[row][colum] = 'r';
	}
	else if (current == 'E')
	{
		data->exit_r = 1;
		return ;
	}
	ft_painting(data, row + 1, colum, map);
	ft_painting(data, row - 1, colum, map);
	ft_painting(data, row, colum + 1, map);
	ft_painting(data, row, colum - 1, map);
}
