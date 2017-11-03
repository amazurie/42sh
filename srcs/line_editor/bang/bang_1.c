/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bang_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hublanc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 19:28:52 by hublanc           #+#    #+#             */
/*   Updated: 2017/11/03 22:00:24 by hublanc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char			*replace_str(char **tab, char *final, t_bang2 *bang)
{
	char	*new;
	char	*tmp;
	int		i;

	new = ft_strsub(final, 0, bang->begin);
	i = 0;
	while (tab && tab[i])
	{
		new = ft_strapp(new, tab[i]);
		i++;
	}
	tmp = ft_strsub(final, bang->end, ft_strlen(final) - 1);
	new = ft_strapp(new, tmp);
	ft_strdel(&tmp);
	ft_strdel(&final);
	return (new);
}

void			del_bang(t_bang2 *bang)
{
	if (!bang)
		return ;
	if (bang->cmd)
		ft_strdel(&(bang->cmd));
	if (bang->str)
		ft_strdel(&(bang->str));
	free(bang);
}

int				begin_bang(t_control *hist, char **final, int i)
{
	t_bang2		*bang;
	char		**tab;

	bang = (t_bang2*)ft_memalloc(sizeof(t_bang2));
	bang->begin = i;
	i = event_designator(*final, bang, i);
	i = word_designator_x(*final, bang, i);
	i = word_designator_y(*final, bang, i);
	i = word_modifier(*final, bang, i);
	bang->end = i;
	if (!(tab = get_line_history(hist, bang, *final))
	|| !(tab = designator_fnc(tab, bang)))
		return (-1);
	*final = replace_str(tab, *final, bang);
	i = bang->begin;
	del_tabstr(&tab);
	del_bang(bang);
	return (i);
}

char			*deal_bang(char *cmd, t_control *hist)
{
	char		c;
	char		*new;
	int			i;

	c = 0;
	i = 0;
	if (!ft_strchr(cmd, '!'))
		return (ft_strdup(cmd));
	new = ft_strdup(cmd);
	while (new && new[i])
	{
		if (new[i] == '!' && new[i + 1] && new[i + 1] != ' ' && c != '\''
			&& new[i + 1] != '\t' && new[i + 1] != '=' && new[i + 1] != '(')
			if ((i = begin_bang(hist, &new, i)) == -1)
				return (NULL);
		if (new[i] == '\'')
			while (new[i] && new[i] != '\'')
				i++;
		if (new[i] == '\\')
			i++;
		new[i] ? i++ : 0;
	}
	add_hist_or_not(&hist, new);
	ft_putendl(new);
	return (new);
}
