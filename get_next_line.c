/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchoy-me <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 15:34:08 by jchoy-me          #+#    #+#             */
/*   Updated: 2023/08/28 16:31:01 by jchoy-me         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
static char	*get_rough_line(int fd, char *buffer, char *line_save);
- Loops until a rough line is completed.
- Reads and saves it into the buffer as many times as needed to get the next 
rough line. The buffer is saved as a string with '\0'.
- If the read return is < 0, there is an error and the function returns NULL. 
- If the read return is = 0, it reached the EOF and breaks out of the loop.
- If line_save, which its initial input is the line_remainder, is NULL,
we create an empty string to assign it to its value to use with ft_strjoin().
- The line_save is joined with the buffer.
- If the buffer has a '\n' we break out of the loop.
*/

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

/*
static char	*get_cropped_line(char *rough_line);
- Iterates through the rough line until if finds the '\n'.
- Returns a substring of rough line from index 0 up to and including '\n'.
*/

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

/*
static char	*get_line_remainder(char *rough_line);
- Creates a string line_remainder initialised as NULL.
- Iterates through the rough line until if finds the '\n'.
- Sets a start index as the character after the '\n'.
- Calculates the length of the line_remainder and sets it to remain_len.
- Creates a substring for the characters after the '\n'.
- Returns the line_remainder or NULL if there is no remaining characters.
*/

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
char	*get_next_line(int fd);
- Allocates the buffer memory to save what is read from the file.
- Gets the next rough line and checks if it is NULL to clear the
line_remainder if it still carries a string.
- Saves the remainder characters after the '\n' to use it on the next read.
- Crops the rough line up to and including the '\n' and returns it.
*/

char	*get_next_line(int fd)
{
	char		*buffer;
	char		*rough_line;
	char		*cropped_line;
	static char	*line_remainder;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *) malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buffer == NULL)
		return (NULL);
	rough_line = get_rough_line(fd, buffer, line_remainder);
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
	line_remainder = get_line_remainder(rough_line);
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
