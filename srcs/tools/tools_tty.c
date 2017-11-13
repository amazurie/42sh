/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_tty.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazurie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 16:18:47 by amazurie          #+#    #+#             */
/*   Updated: 2017/11/13 14:17:19 by hublanc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	test_tty(struct termios term)
{
	char	tmp[6];
	int		ret;

	ret = 0;
	term.c_cc[VMIN] = 0;
	term.c_cc[VTIME] = 1;
	tcsetattr(0, TCSADRAIN, &term);
	tmp[5] = 0;
	if (!isatty(0))
	{
		tmp[0] = 0;
		if (read(0, tmp, 5) == -1)
			ret = 1;
		if (!tmp[0])
			ret = 1;
		save_buf(tmp);
		can_sigint(1);
	}
	if (!isatty(1))
		if (read(1, tmp, 0) == -1)
			ret += 2;
	return (ret);
}

int			check_in(struct termios term)
{
	int		ret;

	ret = 0;
	g_term = term;
	term.c_lflag &= ~(ECHO | ICANON);
	if (!save_buf(NULL))
		ret = test_tty(term);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	tcsetattr(0, TCSADRAIN, &term);
	return (ret);
}

int			ttyyyy(int i)
{
	if (i == 0)
		return (isatty(0) && isatty(1));
	if (i == 2)
		return (isatty(0));
	return (1);
}
