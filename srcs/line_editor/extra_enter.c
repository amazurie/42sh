/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_enter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hublanc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 13:52:21 by hublanc           #+#    #+#             */
/*   Updated: 2017/11/13 13:54:06 by hublanc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		t_istwo(int t, t_cmd *cmd)
{
	if (t == 2)
	{
		clear_cmd(cmd);
		*cmd = init_cmd(return_prompt());
	}
}
