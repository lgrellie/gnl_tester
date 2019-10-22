/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrellie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 14:37:10 by lgrellie          #+#    #+#             */
/*   Updated: 2019/10/22 18:15:37 by lgrellie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include "get_next_line.h"

void		ft_putstr_fd(char *s, int fd)
{
	size_t	len;

	len = strlen(s);
	write(fd, s, len);
}

void		ft_putendl_fd(char *s, int fd)
{
	ft_putstr_fd(s, fd);
	write(fd, "\n", 1);
}

int	gnl_output(const char *path)
{
	int fd = open(path, O_RDONLY);
	char *line;
	char *outpath;
	char output[] = "output/output_";
	outpath = malloc(14 + strlen(path));
	for (int i = 0; i <= 14 + strlen(path); ++i)
		outpath[i] = i < 14 ? output[i] : path[6 + i - 14];
	
	int out_fd = open(outpath, O_CREAT | O_WRONLY, S_IRWXU);
	//printf("%d\t%d\t%s\n", fd, out_fd, outpath);
loop:
	switch(get_next_line(fd, &line))
	{
		case 1:
			ft_putendl_fd(line, out_fd);
			free(line);
			goto loop;
		case 0:
			ft_putstr_fd(line, out_fd);
			free(line);
			close(fd);
			close(out_fd);
			return (0);
		case -1:
			ft_putstr_fd("@@@@@@@@@@ERROR@@@@@@@@@@", out_fd);
			free(line);
			close(fd);
			close(out_fd);
			return (-1);
	}
	return (-1);
}

int gnl_tester(const char *path)
{
	int fd = open(path, O_RDONLY);
	char *line;

	if (fd > 0)
	{
deb:
		switch (get_next_line(fd, &line))
		{
			case 1:
				printf("%s\n", line);
				free(line);
				goto deb;
			case 0:
				printf("%sEOF\n", line);
				free(line);
				close(fd);
				return (0);
			case -1:
				printf("Houston, we got a problem...\n");
				close(fd);
				return (-1);
		}
	}
	return(-1);
}

int main(int ac, const char **av)
{
	if (ac < 2)
	{
		printf("program path\n");
		return (1);
	}
	else
	{
		int tests_passed = 0;
		int tests_failed = 0;
		int names_passed[ac];
		int i = 1;

		while (i < ac)
		{
			if (gnl_output(av[i]) == 0)
			{
				++tests_passed;
				names_passed[i] = 0;
			}
			else
			{
				++tests_failed;
				names_passed[i] = 1;
			}
			++i;
		}
		printf("Tests taken: %d\tTests passed: %d\tTests failed: %d\n", ac - 1, tests_passed, tests_failed);
		return (0);
	}
}
