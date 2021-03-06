/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mschmit <mschmit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/20 17:35:30 by mschmit           #+#    #+#             */
/*   Updated: 2015/05/04 14:32:22 by mschmit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/client.h"

static void		ft_get_norme(char *buf, int sock, int len, int fd)
{
	char	*name;
	int		n;

	ft_bzero(buf, 1023);
	n = recv(sock, buf, 1023, 0);
	buf[n] = '\0';
	name = ft_strdup(buf);
	if (ft_strcmp(name, "-1") == 0)
		ft_printf("ERROR:  \"get <file>\", not \"get <folder>\"...\n", name);
	else if ((fd = open(name, O_WRONLY | O_TRUNC | O_CREAT, 0644)) == -1)
		ft_printf("ERROR:  can't create %s.\n", name);
	else
	{
		while (len > 0)
		{
			ft_bzero(buf, 1023);
			if ((n = recv(sock, buf, 1023, 0)) < 2)
				ft_bzero(buf, 1023);
			write(fd, buf, n);
			len -= n;
		}
		ft_putendl("SUCCESS");
	}
	close(fd);
}

void			ft_get(int sock, char *buf)
{
	int		n;
	int		len;
	int		fd;

	fd = 0;
	ft_bzero(buf, 1023);
	n = recv(sock, buf, 1023, 0);
	buf[n] = '\0';
	len = ft_atoi(buf);
	if (len == -1)
	{
		ft_putendl("ERROR: open().");
		ft_putendl("usage: get <file>.");
	}
	else
		ft_get_norme(buf, sock, len, fd);
	ft_bzero(buf, 1023);
}
