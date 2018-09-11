/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molwage <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/27 10:47:04 by molwage           #+#    #+#             */
/*   Updated: 2018/09/01 17:25:13 by molwage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include <stdio.h>

t_map *init_filler(void)
{
	t_map *e;

	e = (t_map *)malloc(sizeof(t_map));
	e->map = NULL;
	e->mx = 0;
	e->my = 0;
	e->tok = NULL;
	e->tx = 0;
	e->ty = 0;
	e->p1 = 0;
	e->p2 = 0;
	return (e);
}

void	get_map(t_map *e)
{
	char **s;
	char *line;

	while (get_next_line(0, &line) > 0)
	{
		if (!ft_strncmp(line, "$$$", 3))
		{
			e->p1 = *(line + 10) == '1' ? 'O' : 'X';
			e->p2 = (e->p1 == 'O' ? 'X' : 'O');
			get_next_line(0, &line);
		}
		else if (!ft_strncmp(line, "Plateau", 7))
		{
			s = ft_strsplit(line, ' ');
			e->my = ft_atoi(s[1]);
			e->mx = ft_atoi(s[2]);
			get_next_line(0, &line);
			break;
		}
	}
}

void	store_map(t_map *e)
{
	char **s;
	int i = 0;
	char *line;
	e->map = (char **)malloc(sizeof(char *) * e->my);
	while (get_next_line(0, &line) > 0)
	{	
		if (ft_strstr(line, "Piece") != NULL)
			break;
		e->map[i] = ft_strdup(line + 4);
		i++;
	}
	i = 0;
	s = ft_strsplit(line, ' ');
	e->ty = ft_atoi(s[1]);
	fprintf(stderr, ">>>> ty = %d\n", e->ty);
	e->tx = ft_atoi(s[2]);
	fprintf(stderr, ">>>> tx = %d\n", e->tx);
	e->tok = (char **)malloc(sizeof(char *) * e->ty);
	while(get_next_line(0, &line) > 0)
	{
		e->tok[i] = ft_strdup(line);
		i++;
	}
}

int main()
{
	t_map *e;
	char *line;

	e = init_filler();
	get_map(e);
	store_map(e);
	printf("8 2\n");
	fprintf(stderr, "p1  %c\n", e->p1);
	fprintf(stderr, "p2  %c\n", e->p2);
	for(int i = 0; i < e->my;i++)
		fprintf(stderr, "%s\n", e->map[i]);
	for(int z = 0; z < e->ty;z++)
		fprintf(stderr, "%s\n", e->tok[z]);
}
