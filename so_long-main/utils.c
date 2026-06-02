/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brimarti <brimarti@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 14:31:16 by brimarti          #+#    #+#             */
/*   Updated: 2025/06/27 14:31:19 by brimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	count_lines(int fd)
{
	int		lines;
	char	*line;

	lines = 0;
	line = get_next_line(fd);
	while (line)
	{
		lines++;
		free(line);
		line = get_next_line(fd);
	}
	return (lines);
}

int	line_lenght(int fd)
{
	int		length;
	int		bytes;
	char	buffer[1];

	buffer[0] = '\0';
	bytes = 1;
	length = 0;
	while (bytes == 1)
	{
		bytes = read(fd, buffer, 1);
		if (buffer[0] != '\n')
			length++;
		else
			break ;
	}
	return (length);
}

void	window_size(t_data *data, char **argv)
{
	int	fd;

	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		handle_error(BER, data);
	data->size_x = (line_lenght(fd));
	data->size_y = (count_lines(fd));
	close(fd);
}

void	free_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

void	free_data(t_data *data)
{
	if (data)
	{
		if (data->map)
			free_map(data->map);
		if (data->map_copy)
			free_map(data->map_copy);
	}
}
