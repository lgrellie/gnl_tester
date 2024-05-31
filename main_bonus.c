/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrellie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 14:37:10 by lgrellie          #+#    #+#             */
/*   Updated: 2024/05/31 13:45:13 by lgrellie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include "get_next_line_bonus.h"

void		ft_putstr_fd(char *s, int fd)
{
	size_t	len;

	len = strlen(s);
	write(fd, s, len);
}

int	gnl_output(const char *path, int *fd)
{
	*fd = open(path, O_RDONLY);
	char *line = NULL;
	char outpath[128];
	char output[] = "output/output_";
	size_t i;
	for (i = 0; i <= 14 + strlen(path); ++i)
		outpath[i] = i < 14 ? output[i] : path[6 + i - 14];

	int out_fd = open(outpath, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	line = get_next_line(*fd);
	while (line != NULL)
	{
		ft_putstr_fd(line, out_fd);
		free(line);
		line = get_next_line(*fd);
	}
	close(out_fd);
	return (0);
}

int main(int ac, const char **av)
{
	if (ac == 1)
	{
		printf("Gimme some file paths!\n");
		return (0);
	}
	else
	{
		int fd_tab[ac];
		int i = 1;

		while (i < ac)
		{
			gnl_output(av[i], &fd_tab[i]);
			++i;
		}
		for (i = 1; i < ac; ++i)
			close(fd_tab[i]);
		return (0);
	}
}
