/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soabbas <soabbas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 13:54:16 by soabbas           #+#    #+#             */
/*   Updated: 2022/07/01 19:31:14 by soabbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*return_save_stash(int *readed, int fd)
{
	char		*stash;
	char		*buffer;

	stash = NULL;
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	while (!ft_strchr_int(stash, '\n'))
	{
		*readed = read(fd, buffer, BUFFER_SIZE);
		if (*readed < 0)
			return (free(stash), free(buffer), NULL);
		buffer[*readed] = '\0';
		stash = ft_strjoin(stash, buffer);
		if (*readed < BUFFER_SIZE)
		{
			free(buffer);
			return (stash);
		}	
		if (!stash || !*readed)
			return (NULL);
	}
	free(buffer);
	return (stash);
}

char	*return_line(char *stash)
{
	int		i;
	int		len;
	char	*line;

	i = 0;
	len = 0;
	if (stash[0] == '\0')
		return (NULL);
	while (stash[len] && stash[len] != '\n')
		len++;
	line = malloc(sizeof(char) * (len + 2));
	if (!line)
		return (NULL);
	while (i < len)
	{
		line[i] = stash[i];
		i++;
	}
	if (stash[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*return_new_save(char *save)
{
	char	*new_save;
	int		len;
	int		i;

	i = 0;
	while (save[i] && save[i] != '\n')
		i++;
	if (save[i] == '\n')
		i++;
	len = i;
	while (save[len])
		len++;
	new_save = malloc(sizeof(char) * ((len - i) + 1));
	if (!new_save)
		return (NULL);
	len = 0;
	while (save[i])
		new_save[len++] = save[i++];
	new_save[len] = '\0';
	free(save);
	return (new_save);
}

char	*get_next_line(int fd)
{
	static char			*save;
	char				*line;
	int					readed;

	readed = 1;
	if (fd < 1 || fd > 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	while (!ft_strchr_int(save, '\n') && (readed > 0))
	{
		save = ft_strjoin(save, return_save_stash(&readed, fd));
		if (!save)
			return (NULL);
	}
	save[ft_strlen(save)] = '\0';
	line = return_line(save);
	if (line == NULL || !line)
		return (NULL);
	save = return_new_save(save);
	return (line);
}
int main()
{
	int		fd = open("test.txt", O_RDONLY);
	char 	*line;

	while(1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		printf("%s", line);
		free(line);
	}
	free(line);
	close(fd);
}
