/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjenae <fjenae@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 20:45:03 by fjenae            #+#    #+#             */
/*   Updated: 2019/07/04 20:46:49 by fjenae           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFF_SIZE 10000

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include "libft/libft.h"

typedef struct		s_listg
{
	int				fd;
	char			*array;
	struct s_listg	*next;
}					t_listg;

int					get_next_line(const int fd, char **line);

typedef struct		s_gnl_core
{
	int				ret;
	char			buf[BUFF_SIZE + 1];
	char			*array;
	char			*temp;
}					t_gnl_core;

#endif
