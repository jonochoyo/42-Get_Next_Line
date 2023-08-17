/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchoy-me <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 15:34:08 by jchoy-me          #+#    #+#             */
/*   Updated: 2023/08/17 17:11:36 by jchoy-me         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
Attempting to read BUFFER_SIZE from a text file. 
If the fd is negative or the BUFFER_SIZE is <= 0, return NULL as can't read. 
If the return value of read is <= 0 mean we reached the EOF or we got an error.
*/

char	*get_next_line(int fd)
{
	char	*buffer;
	int		bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *) malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buffer == NULL)
		return (NULL);
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read <= 0)
		return (NULL);
	return (buffer);
}

/*
Test with main to keep reading until it reaches the end of file.
*/

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
