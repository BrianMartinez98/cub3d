/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brimarti <brimarti@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 14:30:52 by brimarti          #+#    #+#             */
/*   Updated: 2025/06/27 14:30:54 by brimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# define TILE_SIZE 32

# define KEY_PRESS 2
# define MOUSE_PRESS 17

# define KEY_UP 65362
# define KEY_DOWN 65364
# define KEY_RIGHT 65363
# define KEY_LEFT 65361

# define A 97
# define S 115
# define D 100
# define W 119

# define CHARS "PEC01"

# include "minilibx-linux/mlx.h"
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdbool.h>
# include "get_next_line.h"
# include "ft_printf.h"

typedef enum s_errorlst
{
	PARAMETROS,
	MALLOCERROR,
	FD,
	IMG_ERROR,
	NOTRECTANGULAR,
	NOTWALLS,
	NOTPOSSIBLE,
	BER,
	INVALID_CHARS,
	INVALID_PE,
	NOTPLAYER,
	MAPERROR
}		t_errorlst;

typedef struct s_data
{
	void		*mlx;
	void		*window;
	char		*back;
	char		*obj;
	char		*wall;
	char		*player;
	char		*exit;
	int			size_x;
	int			size_y;
	int			fd;
	int			player_x;
	int			player_y;
	int			total_collectables;
	int			collectables;
	int			player_collectables;
	int			player_moves;
	bool		flag;
	char		**map;
	char		**map_copy;
	int			width;
	int			height;
	int			exit_r;
	int			enumb;
	int			pnumb;
	int			flag_move;
	bool		game_over;
}				t_data;

void	count_collectables(t_data *data);
char	**duplicate_map(char **original, int height, t_data *data);
char	*find_place(t_data *data, char a);
void	ft_painting(t_data *data, int row, int colum, char **map);

void	map_checker(t_data *data);

void	handle_error(t_errorlst error, t_data *data);
int		destroy_all(t_data *data);

int		ft_init(t_data *data, char **argv);
void	check_chars(t_data *data);

int		key_hook(int keycode, t_data *data);

void	game_init(t_data *data);
int		game_loop(t_data *data);

char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
void	*ft_memset(void *b, int c, size_t len);
char	*ft_strdup(char *src);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

void	open_exit(t_data *data);
void	create_map(t_data *data);

int		count_lines(int fd);
int		line_lenght(int fd);
void	window_size(t_data *data, char **argv);
void	free_map(char **map);
void	free_data(t_data *data);

#endif
