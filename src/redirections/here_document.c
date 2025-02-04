/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_document.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylagtab <ylagtab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 17:44:40 by ylagtab           #+#    #+#             */
/*   Updated: 2021/03/05 19:47:04 by ylagtab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal.h"

static char	*remove_leading_tabs(char *str)
{
	char	*result;
	size_t	i;

	if (str == NULL)
		return (NULL);
	i = 0;
	while (str[i])
	{
		if (str[i] != '\t')
			break ;
		++i;
	}
	result = ft_strdup(str + i);
	free(str);
	return (result);
}

static int	read_buffer(char **buffer, char *delimiter, t_bool remove_tabs)
{
	char	*line;
	int		ret;

	*buffer = ft_strdup("");
	while (1)
	{
		if ((ret = readline_21sh(&line, PS2)) == ERROR)
			exit(1);
		if (ret == EXIT)
			break ;
		if (ret == INTERRUPTED)
		{
			free(*buffer);
			return (EXIT_FAILURE);
		}
		if (remove_tabs)
			line = remove_leading_tabs(line);
		if (ft_strequ(line, delimiter))
			break ;
		*buffer = ft_strjoin_free(*buffer, line, 1, 1);
		*buffer = ft_strjoin_free(*buffer, "\n", 1, 0);
	}
	return (EXIT_SUCCESS);
}

int		here_document(int fd, char *delimeter, t_bool remove_tabs)
{
	char	*buffer;
	int		pipe_fd[2];

	if (fd == -1)
		fd = STDIN_FILENO;
	if (pipe(pipe_fd) == -1)
	{
		g_errno = EUNK;
		ft_perror(NULL, NULL, FALSE);
		return (-1);
	}
	if (read_buffer(&buffer, delimeter, remove_tabs) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	ft_printf(pipe_fd[1], buffer);
	close(pipe_fd[1]);
	if (dup2(pipe_fd[0], fd) == -1)
	{
		g_errno = EREDIRECTION;
		ft_perror(NULL, NULL, FALSE);
		return (-1);
	}
	return (EXIT_SUCCESS);
}
