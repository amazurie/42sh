/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/21 22:22:29 by lbopp             #+#    #+#             */
/*   Updated: 2017/11/15 16:37:53 by mameyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	check_flags(t_hist_flags *flags, int *args_pos, int i)
{
	if (flags->more > 1)
	{
		ft_putendl("shell: history: cannot use more than one of -anrw");
		return (0);
	}
	if (flags->c == 1)
		flags->d = 0;
	*args_pos = i;
	return (1);
}

int			get_cd_flags(t_hist_flags *flags, char **tab, int *args_pos)
{
	int		i;
	int		j;

	i = 1;
	while (i < tablen(tab) && tab[i] && tab[i][0] == '-')
	{
		j = 0;
		if (tab[i][j] && tab[i][j] == '-' && tab[i][j + 1]
			&& tab[i][j + 1] == 'd')
		{
			i++;
			flags->d = 1;
		}
		else if (!(get_other_flags(tab, i, j, flags)))
			return (0);
		i++;
	}
	return (check_flags(flags, args_pos, i));
}

static int	error_muchflags(void)
{
	ft_putendl("shell: history: cannot use more than one of -anrw");
	return (0);
}

int			get_cd_flags_2(t_hist_flags *flags, char c)
{
	int		i;
	int		j;

	c == 'c' ? flags->c = 1 : 0;
	c == 'a' ? flags->a = 1 : 0;
	c == 'n' ? flags->n = 1 : 0;
	c == 'r' ? flags->r = 1 : 0;
	c == 'w' ? flags->w = 1 : 0;
	c == 'p' ? flags->p = 1 : 0;
	c == 's' ? flags->s = 1 : 0;
	if ((flags->t += c == '-' ? 1 : 0) > 1)
		return (set_usage(c, 0));
	if (!(i = -1) && c != 'c' && c != 'd' && c != 'a' && c != 'n' && c != 'r'
			&& c != 'w' && c != 'p' && c != 's' && c != '-')
		return (set_usage(c, 0));
	j = 0;
	if (!(check_too_much(flags)))
		return (error_muchflags());
	return (1);
}

int			set_usage(char c, int type)
{
	if (type == 2)
	{
		ft_putendl("shell: history: too many arguments");
		return (1);
	}
	ft_putstr("shell: history: -");
	ft_putchar(c);
	if (type == 0)
		ft_putstr(": invalid option\n");
	else if (type == 1)
		ft_putstr(": option requires an argument\n");
	ft_putstr("history: usage: history [-c] [-d offset] [n] or history");
	ft_putendl(" -awrn [filename] or history -ps arg [arg...]");
	return (1);
}
