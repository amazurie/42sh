/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hublanc <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 17:08:55 by hublanc           #+#    #+#             */
/*   Updated: 2017/10/12 19:16:56 by hublanc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

/*
**	Token.c
*/
t_token		*new_token(char *token, int type);
void		add_token(t_token **list, t_token *new);
void		delone_token(t_token **list);
void		del_token(t_token **list);
t_token		*destroy_one(t_token *list, t_token *cur);

/*
**	Lexer.c
*/
int			add_word(char *cmd, t_token **list);
t_token		*tokenizer(char *cmd);

/*
**	Node.c
*/
void		destroy_tree(t_node *leaf);
void		insert_right(t_node **leaf, int value, char *token);
void		insert_pipe(t_node **leaf, int value, char *token, int depth);
void		insert_token(t_node **leaf, t_token *tk, int depth, int pipe);

/*
**	Sort_token.c
*/
t_token		*sort_token(t_token *list, t_control **history);

/*
**	Stock_tree.c
*/
t_node		*create_tree(t_token *list);

/*
**	Extra_lexer.c
*/
void		node_print(t_node *this, int current_level, int max_level);
t_token		*get_prev(t_token *list, t_token *cur);
void		display_token(t_token *list);
void		extra_check_word(t_token *list, t_token *tmp, t_token **next);

/*
**	substitution.c
*/
int			substitution(char **cmmd, int is_redir);

#endif
