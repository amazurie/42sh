/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_bang.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/05 15:53:11 by lbopp             #+#    #+#             */
/*   Updated: 2017/11/05 16:47:53 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char		*loop_bang(t_control **history, char *cmd, char ***env)
{
	int		end;
	int		f;
	char	*new;
	t_cmd	cmd2;

	end = 0;
	f = 0;
	cmd2 = init_cmd(return_prompt());
	cmd2.str = ft_strdup(cmd);
	if ((new = deal_bang(cmd2.str, *history, &end, &f)) && !end && f)
	{
		ft_strdel(&cmd2.str);
		cmd2.str = ft_strdup(new);
		enter_hub(&cmd2, history, env);
		ft_strdel(&new);
		clear_cmd(&cmd2);
		tputs(tgetstr("cr", NULL), 1, tputchar);
		return (NULL);
	}
	clear_cmd(&cmd2);
	return (new);
}

void		init_var_bang(char *c, int *is_p, int *i)
{
	*c = 0;
	*is_p = 0;
	*i = 0;
}