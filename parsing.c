/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tajeong <tajeong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 19:03:52 by tajeong           #+#    #+#             */
/*   Updated: 2024/06/25 18:23:44 by tajeong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "queue.h"

void	_error(char *msg, int error_code)
{
	perror(msg);
	exit(error_code);
}

int	check_file_name(char *path)
{
	int	path_len;

	path_len = ft_strlen(path);
	if (path_len < 5 || \
		!(path[path_len - 4] == '.' && \
		path[path_len - 3] == 'c' && \
		path[path_len - 2] == 'u' && \
		path[path_len - 1] == 'b'))
		return (1);
	return (0);
}

int	check_num(char *num)
{
	while (*num)
	{
		if (ft_isalpha(*num))
			return (1);
		num++;
	}
	return (0);
}

int	free_split(char **split_res, int code)
{
	int	idx;

	idx = 0;
	while (split_res[idx])
	{
		free(split_res[idx]);
		idx++;
	}
	free(split_res);
	return (code);
}

int	color_data_extract(char *color)
{
	char	**split_line;
	int		colori;

	split_line = ft_split(color, ',');
	if (!split_line || \
		split_line[0] == NULL || \
		split_line[1] == NULL || \
		split_line[2] == NULL || \
		split_line[3] != NULL)
		return (free_split(split_line, -1));
	colori = 0;
	if (check_num(split_line[0]) || \
		check_num(split_line[1]) || \
		check_num(split_line[2]))
		return (free_split(split_line, -1));
	colori += (ft_atoi(split_line[0]) << 16);
	colori += (ft_atoi(split_line[1]) << 8);
	colori += ft_atoi(split_line[2]);
	free_split(split_line, 0);
	return (colori);
}

int	element_to_int(char *element)
{
	if (ft_strncmp(element, "NO", 3) == 0)
		return (0);
	else if (ft_strncmp(element, "SO", 3) == 0)
		return (1);
	else if (ft_strncmp(element, "EA", 3) == 0)
		return (2);
	else if (ft_strncmp(element, "WE", 3) == 0)
		return (3); 
	else if (ft_strncmp(element, "F", 2) == 0)
		return (4);
	else if (ft_strncmp(element, "C", 2) == 0)
		return (5);
	return (-1);
}


int	identifier_parsing(t_screen *screen, char *line, int *count)
{
	char	**split_line;
	int		element;

	split_line = ft_split(line, ' ');
	if (!split_line || split_line[0] == NULL || \
		split_line[1] == NULL || split_line[2] != NULL)
		return (free_split(split_line, 1));
	element = element_to_int(split_line[0]);
	if (element == -1)
		return (free_split(split_line, 2));
	if ((*count & (1 << element)) != 0)
		return (free_split(split_line, 3));
	split_line[1][(size_t)(ft_strchr(split_line[1], '\n') - split_line[1])] \
																= '\0';
	if (element < 4)
		screen->tex_ary[element].tex_path = ft_strdup(split_line[1]);
	else if (element == 4)
		screen->floor = color_data_extract(split_line[1]);
	else if (element == 5)
		screen->ceiling = color_data_extract(split_line[1]);
	*count |= (1 << element);
	return (free_split(split_line, 0));
}

void	dump_fd(int fd)
{
	char	*res;

	res = get_next_line(fd);
	free(res);
}

int	extract_texture(t_screen *screen, int fd_tmp, int fd_real)
{
	int		res;
	int		count;
	char	*line;

	count = 0;
	while (count != ((1 << 6) - 1))
	{
		line = get_next_line(fd_tmp);
		dump_fd(fd_real);
		if (line[0] == '\n' || line[0] == '#')
		{
			free(line);
			continue ;
		}
		if (ft_strchr("NSWEFC", line[0]) == NULL)
			_error("invalid identifier", 2);
		res = identifier_parsing(screen, line, &count);
		if (res)
			_error("identifier parsing failed", res);
		free(line);
	}
	return (0);
}

void	print_texture(t_screen *screen)
{
	printf("============ print_texture ============\n");
	printf("%s\n", screen->tex_ary[0].tex_path);
	printf("%s\n", screen->tex_ary[1].tex_path);
	printf("%s\n", screen->tex_ary[2].tex_path);
	printf("%s\n", screen->tex_ary[3].tex_path);
	printf("%d %d %d\n", (screen->ceiling >> 16) % 256, (screen->ceiling >> 8) % 256, screen->ceiling  % 256);
	printf("%d %d %d\n", (screen->floor >> 16) % 256, (screen->floor >> 8) % 256, screen->floor  % 256);
	printf("============ print_texture ============\n");
}

int	maxi(int a, int b)
{
	if (a >= b)
		return (a);
	return (b);
}

void	extract_map_size(t_map *map, int fd_tmp, int fd_real)
{
	char	*line;
	int		flag;

	flag = 0;
	map->map_width = 0;
	map->map_height = 0;
	while (1)
	{
		line = get_next_line(fd_tmp);
		if (flag == 1 && line == NULL)
			break ;
		if (flag == 0 && (line == NULL || ft_isalpha(line[0])))
			_error("map invalid", 1);
		if (flag == 1 && !(line[0] == ' ' || line[0] == '1'))
			_error("map invalid", 2);
		if (line[0] == ' ' || line[0] == '1')
		{
			flag = 1;
			map->map_height++;
			map->map_width = maxi(map->map_width, ft_strlen(line) - 1);
		}
		if (flag == 0)
			dump_fd(fd_real);
		free(line);
	}
}

void	map_alloc(t_map *map)
{
	int		col_idx;
	int		row_idx;

	row_idx = 0;
	map->worldmap = (int **)ft_calloc(map->map_height, sizeof(int *));
	while (row_idx < map->map_height)
	{
		map->worldmap[row_idx] = (int *)ft_calloc(map->map_width, sizeof(int));
		col_idx = 0;
		while (col_idx < map->map_width)
		{
			map->worldmap[row_idx][col_idx] = -1;
			col_idx++;
		}
		row_idx++;
	}
}

void	extract_map(t_map *map, int fd_tmp, int fd_real)
{
	int		col_idx;
	int		row_idx;
	char	*line;

	row_idx = 0;
	extract_map_size(map, fd_tmp, fd_real);
	map_alloc(map);
	while (row_idx < map->map_height)
	{
		line = get_next_line(fd_real);
		col_idx = 0;
		while (col_idx < map->map_width && line[col_idx] != '\n')
		{
			if (ft_strchr(" 01NSEW", line[col_idx]) == NULL)
				_error("invalid character", 1);
			if (line[col_idx] == '0' || line[col_idx] == '1')
				map->worldmap[row_idx][col_idx] = line[col_idx] - '0';
			else if (ft_isalpha(line[col_idx]))
				map->worldmap[row_idx][col_idx] = line[col_idx];
			col_idx++;
		}
		free(line);
		row_idx++;
	}
}

void	print_map(t_map *map)
{
	int		col_idx;
	int		row_idx;

	row_idx = 0;
	while (row_idx < map->map_height)
	{
		col_idx = 0;
		while (col_idx < map->map_width)
		{
			printf("%3d", map->worldmap[row_idx][col_idx]);
			col_idx++;
		}
		printf("\n");
		row_idx++;
	}
}

void	flood(t_map *map, int **visited, t_queue **queue, t_pair coor)
{
	t_queue	*new_data;
	int		y;
	int		x;

	y = coor.y;
	x = coor.x;
	if (!(0 <= y && y < map->map_height && \
		0 <= x && x < map->map_width))
		_error("map invalid", 1);
	if (0 <= y && y < map->map_height && 0 <= x && \
		x < map->map_width && map->worldmap[y][x] == -1)
	{
		_error("map invalid", 2);
	}
	if (0 <= y && y < map->map_height && \
		0 <= x && x < map->map_width && \
		map->worldmap[y][x] != -1 && \
		map->worldmap[y][x] != 1 && visited[y][x] == 0)
	{
		visited[y][x] = 1;
		new_data = queue_new_node(y, x);
		queue_add_back(queue, new_data);
	}
}

void	bfs(t_map *map, int **visited, int y, int x)
{
	t_queue	*data;
	t_queue	*queue;

	queue = queue_new_node(y, x);
	visited[y][x] = 1;
	while (!queue_empty(queue))
	{
		data = queue_del_front(&queue);
		flood(map, visited, &queue, (t_pair){data->y + 1, data->x});
		flood(map, visited, &queue, (t_pair){data->y - 1, data->x});
		flood(map, visited, &queue, (t_pair){data->y, data->x + 1});
		flood(map, visited, &queue, (t_pair){data->y, data->x - 1});
		free(data);
	}
}

void	visited_free(t_map *map, int **visited)
{
	int	idx;

	idx = 0;
	while (idx < map->map_height)
	{
		free(visited[idx]);
		idx++;
	}
	free(visited);
}

int	**visited_alloc(t_map *map)
{
	int	**visited;
	int	idx;

	visited = (int **)ft_calloc(map->map_height, sizeof(int *));
	idx = 0;
	while (idx < map->map_height)
	{
		visited[idx] = (int *)ft_calloc(map->map_width, sizeof(int));
		idx++;
	}
	return (visited);
}


void	print_visited(t_map *map, int **visited)
{
	int		col_idx;
	int		row_idx;

	row_idx = 0;
	while (row_idx < map->map_height)
	{
		col_idx = 0;
		while (col_idx < map->map_width)
		{
			printf("%3d", visited[row_idx][col_idx]);
			col_idx++;
		}
		printf("\n");
		row_idx++;
	}
}

void	check_map(t_map *map)
{
	int	row_idx;
	int	col_idx;
	int	**visited;

	visited = visited_alloc(map);
	row_idx = 0;
	while (row_idx < map->map_height)
	{
		col_idx = 0;
		while (col_idx < map->map_width)
		{
			if (map->worldmap[row_idx][col_idx] == 0 && \
				visited[row_idx][col_idx] == 0)
			{
				bfs(map, visited, row_idx, col_idx);
			}
			col_idx++;
		}
		row_idx++;
	}
	visited_free(map, visited);
}

void	check_map_character(t_map *map)
{
	int	row_idx;
	int	col_idx;
	int	user;

	user = 0;
	row_idx = 0;
	while (row_idx < map->map_height)
	{
		col_idx = 0;
		while (col_idx < map->map_width)
		{
			if (map->worldmap[row_idx][col_idx] == 'N' || \
				map->worldmap[row_idx][col_idx] == 'S' || \
				map->worldmap[row_idx][col_idx] == 'E' || \
				map->worldmap[row_idx][col_idx] == 'W')
				user++;
			col_idx++;
		}
		row_idx++;
	}
	if (user != 1)
		_error("invalid user", 1);
}

void	parsing_map(t_screen *screen, char *path)
{
	int	fd_tmp;
	int	fd_real;

	if (check_file_name(path))
		_error("file format invalid", 1);
	fd_tmp = open(path, O_RDONLY);
	if (fd_tmp == -1)
		_error("map file invalid", 2);
	fd_real = open(path, O_RDONLY);
	if (fd_real == -1)
	{
		close(fd_tmp);
		_error("map file invalid", 2);
	}
	extract_texture(screen, fd_tmp, fd_real);
	print_texture(screen);
	extract_map(&screen->worldmap, fd_tmp, fd_real);
	close(fd_tmp);
	close(fd_real);
	check_map_character(&screen->worldmap);
	check_map(&screen->worldmap);
}
