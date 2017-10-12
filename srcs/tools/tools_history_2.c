/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_history_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mameyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/09 15:57:56 by mameyer           #+#    #+#             */
/*   Updated: 2017/10/12 15:33:16 by mameyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		add_hist_or_not(t_control **history, char *str)
{
	if (*history && (*history)->length == 0)
		(*history) = dll_add_new_elem_frnt(*history, str);
	else if (*history && (*history)->begin && (*history)->begin->name
		&& ft_strcmp((*history)->begin->name, str) != 0)
		(*history) = dll_add_new_elem_frnt(*history, str);
	else if (*history && (*history)->begin && (*history)->begin->name
		&& ft_strcmp((*history)->begin->name, str) == 0)
		return ;
	else
		(*history) = dll_add_new_elem_frnt(*history, str);
}

void		change_cmd(char *new, t_cmd *cmd)
{
	go_begin(cmd->col, cmd->sc_col);
	tputs(tgetstr("cd", NULL), 1, tputchar);
	if (!ft_strcmp(cmd->prompt, "dquote> ")
		|| !ft_strcmp(cmd->prompt, "quote> ")
		|| !ft_strcmp(cmd->prompt, "heredoc> ")
		|| !ft_strcmp(cmd->prompt, "pipe> "))
		ft_putstr(cmd->prompt);
	else
		print_prompt();
	ft_putstr(new);
	cmd->col = ft_strlen(new) + cmd->prlen + 1;
	ft_strdel(&(cmd->str));
	cmd->str = ft_strdup(new);
}

void		set_selected_null(t_control **history)
{
	t_lst		*tmp;

	tmp = NULL;
	tmp = (*history)->begin;
	while (tmp != NULL)
	{
		tmp->selected = 0;
		tmp = tmp->next;
	}
}
