/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchoy-me <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 15:34:08 by jchoy-me          #+#    #+#             */
/*   Updated: 2023/08/28 13:22:43 by jchoy-me         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
A rough line is the result of 1 or more buffer reads that reaches a new line 
or EOF. This can include characters after the '\n' or not include a '\n' if
it is the EOF.
If the return value of read is < 0 mean we have an error.
If the return value of read is = 0 we reached the EOF.
*/

/*
prep_rough_line will get a full line including '\n' by reading the file
and saving the bytes into the buffer as many times as needed. it stops once
get a full line. It also gets the remaining from the static variable to make 
the full line.
*/

static char	*prep_rough_line(int fd, char *buffer, char *line_remainder)
{
	int		bytes_read;
	int		line_completed;
	char	*temp;

	line_completed = 0;
	while (line_completed == 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (NULL);
		if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0'; 
		if (line_remainder == NULL)
			line_remainder = ft_strdup("");
		temp = line_remainder;
		line_remainder = ft_strjoin(temp, buffer);
		free(temp);
		temp = NULL;
		if (ft_strchr(buffer, '\n') != 0)
			line_completed = 1;
	}
	return (line_remainder);
}

/*
Pass the rough line to the helper function and get a substring from it up 
to and including the \n.
*/

static char	*get_cropped_line(char	*rough_line)
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

/*
Gets the rough line and returns the remainder of the line after the '\n'
*/

static char	*get_line_remainder(char *rough_line)
{
	size_t	i;
	int		start;
	int		remain_len;
	char	*line_remainder;

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
Allocates the read buffer memory and calls the function to get the rough line, 
crop the line and save the remainder to use it on the next read.
*/

char	*get_next_line(int fd)
{
	char		*rough_line;
	char		*cropped_line;
	char		*buffer;
	static char	*line_remainder;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *) malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buffer == NULL)
		return (NULL);
	rough_line = prep_rough_line(fd, buffer, line_remainder);
	free(buffer);
	if (rough_line == NULL)
	{
		if (line_remainder != NULL)
		{
			free(line_remainder);
			line_remainder = NULL;
		}
		return (NULL);
	}
	cropped_line = get_cropped_line(rough_line);
	line_remainder = get_line_remainder(rough_line);
	free(rough_line);
	return (cropped_line);
}

/*
Test with main to keep reading until it reaches the end of file.
*/

// #include <fcntl.h>
// #include <stdio.h>

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
