/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchoy-me <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 15:34:08 by jchoy-me          #+#    #+#             */
/*   Updated: 2023/08/18 17:55:08 by jchoy-me         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
Attempting to read BUFFER_SIZE from a text file. 
If the fd is negative or the BUFFER_SIZE is <= 0, return NULL as can't read. 
If the return value of read is <= 0 mean we reached the EOF or we got an error.
*/

/*
save_full_line will get a full line including '\n' by reading the file
and saving the bytes into the buffer as many times as needed. it stops once
get a full line.
*/

char	*save_full_line(int fd)
{
	char	*full_line;
	int		bytes_read;
	int		line_completed;
	char	*buffer;

	line_completed = 0;
	full_line = ft_strdup("\0");
	while (line_completed == 0)
	{
		buffer = (char *) malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (buffer == NULL)
		{
			free(full_line);
			return (NULL);
		}	
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
		{
			free(buffer);
			free(full_line);
			return (NULL);
		}
		buffer[BUFFER_SIZE] = '\0';
		if (ft_strchr(buffer, '\n') != 0)
			line_completed = 1;
		full_line = ft_strjoin(full_line, buffer);
		free(buffer);
	}
	return (full_line);
}

/*
Pass the full line to the helper function and get a substring from it up 
to and including the \n.
*/

char	*get_cropped_line(char	*full_line)
{
	size_t	i;
	char	*cropped_line;

	i = 0;
	if (full_line == NULL)
		return (NULL);
	while (full_line[i] != '\n' && full_line[i] != '\0')
	{
		i++;
	}
	i++;
	cropped_line = ft_substr(full_line, 0, i);
	return (cropped_line);
}

char	*get_line_remainder(char *full_line)
{
	size_t	i;
	int		start;
	int		remain_len;
	char	*line_remainder;

	i = 0;
	if (full_line == NULL)
		return (NULL);
	while (full_line[i] != '\n' && full_line[i] != '\0')
	{
		i++;
	}
	i++;
	start = i;
	remain_len = ft_strlen(full_line) - start + 1;
	line_remainder = ft_substr(full_line, start, remain_len);
	if (line_remainder == NULL)
		return (NULL);
	return (line_remainder);
}

char	*get_next_line(int fd)
{
	char	*full_line;
	char	*cropped_line;
	static char	*remaining_line;
	char	*return_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	full_line = save_full_line(fd);
	if (full_line == NULL)
		return (NULL);
	cropped_line = get_cropped_line(full_line);
	if (remaining_line != NULL)
		return_line = ft_strjoin(remaining_line, cropped_line);
	else
		return_line = ft_strdup(cropped_line);
	remaining_line = get_line_remainder(full_line);
	free(full_line);
	free(cropped_line);
	return (return_line);
}

/*
Test with main to keep reading until it reaches the end of file.
*/

// int	main(void)
// {
// 	char	*line;
// 	int		fd;

// 	fd = open("test.txt", O_RDONLY);
// 	line = get_next_line(fd);
// 	printf("--");
// 	while (line != NULL)
// 	{
// 		printf("%s--", line);
// 		free(line);
// 		line = get_next_line(fd);
// 	}
// 	close(fd);
// 	return (0);
// }
