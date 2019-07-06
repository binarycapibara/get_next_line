/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjenae <fjenae@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 20:44:17 by fjenae            #+#    #+#             */
/*   Updated: 2019/07/04 20:46:07 by fjenae           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static t_listg	*ft_generator(int fd, t_listg **alst, t_listg *new, int flag)
{
	t_listg			*shaker;

	if (flag == 1)
	{
		if (!(shaker = (t_listg *)malloc(sizeof(t_listg))))
			return (NULL);
		shaker->fd = fd;
		shaker->array = ft_strnew(0);
		shaker->next = NULL;
		return (shaker);
	}
	if (!alst || !new)
		return (NULL);
	new->next = *alst;
	*alst = new;
	return (NULL);
}

static void		data_management(t_listg **root, int fd, char **array)
{
	t_listg			*kit;
	t_listg			*list_copy;

	if (!(*root))
		*root = ft_generator(fd, NULL, NULL, 1);
	list_copy = *root;
	while (list_copy)
	{
		if (list_copy->fd == fd)
		{
			*array = list_copy->array;
			return ;
		}
		list_copy = list_copy->next;
	}
	kit = ft_generator(fd, NULL, NULL, 1);
	ft_generator(0, root, kit, 0);
	*array = (*root)->array;
}

static int		check_eof(char *array, char **line)
{
	if (!array || array[0] == '\0')
	{
		*line = "";
		return (1);
	}
	return (0);
}

static void		clear_temp(t_listg **root, int fd, char **temp)
{
	t_listg	*list_copy;

	list_copy = *root;
	while (list_copy)
	{
		if (list_copy->fd == fd)
		{
			if (*temp)
			{
				list_copy->array = ft_strdup(*temp + 1);
				**temp = '\0';
			}
			else
				list_copy->array = "\0";
			return ;
		}
		list_copy = list_copy->next;
	}
}

int				get_next_line(const int fd, char **line)
{
	static t_listg	*root;
	t_gnl_core		m;

	if ((read(fd, m.buf, 0)) == -1 || !line)
		return (-1);
	m.array = NULL;
	data_management(&root, fd, &m.array);
	while (!ft_strchr(m.array, '\n') && (m.ret = read(fd, m.buf, BUFF_SIZE)))
	{
		m.buf[m.ret] = '\0';
		m.temp = m.array;
		m.array = ft_strjoin(m.temp, m.buf);
		ft_strdel(&m.temp);
	}
	if (check_eof(m.array, line))
	{
		return (0);
	}
	*line = m.array;
	m.temp = ft_strchr(m.array, '\n');
	clear_temp(&root, fd, &m.temp);
	return (1);
}
