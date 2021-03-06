/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compl_keys.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/20 13:00:36 by lbopp             #+#    #+#             */
/*   Updated: 2017/11/04 11:33:26 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	check_onscreen(t_compl *compl, int *size, int toskip)
{
	int	i;

	i = -1;
	while (++i < size[3])
	{
		if (compl->curr >= toskip + size[4] * i
				&& compl->curr < toskip + size[4] * i + size[1])
			return (1);
	}
	return (0);
}

static int	get_onscreen(t_compl *compl, t_cmd *cmd)
{
	int	*size;
	int	toskip;

	size = get_size(compl, cmd);
	toskip = compl->toskip;
	while (toskip < size[4] - size[1])
	{
		if (check_onscreen(compl, size, toskip))
		{
			free(size);
			return (toskip);
		}
		toskip++;
	}
	while (toskip > 0)
	{
		if (check_onscreen(compl, size, toskip))
		{
			free(size);
			return (toskip);
		}
		toskip--;
	}
	free(size);
	return (0);
}

static int	check_keys(t_compl *compl, t_cmd *cmd, char **buf)
{
	if ((*buf)[0] == 27 && !(*buf)[1])
		return (-1);
	else if (compl->curr != -1 && (*buf)[0] == 27
			&& compl_arrow(compl, cmd, *buf))
	{
		compl->toskip = get_onscreen(compl, cmd);
		display_args(compl, cmd);
	}
	else if ((*buf)[0] == 9 && !(*buf)[1])
	{
		compl->curr = (compl->curr < compl->nbrargs - 1) ? compl->curr + 1 : 0;
		compl->toskip = get_onscreen(compl, cmd);
		display_args(compl, cmd);
	}
	else
	{
		add_argtoline(compl, cmd);
		if ((*buf)[0] == 10 && !(*buf)[1])
			return (-1);
		return (0);
	}
	return (1);
}

int			compl_keys(t_compl *compl, t_cmd *cmd, char **buf)
{
	int	i;

	ft_bzero(*buf, ft_strlen(*buf));
	read(0, *buf, 5);
	if ((i = is_sigint(0)) == 2)
		return (0);
	(i == 1) ? is_sigint(1) : 0;
	if (i == 1)
		return (0);
	return (check_keys(compl, cmd, buf));
}
