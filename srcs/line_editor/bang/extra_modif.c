/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_modif.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/04 19:26:44 by lbopp             #+#    #+#             */
/*   Updated: 2017/11/05 13:10:09 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		init_substi1(int *i, int *k, char *old, int j)
{
	*i = 0;
	*k = j * ft_strlen(old);
}

void		init_substi2(int *j, int *l, char *arg)
{
	*j = 0;
	*l = ft_strlen(arg);
}

void		init_substi3(int *i, int *j, int *l, char *arg)
{
	*i = 0;
	*j = 0;
	*l = ft_strlen(arg);
}

void		loop_substi(int *i, int *j, char *old)
{
	*i += ft_strlen(old);
	(*j)++;
}

char		*free_str_return_null(char **str)
{
	ft_strdel(str);
	return (NULL);
}
