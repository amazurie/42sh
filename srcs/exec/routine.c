/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hublanc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 11:10:52 by hublanc           #+#    #+#             */
/*   Updated: 2017/10/30 16:33:47 by amazurie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void		check_status(int status)
{
	if (status == 6 || status == 10 || status == 11)
	{
		ft_putstr_fd("Program has encounter a problem: ", 2);
		get_signal(status);
	}
	else if (status == 2)
		ft_putchar('\n');
}

void		exec_cmd(t_node *tree, char ***env, t_control **hist, int ghost)
{
	static int		input = 0;
	static int		fd[2] = {0, 1};
	int				*signal;

	signal = singleton_status();
	if (get_fail() == 1)
		reset_var(&input, &fd[0], &fd[1]);
	if (tree->pipe)
		pipe(fd);
	else if (tree->end_pipe)
		fd[1] = 1;
	tree->in = input;
	tree->out = fd[1];
	tree->in_pipe = fd[0];
	if (!ghost)
	{
		get_cmd(tree, env, signal, hist);
		check_status(*signal);
	}
	fd[1] != 1 ? close(fd[1]) : 0;
	input != 0 ? close(input) : 0;
	if (tree->pipe)
		input = fd[0];
	if (tree->end_pipe)
		reset_var(&input, &fd[0], &fd[1]);
}

int			hub(t_node *tree, char ***env, t_control **hist)
{
	int		*fail;

	fail = singleton_fail();
	if (tree->value == 1)
		exec_cmd(tree, env, hist, 0);
	if (tree->wait)
		wait_allpid();
	if (tree->value == 4 && tree->right)
	{
		pipe_flag(tree);
		end_flag(tree);
		wait_flag(tree);
	}
	tree->value != 3 ? close_fd(tree) : 0;
	if (tree->value == 3 && manage_fd(tree) == -1)
	{
		*fail = 1;
		return (-1);
	}
	if (tree->value == 3 && tree->left == NULL)
		exec_cmd(tree, env, hist, 1);
	return (1);
}

int			exec_tree(t_node *tree, char ***env, t_control **hist)
{
	static int		stop = 0;

	if (!tree)
		return (0);
	if (tree->value < 5 && hub(tree, env, hist) == -1)
	{
		stop = 1;
		return (-1);
	}
	if (tree->left && tree->left->do_it == 0 && !stop)
		exec_tree(tree->left, env, hist);
	if (tree->value == 7)
		operator_and(tree);
	else if (tree->value == 8)
		operator_or(tree);
	if (tree->value >= 5 && stop == 1)
		stop = 0;
	if (tree->right && tree->right->do_it == 0 && !stop)
		exec_tree(tree->right, env, hist);
	return (1);
}

void		routine(char *cmd, char ***env, t_control **history)
{
	t_token		*list;
	t_node		*tree;
	char		*new_command;

	if (!cmd)
		return ;
	ft_putcolor("cmd : ");
	ft_putendl(cmd);
	new_command = wd_designator(cmd, history);
	ft_putcolor("new : ");
	ft_putendl(new_command);
	if (new_command == NULL)
		return ;
	list = tokenizer(new_command);
	display_token(list);
	ft_putendl("TRI");
	list = sort_token(list, history);
	if (!list)
	{
		ft_strdel(&new_command);
		return ;
	}
	display_token(list);
	tree = create_tree(list);
	if (tree == NULL)
		return ;
	reset_term();
	node_print(tree, 0, 5);
	exec_tree(tree, env, history);
	set_terminal();
	del_token(&list);
	destroy_tree(tree);
	ft_strdel(&new_command);
}
