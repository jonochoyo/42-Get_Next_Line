/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchoy-me <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 15:34:08 by jchoy-me          #+#    #+#             */
/*   Updated: 2023/08/15 17:34:22 by jchoy-me         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
Static variables have the property of preserving their value even after 
they are out of their scope. 
*/

char	*get_next_line(int fd)
{
	char	*buffer;

	buffer = malloc(sizeof(char) * 25);
	fd = open("test.txt", O_RDONLY);
	read(fd, buffer, 25);

	return (buffer);
}

int	main(void)
{
	printf("%s", get_next_line(1));
}