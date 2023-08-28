/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchoy-me <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 15:34:08 by jchoy-me          #+#    #+#             */
/*   Updated: 2023/08/28 17:52:04 by jchoy-me         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*get_rough_line(int fd, char *buffer, char *line_save)
{
	char	*temp;
	int		bytes_read;
	int		line_completed;

	line_completed = 0;
	while (line_completed == 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (NULL);
		if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0'; 
		if (line_save == NULL)
			line_save = ft_strdup("");
		temp = line_save;
		line_save = ft_strjoin(temp, buffer);
		free(temp);
		temp = NULL;
		if (ft_strchr(buffer, '\n') != 0)
			line_completed = 1;
	}
	return (line_save);
}

static char	*get_cropped_line(char *rough_line)
{
	size_t	i;
	char	*cropped_line;

	i = 0;
	if (rough_line == NULL)
		return (NULL);
	while (rough_line[i] != '\n' && rough_line[i] != '\0')
		i++;
	cropped_line = ft_substr(rough_line, 0, i + 1);
	return (cropped_line);
}

static char	*get_line_remainder(char *rough_line)
{
	char	*line_remainder;
	int		start;
	int		remain_len;
	size_t	i;

	i = 0;
	line_remainder = NULL;
	if (rough_line == NULL)
		return (NULL);
	while (rough_line[i] != '\n' && rough_line[i] != '\0')
		i++;
	start = i + 1;
	remain_len = ft_strlen(rough_line) - start;
	if (remain_len > 0)
		line_remainder = ft_substr(rough_line, start, remain_len);
	if (line_remainder == NULL)
		return (NULL);
	return (line_remainder);
}

/*
Bonus
- Use an array of strings as static variable to carry the line_remainder
for each fd. 
- Edit the function to use line_remainder[fd] to get next line of each fd and
edit the static variable string that corresponds to each fd.
*/

char	*get_next_line(int fd)
{
	char		*buffer;
	char		*rough_line;
	char		*cropped_line;
	static char	*line_remainder[1024];

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > 1023)
		return (NULL);
	buffer = (char *) malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buffer == NULL)
		return (NULL);
	rough_line = get_rough_line(fd, buffer, line_remainder[fd]);
	free(buffer);
	if (rough_line == NULL)
	{
		if (line_remainder[fd] != NULL)
		{
			free(line_remainder[fd]);
			line_remainder[fd] = NULL;
		}
		return (NULL);
	}
	line_remainder[fd] = get_line_remainder(rough_line);
	cropped_line = get_cropped_line(rough_line);
	free(rough_line);
	return (cropped_line);
}

/*
Test with main to keep reading until it reaches the end of file.
*/

/*
#include <fcntl.h>
#include <stdio.h>

int	main(void)
{
	char	*line;
	int		fd;

	fd = open("test.txt", O_RDONLY);
	line = get_next_line(fd);
	printf("--");
	while (line != NULL)
	{
		printf("%s--", line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}
*/
