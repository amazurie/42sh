/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbopp <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 14:01:06 by lbopp             #+#    #+#             */
/*   Updated: 2016/11/14 12:13:53 by lbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_striter(char *s, void (*f)(char*))
{
	unsigned int	i;

	i = 0;
	if (!s || !f)
		return ;
	while (s[i])
	{
		f(&(s[i]));
		i++;
	}
}
